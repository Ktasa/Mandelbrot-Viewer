#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <SFML/Graphics.hpp>
using namespace sf;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

class ComplexPlane
{
public:
    ComplexPlane(double aspectRatio);
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2f coord);
    void setMouseLocation(Vector2f coord);
    void loadText(Text& text);
    View getView();
    size_t countIterations(Vector2f coord);
    //void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
    void iterationsToBW(size_t count, Uint8& shade); 

private:
    View m_view;
    Vector2f m_mouseLocation;
    int m_zoomCount;
    double m_aspectRatio;
};

#endif
