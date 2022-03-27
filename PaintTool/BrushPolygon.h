#pragma once

#include "Brush.h"

class BrushPolygon : public Brush
{
private:
	std::vector<sf::Vector2f> points;
public:
	BrushPolygon();
	~BrushPolygon();
	// Inherited via Brush
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer) override;
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer) override;
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer) override;
};
