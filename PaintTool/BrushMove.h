#pragma once

#include "Brush.h"

class BrushMove : public Brush
{
protected:
	sf::Vector2f* start;
	sf::Vector2f* layerStart;

public:
	BrushMove();
	~BrushMove();
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer);
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer);
	virtual void MouseUp(const sf::Vector2f& position, Layer& layer);

};

