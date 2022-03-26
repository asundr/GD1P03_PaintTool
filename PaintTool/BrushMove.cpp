#include "BrushMove.h"
#include "Layer.h"

#include <iostream>

BrushMove::BrushMove()
{
	start = 0;
	layerStart = 0;
	spriteUI = 0;
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

	overlay = new Layer(823, 1180); // TODO
	spriteUI = new sf::Sprite(layer.GetTexture());

	layer.SetHidden(true);
}

Layer* BrushMove::Update(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		MouseDown(position, layer);
		return nullptr;
	}
	overlay->Clear();
	sf::Vector2f dif = Subtract(position, *start);
	sf::Vector2f newPos(dif.x + layerStart->x, dif.y + layerStart->y);
	spriteUI->setPosition(dif);
	overlay->draw(*spriteUI);
	return overlay;
}

Layer* BrushMove::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	sf::Vector2f dif = Subtract(position, *start);
	sf::Vector2f newPos(dif.x + layerStart->x, dif.y + layerStart->y);
	layer.SetPosition(newPos);
	layer.SetHidden(false);
	delete layerStart;
	delete start;
	layerStart = 0;
	start = 0;
	delete spriteUI;
	spriteUI = 0;
	delete overlay;
	overlay = 0;
	return nullptr;
}
