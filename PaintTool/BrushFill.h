#pragma once

#include "Brush.h"

class BrushFill : public Brush
{
	// Inherited via Brush
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer) override;
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer) override;
	virtual void MouseUp(const sf::Vector2f& position, Layer& layer) override;
};

