#include <iostream>
#include <complex>      // std::complex, std::abs
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;
#include <sstream>

int main ()
{
    //set up window
    int resolutionWidth = VideoMode::getDesktopMode().width;
    int resolutionHeight = VideoMode::getDesktopMode().height;
    double aspectRatio = resolutionHeight * 1.0 / resolutionWidth;
    //cout << "Aspect ratio: " << fixed << aspectRatio << endl;

    VideoMode vm(resolutionWidth, resolutionHeight);

    RenderWindow window(vm, "Mandelbrot Viewer", Style::Default);

    RectangleShape rectangle;

    enum State{ CALCULATING, DISPLAYING };
    State progState = CALCULATING;

    ComplexPlane plane(aspectRatio);

    //this function is used to load text before the mouse moves, may be unnecessary
    Vector2i mouseLocation = sf::Mouse::getPosition(window);
    Vector2f mouseLocationF;
    mouseLocationF.x = mouseLocation.x;
    mouseLocationF.y = mouseLocation.y;
    plane.setMouseLocation(mouseLocationF);
    plane.loadText(window);
    window.display();
    /*
    View view0 = plane.getView();
    Vector2f centerCoord = view0.getCenter();
    cout << "Center X: " << centerCoord.x << endl;
    cout << "Center Y: " << centerCoord.y << endl;
    Vector2f size = view0.getSize();
    cout << "Size X: " << size.x << endl;
    cout << "Size Y: " << size.y << endl;
    */


    VertexArray vArray(sf::Points, resolutionWidth * resolutionHeight);
    Uint8 r, g, b = 0;
    int pixIndex = 0;
    View view = plane.getView();
    //Vector2i pixelPos;
    //Vector2f pixelCoord;
    //size_t iterations;
    //Vector2f pixelPosF;
    //Color color;
    
    for(int i= 0; i < resolutionWidth; i++)
    {
        for(int j=0; j< resolutionHeight; j++)
        {
            Vector2i pixelPos = {i,j};
            Vector2f pixelCoord = window.mapPixelToCoords(pixelPos, view);
            size_t iterations = plane.countIterations(pixelCoord);
            plane.iterationsToRGB(iterations, r, g, b);
            Color color(r,g,b);
            vArray[pixIndex].position = {double(i),double(j)};
            vArray[pixIndex].color = color;
            pixIndex++;
            //cout << "Pixel position: " << pixelPos.x << ", " << pixelPos.y << endl;
            //cout << "Pixel coord: " << pixelCoord.x << ", " << pixelCoord.y << endl;
        }
    }
    
    window.draw(vArray);
    window.display();
    
    //stall for testing above drawing
    /*
    Event event;
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || 
                (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                {
                    window.close();
                }
        }
    } */


    Event event;
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || 
              (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
            }
            
            //if mouse moves, check for mouse location and update cursor text
            if (event.type == sf::Event::MouseMoved)
            {
                window.clear(); //maybe have text in a separate view to avoid clearing mandelbrot set
                //set new mouse location
                Vector2f mouseLocation;
                mouseLocation.x = event.mouseMove.x;
                mouseLocation.y = event.mouseMove.y;
                plane.setMouseLocation(mouseLocation);
                
                //things drawn in the function can be displayed outside
                plane.loadText(window);
                window.display();
            }

            //if mouse is clicked, zoomIn/zoomOut, set up new View / set center
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //Zoom In
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    //Zoom Out
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }
        }
    }

    return 0;
    
}
