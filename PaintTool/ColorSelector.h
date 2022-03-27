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
	void SetVisible(bool visible = true);
	bool IsOpen() const;
	sf::Color SelectColor(sf::Color& currColor) const;
};
