#pragma once

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <vector>
#include <string>
#include "SFML/Graphics.hpp"

class Layer;

class Canvas
{
private:
	unsigned int width;
	unsigned int height;
	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::RenderTexture* rTexture;

public:
	Canvas(int width, int height);
	~Canvas();
	unsigned int Width() const;
	unsigned int Height() const;
	sf::RenderTexture* RenderTexture();
	sf::Sprite* Sprite();
	void Resize(int newWidth, int newHeight);
	void clear();
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
	void Save(const std::vector<Layer*>& layers, std::string path);
};

#endif //__CANVAS_H__
