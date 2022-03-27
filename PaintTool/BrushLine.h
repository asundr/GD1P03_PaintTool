#pragma once
#include "Brush.h"

class BrushLine : public Brush
{
protected:
	sf::Vector2f* start;
public:
	BrushLine();
	~BrushLine();
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer);
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer);
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer);
private:
	sf::CircleShape MakeLineEnds() const;
};
