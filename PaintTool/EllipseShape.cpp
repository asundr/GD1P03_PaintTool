#define _USE_MATH_DEFINES
#include <math.h>
#include "EllipseShape.h"

EllipseShape::EllipseShape() : pointCount(30), radius(sf::Vector2f(1.f,1.f))
{
}

EllipseShape::~EllipseShape()
{
}

void EllipseShape::setRadius(const sf::Vector2f radius)
{
    this->radius.x = radius.x;
    this->radius.y = radius.y;
}

sf::Vector2f EllipseShape::getRadius() const
{
    return radius;
}

std::size_t EllipseShape::getPointCount() const
{
    return pointCount;
}

sf::Vector2f EllipseShape::getPoint(std::size_t index) const
{
    float angle = index * 2.f * (float)M_PI / getPointCount() - (float)M_PI / 2.f;
    float x = (1.f + std::cos(angle)) * radius.x;
    float y = (1.f + std::sin(angle)) * radius.y;
    return sf::Vector2f(x, y);
}
