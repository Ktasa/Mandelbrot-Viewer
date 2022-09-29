#include <complex>      // std::complex, std::abs
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;
#include <iostream>

    ComplexPlane::ComplexPlane(double aspectRatio)
    {}
    void ComplexPlane::zoomIn()
    {}
    void ComplexPlane::zoomOut()
    {}
    void ComplexPlane::setCenter(Vector2f coord)
    {}
    void ComplexPlane::setMouseLocation(Vector2f coord)
    {}
    void ComplexPlane::loadText(Text& text)
    {}
    View ComplexPlane::getView()
    {}
    size_t ComplexPlane::countIterations(Vector2f coord)
    {
        double re = coord.x;
        double im = coord.y; 
        complex<double> c (re, im);
        complex<double> z (0,0);

        size_t i = 0;
        bool escaped = false;
        while (i < MAX_ITER && !escaped)
        {
            z = z*z + c;
            if (abs(z) > 2.0)
            {
                escaped = true;
            }
            else {i++;}
        }
        //cout << "total iterations: " << i << endl;
        return i;
    }
    
    //void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b){}

    void ComplexPlane::iterationsToBW(size_t count, Uint8& shade)
    {
        double iter_ratio = count / 64.0;
        shade = iter_ratio * 255;
        //store shade value where ever its needed
    }
