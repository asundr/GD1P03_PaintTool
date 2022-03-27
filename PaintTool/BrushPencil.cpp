#include "BrushPencil.h"
#include "Layer.h"


BrushPencil::BrushPencil() : start(0)
{
	shape = new sf::CircleShape(size);
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

Layer* BrushPencil::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	delete start;
	start = 0;
	return nullptr;
}
