#include "Layer.h"
#include "EllipseShape.h"
#include "BrushEllipse.h"

#include <iostream>

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
	overlay = new Layer(823, 1180); // TODO get from canvas
	
}

Layer* BrushEllipse::Update(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		MouseDown(position, layer);
		return nullptr;
	}
	overlay->Clear();
	sf::Vector2f dif = Subtract(position, *start);
	sf::Vector2f origin = sf::Vector2f(fminf(start->x, position.x), fminf(start->y, position.y));

	EllipseShape ellipse;
	ellipse.setOutlineColor(color);
	ellipse.setFillColor(sf::Color::Transparent);
	ellipse.setPosition(origin);
	sf::Vector2f radius = sf::Vector2f(abs(dif.x)/2.f, abs(dif.y)/2.f);
	std::cout << radius.x << '\t' << radius.y << std::endl;
	ellipse.setRadius(radius);
	ellipse.setOutlineThickness(size);
	overlay->draw(ellipse);

	return overlay;
}

void BrushEllipse::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	if (!start)
		return;

	sf::Vector2f dif = Subtract(position, *start);
	sf::Vector2f origin = sf::Vector2f(fminf(start->x, position.x), fminf(start->y, position.y));

	EllipseShape ellipse;
	ellipse.setOutlineColor(color);
	ellipse.setFillColor(sf::Color::Transparent);
	ellipse.setPosition(origin);
	sf::Vector2f radius = sf::Vector2f(abs(dif.x)/2.f, abs(dif.y)/2.f);
	//std::cout << radius.x << '\t' << radius.y << std::endl;
	ellipse.setRadius(radius);
	ellipse.setOutlineThickness(size);
	layer.draw(ellipse);


	delete start;
	start = 0;
	delete overlay;
	overlay = 0;
}
