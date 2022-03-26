#pragma once

#include "Brush.h"

class BrushEllipse : public Brush
{
private:
	sf::Vector2f* start;
public:
	BrushEllipse();
	~BrushEllipse();
	// Inherited via Brush
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer) override;
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer) override;
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer) override;
};

