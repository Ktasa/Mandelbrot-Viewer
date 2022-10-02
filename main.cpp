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
    double aspectRatio = resolutionHeight / resolutionWidth;

    VideoMode vm(resolutionWidth, resolutionHeight);

    RenderWindow window(vm, "Mandelbrot Viewer", Style::Default);

    RectangleShape rectangle;

    /*iteration counter test
    Vector2f test_coord;
    test_coord.x = 5;
    test_coord.y = 0; //imaginary part
    ComplexPlane test_plane(aspectRatio); 
    test_plane.countIterations(test_coord);
    */

    enum State{ CALCULATING, DISPLAYING };
    State progState = CALCULATING;

    ComplexPlane plane(aspectRatio);

    //this function is used to load text before the mouse moves, may be unnecessary
    plane.loadAllText(window);

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
                //update cursor text
                Text cursor; //maybe just pass coordinates instead of doing text set up here
                ostringstream cursorStream;
                cursorStream << "Cursor:(" << mouseLocation.x << ", " << mouseLocation.y << ")";
                cursor.setString(cursorStream.str());
                plane.loadText(cursor, window);
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
