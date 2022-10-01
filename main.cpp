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

    //iteration counter test
    Vector2f test_coord;
    test_coord.x = 5;
    test_coord.y = 0; //imaginary part
    ComplexPlane test_plane(aspectRatio); 
    test_plane.countIterations(test_coord);

    enum State{ CALCULATING, DISPLAYING };
    State progState = CALCULATING;

    test_plane.loadAllText(window);

    Event input;
    while(window.isOpen())
    {
        while(window.pollEvent(input))
        {
            if(input.type == Event::KeyPressed && input.key.code == Keyboard::Escape)
            {
                window.close();
            }
            //if cursor moves, check for mouse location and update cursor text
            //if mouse is clicked, zoomIn/zoomOut, set up new View
        }
    }

    return 0;
    
}
