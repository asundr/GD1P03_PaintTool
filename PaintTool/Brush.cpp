#define _USE_MATH_DEFINES
#include <math.h>
#include "Layer.h"
#include "Brush.h"

const Canvas* Brush::canvas = nullptr;

Brush::Brush(int size, sf::Color color) : size(size), color(color), overlay(0)
{
}

Brush::~Brush()
{
	delete overlay;
}

void Brush::SetColor(const sf::Color color)
{
	this->color = color;
}

void Brush::SetSize(float size)
{
	this->size = size;
}

const sf::Color& Brush:: GetColor() const
{
	return color;
}

int Brush::GetSize() const
{
	return size;
}

void Brush::SetCanvas(const Canvas* canvas)
{
	Brush::canvas = canvas;
}

// Subtracts the vector b from vector a and returns it
sf::Vector2f Brush::Subtract(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a.x - b.x, a.y - b.y);
}

// Draws a line between points a and b with the passed shape on the passed layer
// Could be made more efficient for circle-shaped lines by using a RectancleShape
void Brush::DrawLine(const sf::Vector2f& a, const sf::Vector2f& b, Layer& layer, sf::Shape& shape)
{
	sf::Vector2f dif = Subtract(a, b);
	float length = sqrtf(dif.x * dif.x + dif.y * dif.y);
	float angle = atanf(dif.y / dif.x) * 180.f / (float)M_PI;
	sf::Vector2f norm = sf::Vector2f(dif.x / length, dif.y / length);
	sf::Vector2f perpendicularDif = sf::Vector2f(-norm.y * size / 2.f, norm.x * size / 2.f);

	sf::VertexArray lines(sf::Quads, 4);
	lines[0].position = sf::Vector2f(b.x + perpendicularDif.x, b.y + perpendicularDif.y);
	lines[1].position = sf::Vector2f(b.x - perpendicularDif.x, b.y - perpendicularDif.y);
	lines[3].position = sf::Vector2f(a.x + perpendicularDif.x, a.y + perpendicularDif.y);
	lines[2].position = sf::Vector2f(a.x - perpendicularDif.x, a.y - perpendicularDif.y);

	for (int i = 0; i < 4; ++i)
	{
		lines[i].color = color;
	}
	layer.draw(lines);

	sf::CircleShape roundedEnd(size / 2.f);
	roundedEnd.setFillColor(color);
	roundedEnd.setPosition(sf::Vector2f(a.x - size / 2, a.y - size / 2));
	layer.draw(roundedEnd);
	roundedEnd.setPosition(sf::Vector2f(b.x - size / 2, b.y - size / 2));
	layer.draw(roundedEnd);
}
