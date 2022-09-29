#include <iostream>
#include <complex>      // std::complex, std::abs
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;

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


    //set up default view on start:
    //calculate all colors (black & white) for each pixel by counting iterations
    //draw text (requires checking mouse position)

    while(window.isOpen())
    {
        //get mouse location / check mouse input

        //if mouse moves:
        //update text (must update when mouse position moves)
        //"Mandelbrot Set", "Center (x, y)", "Cursor (x, y)"
        //"Left-Click to Zoom In", "Right-Click to Zoom Out"

        //if mouse click:
        //calculate new View, remap pixels to comlpex plane coords
        //calculate color of each pixel
        //update text
        //display updated screen at the end
    }

    return 0;
    
}
