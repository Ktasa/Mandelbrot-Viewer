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
        //sf::View::setCenter() is its own SFML function
    }
    void ComplexPlane::setMouseLocation(Vector2f coord)
    {
        m_mouseLocation.x = coord.x;
        m_mouseLocation.y = coord.y;
    }
    //RenderWindow param added for testing
    void ComplexPlane::loadText(Text& text, sf::RenderWindow& window)
    {
        int resolutionWidth = VideoMode::getDesktopMode().width;
        int resolutionHeight = VideoMode::getDesktopMode().height;

        Font arial;
        arial.loadFromFile("arial.ttf");
        double textPositionX = resolutionWidth / 100.0f;
        double textPositionY = resolutionHeight / 100.0f;
        double textSpacing = resolutionHeight / 20.f;

        Text title, center, cursor, zoomI, zoomO;
        title.setString("Mandelbrot Set");
        title.setCharacterSize(20);
        title.setFillColor(Color::White);
        title.setFont(arial);

        FloatRect textRect = title.getLocalBounds();
        title.setOrigin(textRect.left,textRect.top);
        title.setPosition(textPositionX, textPositionY);

        string centerStr = "Center:(0,0)"; //use View object to get center position (convert to complex)
        center.setString(centerStr);
        center.setCharacterSize(20);
        center.setFillColor(Color::White);
        center.setFont(arial);

        textRect = center.getLocalBounds();
        center.setOrigin(textRect.left,textRect.top);
        center.setPosition(textPositionX, textPositionY+textSpacing);

        //Change to display cursor in terms of complex plane instead of pixels
        cursor = text; 
        cursor.setCharacterSize(20);
        cursor.setFillColor(Color::White);
        cursor.setFont(arial);

        textRect = cursor.getLocalBounds();
        cursor.setOrigin(textRect.left,textRect.top);
        cursor.setPosition(textPositionX, textPositionY+textSpacing*2);

        zoomI.setString("Left-click to Zoom In");
        zoomI.setCharacterSize(20);
        zoomI.setFillColor(Color::White);
        zoomI.setFont(arial);

        textRect = zoomI.getLocalBounds();
        zoomI.setOrigin(textRect.left,textRect.top);
        zoomI.setPosition(textPositionX, textPositionY+textSpacing*3);

        zoomO.setString("Right-click to Zoom Out");
        zoomO.setCharacterSize(20);
        zoomO.setFillColor(Color::White);
        zoomO.setFont(arial);

        textRect = zoomI.getLocalBounds();
        zoomO.setOrigin(textRect.left,textRect.top);
        zoomO.setPosition(textPositionX, textPositionY+textSpacing*4);

        window.draw(title);
        window.draw(center);
        window.draw(cursor);
        window.draw(zoomI);
        window.draw(zoomO);
        window.display();

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

    void ComplexPlane::loadAllText(sf::RenderWindow& window)
    {
        int resolutionWidth = VideoMode::getDesktopMode().width;
        int resolutionHeight = VideoMode::getDesktopMode().height;

        Font arial;
        arial.loadFromFile("arial.ttf");
        double textPositionX = resolutionWidth / 100.0f;
        double textPositionY = resolutionHeight / 100.0f;
        double textSpacing = resolutionHeight / 20.f;

        Text title, center, cursor, zoomI, zoomO;
        title.setString("Mandelbrot Set");
        title.setCharacterSize(20);
        title.setFillColor(Color::White);
        title.setFont(arial);

        FloatRect textRect = title.getLocalBounds();
        title.setOrigin(textRect.left,textRect.top);
        title.setPosition(textPositionX, textPositionY);

        string centerStr = "Center:(0,0)"; //use View object to get center position (convert to complex)
        center.setString(centerStr);
        center.setCharacterSize(20);
        center.setFillColor(Color::White);
        center.setFont(arial);

        textRect = center.getLocalBounds();
        center.setOrigin(textRect.left,textRect.top);
        center.setPosition(textPositionX, textPositionY+textSpacing);

        //Change to display cursor in terms of complex plane instead of pixels
        Vector2i localPosition = Mouse::getPosition(window);
        string cursorStr;
        ostringstream s;
        s << "Cursor:(" << localPosition.x << "," << localPosition.y << ")";
        cursorStr = s.str();
        cursor.setString(cursorStr);
        cursor.setCharacterSize(20);
        cursor.setFillColor(Color::White);
        cursor.setFont(arial);

        textRect = cursor.getLocalBounds();
        cursor.setOrigin(textRect.left,textRect.top);
        cursor.setPosition(textPositionX, textPositionY+textSpacing*2);

        zoomI.setString("Left-click to Zoom In");
        zoomI.setCharacterSize(20);
        zoomI.setFillColor(Color::White);
        zoomI.setFont(arial);

        textRect = zoomI.getLocalBounds();
        zoomI.setOrigin(textRect.left,textRect.top);
        zoomI.setPosition(textPositionX, textPositionY+textSpacing*3);

        zoomO.setString("Right-click to Zoom Out");
        zoomO.setCharacterSize(20);
        zoomO.setFillColor(Color::White);
        zoomO.setFont(arial);

        textRect = zoomI.getLocalBounds();
        zoomO.setOrigin(textRect.left,textRect.top);
        zoomO.setPosition(textPositionX, textPositionY+textSpacing*4);

        window.draw(title);
        window.draw(center);
        window.draw(cursor);
        window.draw(zoomI);
        window.draw(zoomO);
        window.display();
    }
    
