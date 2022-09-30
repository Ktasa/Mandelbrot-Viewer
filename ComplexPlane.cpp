#include <complex>      // std::complex, std::abs
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;
#include <iostream>
#include <cmath>

    ComplexPlane::ComplexPlane(double aspectRatio)
    {
        m_aspectRatio = aspectRatio;
        m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
        m_view.setCenter(0.0, 0.0);
        m_zoomCount = 0;
    }
    void ComplexPlane::zoomIn()
    {
        m_zoomCount++;
        double x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
        double y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
        m_view.setSize(x_size, -y_size);
    }
    void ComplexPlane::zoomOut()
    {
        m_zoomCount--;
        double x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
        double y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
        m_view.setSize(x_size, -y_size);
    }
    void ComplexPlane::setCenter(Vector2f coord)
    {
        m_view.setCenter(coord.x, coord.y);
        //sf::View::setCenter() is its own SFML function
    }
    void ComplexPlane::setMouseLocation(Vector2f coord)
    {
        m_mouseLocation.x = coord.x;
        m_mouseLocation.y = coord.y;
    }
    void ComplexPlane::loadText(Text& text)
    {
        //use stringstream and corresponding member variables
        //to create output
        //Mandelbrot Set
        //Center:(0,0)
        //Cursor:(0,0)
        //Left-click to Zoom In
        //Right-click to Zoom Out
    }
    View ComplexPlane::getView()
    {
        return m_view;
    }
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
    //actually BW can still use RGB values so maybe keep the 1st function
    void ComplexPlane::iterationsToBW(size_t count, Uint8& shade)
    {
        double iter_ratio = count / 64.0;
        shade = iter_ratio * 255;
        //store shade value where ever its needed
    }
