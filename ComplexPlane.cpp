#include <complex>      // std::complex, std::abs
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;
#include <iostream>
#include <cmath>
#include <sstream>

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
    }
    void ComplexPlane::setMouseLocation(Vector2f coord)
    {
        m_mouseLocation = coord;
    }
    //RenderWindow param added for testing
    void ComplexPlane::loadText(Text& hud, sf::RenderWindow& window)
    {
        int resolutionWidth = VideoMode::getDesktopMode().width;
        int resolutionHeight = VideoMode::getDesktopMode().height;

        Font arial;
        arial.loadFromFile("arial.ttf");
        double textPositionX = resolutionWidth / 100.0f;
        double textPositionY = resolutionHeight / 100.0f;
        //double textSpacing = resolutionHeight / 20.f;

        hud.setCharacterSize(20);
        hud.setFillColor(Color::White);
        hud.setFont(arial);

        FloatRect textRect = hud.getLocalBounds();
        hud.setOrigin(textRect.left,textRect.top);
        hud.setPosition(textPositionX, textPositionY);
        
        ostringstream hudStream;
        hudStream << "Mandelbrot Set" << endl;
        Vector2f centerCoord = m_view.getCenter();
        hudStream << "Center:(" << centerCoord.x << ", " << centerCoord.y << ")" << endl;
        hudStream << "Cursor:(" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
        hudStream << "Left-click to Zoom In" << endl << "Right-click to Zoom Out" << endl;

        hud.setString(hudStream.str());
        window.draw(hud);
        //window.display();
        //cout << "LoadText Success" << endl;
    }
    View ComplexPlane::getView()
    {
        return m_view;
    }
    size_t ComplexPlane::countIterations(Vector2f coord)
    {
        complex<double> c (coord.x, coord.y);
        complex<double> z (0,0);

        size_t i = 0;
        while (i < MAX_ITER && abs(z) < 2.0)
        {
            z = z*z + c;
            i++;
        }
        //cout << "total iterations: " << i << endl;
        return i;
    }
    
    void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
    {
        double iter_ratio = double(count) / MAX_ITER;
        r = iter_ratio * 255;
        g = iter_ratio * 255;
        b = iter_ratio * 255;
        //high iteration count gets darker
    }
    
