#define _USE_MATH_DEFINES
#include <math.h>
#include "Layer.h"
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
	overlay = new Layer(823, 1180);
}

Layer* BrushLine::Update(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		MouseDown(position, layer);
		return nullptr;
	}
	sf::CircleShape circle((float)size / 2.f);
	circle.setFillColor(color);
	circle.setOutlineColor(color);
	overlay->Clear();
	DrawLine(position, *start, *overlay, circle);
	return overlay;
}

void BrushLine::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	if (!start)
		return;
	sf::CircleShape circle((float)size/2.f);
	circle.setFillColor(color);
	circle.setOutlineColor(color);
	DrawLine(position, *start, layer, circle);
	delete start;
	start = 0;
	delete overlay;
	overlay = 0;
}
