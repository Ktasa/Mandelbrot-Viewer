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

    enum State{ CALCULATING, DISPLAYING };
    State progState = CALCULATING;


    while(window.isOpen())
    {
 
    }

    return 0;
    
}
