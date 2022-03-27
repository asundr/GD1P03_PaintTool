#include "Layer.h"
#include "Canvas.h"
#include "EllipseShape.h"
#include "BrushEllipse.h"

BrushEllipse::BrushEllipse() : start(0)
{
}

BrushEllipse::~BrushEllipse()
{
	delete start;
}

void BrushEllipse::MouseDown(const sf::Vector2f& position, Layer& layer)
{
	delete start;
	start = new sf::Vector2f(position);
	delete overlay;
	overlay = new Layer(canvas->Width(), canvas->Height());
}

Layer* BrushEllipse::Update(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		MouseDown(position, layer);
		return nullptr;
	}
	overlay->Clear();
	DrawEllipse(position, *overlay);
	return overlay;
}

Layer* BrushEllipse::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		return nullptr;
	}
	DrawEllipse(position, layer);
	delete start;
	start = 0;
	delete overlay;
	overlay = 0;
	return nullptr;
}

void BrushEllipse::DrawEllipse(const sf::Vector2f& position, Layer& layer) const
{
	sf::Vector2f dif = Subtract(position, *start);
	sf::Vector2f origin = sf::Vector2f(fminf(start->x, position.x), fminf(start->y, position.y));
	EllipseShape ellipse;
	ellipse.setOutlineColor(color);
	ellipse.setFillColor(sf::Color::Transparent);
	ellipse.setPosition(origin);
	sf::Vector2f radius = sf::Vector2f(abs(dif.x) / 2.f, abs(dif.y) / 2.f);
	ellipse.setRadius(radius);
	ellipse.setOutlineThickness(size);
	layer.draw(ellipse);
}
