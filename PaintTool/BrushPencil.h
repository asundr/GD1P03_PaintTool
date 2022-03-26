#pragma once

#include "Brush.h"

class BrushPencil : public Brush
{
protected:
	sf::Vector2f* start;
	sf::CircleShape* shape;
public:
	BrushPencil();
	~BrushPencil();
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer);
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer);
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer);
};
