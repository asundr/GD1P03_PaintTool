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
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer);
private:
	void DrawBox(const sf::Vector2f& position, Layer& layer) const;
};
