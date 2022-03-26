#include "Layer.h"
#include "BrushPolygon.h"

BrushPolygon::BrushPolygon() : points(std::vector<sf::Vector2f>()), overlay(0)
{
}

BrushPolygon::~BrushPolygon()
{
    delete overlay;
}

void BrushPolygon::MouseDown(const sf::Vector2f& position, Layer& layer)
{
    if (points.empty())
    {
        overlay = new Layer(823, 1180);
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

    sf::CircleShape placeholder;

    for (int i = 0; i < points.size() - 1; ++i)
    {
        DrawLine(points[i], points[(i + 1) % points.size()], *overlay, placeholder);
    }
    return overlay;
}

void BrushPolygon::MouseUp(const sf::Vector2f& position, Layer& layer)
{
    if (points.empty())
    {
        return;
    }
    sf::Vector2f dif = Subtract(position, points[0]);
    float distance = sqrtf(dif.x * dif.x + dif.y * dif.y);
    bool snap = distance < size * 2;
    if (snap && points.size() > 1)
    {
        sf::CircleShape placeholder;
        placeholder.setOutlineColor(color);

        for (int i = 0; i < points.size(); ++i)
        {
            DrawLine(points[i], points[(i + 1) % points.size()], layer, placeholder);
        }
        points.clear();
        delete overlay;
        overlay = 0;
    }
}
