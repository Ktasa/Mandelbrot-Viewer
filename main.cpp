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

    enum State{ CALCULATING, DISPLAYING, IDLE };
    State progState = IDLE;

    ComplexPlane plane(aspectRatio);

    VertexArray vArray(sf::Points, resolutionWidth * resolutionHeight);
    Uint8 r = 0, g = 0, b = 0;
    int pixIndex = 0;
    View view = plane.getView();
    
    for(int i=0; i < resolutionWidth; i++)
    {
        for(int j=0; j< resolutionHeight; j++)
        {
            Vector2i pixelPos = {i,j};
            Vector2f pixelCoord = window.mapPixelToCoords(pixelPos, view);
            size_t iterations = plane.countIterations(pixelCoord);
            plane.iterationsToRGB(iterations, r, g, b);
            Color color(r,g,b);
            vArray[pixIndex].position = {float(i),float(j)};
            vArray[pixIndex].color = color;
            pixIndex++;
        }   
    }
    window.draw(vArray);
    window.display();

    Text hud;
    Vector2i mouseLocation = sf::Mouse::getPosition(window);
    Vector2f cursorCoord = window.mapPixelToCoords(mouseLocation, plane.getView());
    plane.setMouseLocation(cursorCoord);
    plane.loadText(hud, window);
    window.display();
    
    int mouseCount = 0; //variable to prevent displaying too frequently due to mouse movement
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
                //set new mouse location
                Vector2i mouseLocation;
                mouseLocation.x = event.mouseMove.x;
                mouseLocation.y = event.mouseMove.y;
                Vector2f cursorCoord = window.mapPixelToCoords(mouseLocation, plane.getView());
                plane.setMouseLocation(cursorCoord);

                //limit screen updates to prevent lagging
                if (mouseCount%10 == 0)
                {
                    progState = DISPLAYING;
                }
                mouseCount++;
                mouseCount %= 100;
            }
            
            //if mouse is clicked, zoomIn/zoomOut, set up new View / set center
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //Zoom In
                    Vector2i mouseLocation;
                    mouseLocation.x = event.mouseButton.x;
                    mouseLocation.y = event.mouseButton.y;
                    Vector2f centerCoord = window.mapPixelToCoords(mouseLocation, plane.getView());
                    plane.setCenter(centerCoord);
                    plane.zoomIn();

                    progState = CALCULATING;
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    //Zoom Out
                    Vector2i mouseLocation;
                    mouseLocation.x = event.mouseButton.x;
                    mouseLocation.y = event.mouseButton.y;
                    Vector2f centerCoord = window.mapPixelToCoords(mouseLocation, plane.getView());
                    plane.setCenter(centerCoord);
                    plane.zoomOut();

                    progState = CALCULATING;
                }
            }
            if(progState == CALCULATING)
            {   
                //VertexArray vArray(sf::Points, resolutionWidth * resolutionHeight);
                Uint8 r = 0, g = 0, b = 0;
                int pixIndex = 0;
                View view = plane.getView();
                
                for(int i=0; i < resolutionWidth; i++)
                {
                    for(int j=0; j< resolutionHeight; j++)
                    {
                        Vector2i pixelPos = {i,j};
                        Vector2f pixelCoord = window.mapPixelToCoords(pixelPos, view);
                        size_t iterations = plane.countIterations(pixelCoord);
                        plane.iterationsToRGB(iterations, r, g, b);
                        Color color(r,g,b);
                        vArray[pixIndex].position = {float(i),float(j)};
                        vArray[pixIndex].color = color;
                        pixIndex++;
                    }   
                }
                progState = DISPLAYING;                 
            } 
            if (progState == DISPLAYING)
            {
                window.clear();
                window.draw(vArray);
                plane.loadText(hud, window);
                window.display();
                progState = IDLE;
            }
        } 
    }

    return 0;
    
}
