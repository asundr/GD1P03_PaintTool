// Loads an image of the colour spectrum and allows the user to select
// a pixel, returning the corresponding color

#pragma once

#include "SFML/Graphics.hpp"

class ColorSelector
{
private:
	sf::RenderWindow* window;
	sf::Texture* colorTex;
	sf::Sprite* sprite;
public:
	ColorSelector();
	~ColorSelector();
	bool IsOpen() const;
	sf::Color SelectColor(const sf::Color& currColor) const;
};
