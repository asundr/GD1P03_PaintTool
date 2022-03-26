#pragma once

#include "Brush.h"

class BrushBox : public Brush
{
private:
	sf::Vector2f* start;
public:
	BrushBox();
	~BrushBox();
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer);
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer);
	virtual void MouseUp(const sf::Vector2f& position, Layer& layer);
};
