#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <SFML/Graphics.hpp>
using namespace sf;

const unsigned int MAX_ITER = 64; //(64) temporarily reduced to 16 to make drawing faster
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
    void loadText(Text& hud, sf::RenderWindow& window); 
    View getView();
    size_t countIterations(Vector2f coord);
    void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);

private:
    View m_view;
    Vector2f m_mouseLocation;
    int m_zoomCount;
    double m_aspectRatio;
};

#endif
