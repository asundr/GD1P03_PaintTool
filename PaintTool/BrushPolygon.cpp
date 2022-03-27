#include "Layer.h"
#include "Canvas.h"
#include "BrushPolygon.h"

BrushPolygon::BrushPolygon() : points(std::vector<sf::Vector2f>())
{
}

BrushPolygon::~BrushPolygon()
{
}

// Starts new polygon or adds a new point if not closing the shape
void BrushPolygon::MouseDown(const sf::Vector2f& position, Layer& layer)
{
    if (points.empty())
    {
        overlay = new Layer(canvas->Width(), canvas->Height());
        points.push_back(sf::Vector2f(position));
    }
    else
    {
        sf::Vector2f dif = Subtract(position, points[0]);
        float distance = sqrtf(dif.x * dif.x + dif.y * dif.y);
        bool snap = distance < size * 2;
        if (!snap)
        {
            points.push_back(sf::Vector2f(position));
        }
    }
}

// Displays the current partial polygon
Layer* BrushPolygon::Update(const sf::Vector2f& position, Layer& layer)
{
    if (points.empty())
    {
        MouseDown(position, layer);
        return nullptr;
    }
    sf::Vector2f dif = Subtract(position, points[0]);
    float distance = sqrtf(dif.x * dif.x + dif.y * dif.y);
    bool snap = distance < size * 2;
    sf::Color opposite = sf::Color(255 - color.r, 255 - color.g, 255 - color.b, 255); // currently ignored, might change back
    sf::CircleShape corners;
    corners.setOutlineColor(opposite);
    corners.setRadius(size / 2.f);
    for (unsigned int i = 0; i < points.size() - 1; ++i)
    {
        DrawLine(points[i], points[(i + 1) % points.size()], *overlay, corners);
    }
    return overlay;
}

// Completes the polygon if last point matches with first point
Layer* BrushPolygon::MouseUp(const sf::Vector2f& position, Layer& layer)
{
    if (points.empty())
    {
        return nullptr;
    }
    sf::Vector2f dif = Subtract(position, points[0]);
    float distance = sqrtf(dif.x * dif.x + dif.y * dif.y);
    bool snap = distance < size * 2;
    if (snap && points.size() > 1)
    {
        sf::CircleShape corners;
        corners.setOutlineColor(color);
        corners.setRadius(size / 2.f);
        for (unsigned int i = 0; i < points.size(); ++i)
        {
            DrawLine(points[i], points[(i + 1) % points.size()], layer, corners);
        }
        points.clear();
        delete overlay;
        overlay = 0;
    }
    return overlay;
}
