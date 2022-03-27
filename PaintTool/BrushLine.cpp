#define _USE_MATH_DEFINES
#include <math.h>
#include "Layer.h"
#include "Canvas.h"
#include "BrushLine.h"


BrushLine::BrushLine() : start(0)
{
}

BrushLine::~BrushLine()
{
	delete start;
}


void BrushLine::MouseDown(const sf::Vector2f& position, Layer& layer)
{
	delete start;
	start = new sf::Vector2f(position);
	delete overlay;
	overlay = new Layer(canvas->Width(), canvas->Height());
}

Layer* BrushLine::Update(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		MouseDown(position, layer);
		return nullptr;
	}
	overlay->Clear();
	sf::CircleShape circle = MakeLineEnds();
	DrawLine(position, *start, *overlay, circle);
	return overlay;
}

Layer* BrushLine::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	if (!start)
	{
		return nullptr;
	}
	sf::CircleShape circle = MakeLineEnds();
	DrawLine(position, *start, layer, circle);
	delete start;
	start = 0;
	delete overlay;
	overlay = 0;
	return nullptr;
}

sf::CircleShape BrushLine::MakeLineEnds() const
{
	sf::CircleShape circle(size / 2.f);
	circle.setFillColor(color);
	circle.setOutlineColor(color);
	return circle;
}
