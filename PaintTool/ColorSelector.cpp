#include "ColorSelector.h"

ColorSelector::ColorSelector()
{
	colorTex = new sf::Texture();
	if (!colorTex->loadFromFile("color_img.png"))
	{
	}
	window = new sf::RenderWindow(sf::VideoMode(239, 220), "Colour Selector", sf::Style::Close);
	sprite = new sf::Sprite(*colorTex);
	window->draw(*sprite);
}

ColorSelector::~ColorSelector()
{
	delete sprite;
	delete window;
	delete colorTex;
}

bool ColorSelector::IsOpen() const
{
	return false;
}

sf::Color ColorSelector::SelectColor(const sf::Color& currColor) const
{
	window->display();
	window->requestFocus();
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return currColor;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2i pos =  sf::Mouse::getPosition(*window);
				window->close();
				return colorTex->copyToImage().getPixel(pos.x, pos.y);
			}
		}
	}
	return currColor;
}
