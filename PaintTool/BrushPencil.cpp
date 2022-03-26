#include "BrushPencil.h"
#include "Layer.h"


BrushPencil::BrushPencil()
{
	start = 0;
	size = 10;
	color = sf::Color::Black;
	shape = new sf::CircleShape((float)size);
	shape->setFillColor(color);
	shape->setOutlineColor(color);
}

BrushPencil::~BrushPencil()
{
	delete shape;
	delete start;
}

void BrushPencil::MouseDown(const sf::Vector2f& position, Layer& layer)
{
	delete start;
	start = new sf::Vector2f(position);

}

Layer* BrushPencil::Update(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		MouseDown(position, layer);
		return nullptr;
	}
	DrawLine(position, *start, layer, *shape);
	delete start;
	start = new sf::Vector2f(position);
	return overlay;
}

void BrushPencil::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	delete start;
	start = 0;
}
