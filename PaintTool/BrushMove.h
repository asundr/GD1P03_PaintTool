#pragma once

#include "Brush.h"

class BrushMove : public Brush
{
protected:
	sf::Vector2f* start;
	sf::Vector2f* layerStart;
	sf::Sprite* spriteUI;

public:
	BrushMove();
	~BrushMove();
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer);
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer);
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer);

};

