#include "BrushMove.h"
#include "Layer.h"

#include <iostream>

BrushMove::BrushMove()
{
	start = 0;
	layerStart = 0;
}

BrushMove::~BrushMove()
{
	delete layerStart;
	delete start;
}

void BrushMove::MouseDown(const sf::Vector2f& position, Layer& layer)
{
	delete layerStart;
	delete start;
	layerStart = new sf::Vector2f(layer.GetPosition());
	start = new sf::Vector2f(position);
}

Layer* BrushMove::Update(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		MouseDown(position, layer);
		return nullptr;
	}
	else
	{
		sf::Vector2f dif = Subtract(position, *start);
		layer.move(dif);
	}
	delete start;
	start = new sf::Vector2f(position);
	return overlay;
}

void BrushMove::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	//sf::Vector2f dif = Subtract(position, *start);
	delete layerStart;
	delete start;
	layerStart = 0;
	start = 0;
}
