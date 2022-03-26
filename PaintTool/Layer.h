#pragma once

#ifndef __LAYER_H__
#define __LAYER_H__

#include "SFML/Graphics.hpp"

class Canvas;

class Layer : public sf::Drawable //, public sf::Transformable // TODO
{
private:
	//sf::FloatRect bounds;
	sf::Sprite* sprite;
	sf::RenderTexture* rTexture;
public:
	Layer(unsigned int width, unsigned int height);
	Layer(Canvas& canvas);
	Layer(Canvas& canvas, const std::string path);
	~Layer();
	const sf::Vector2f& GetPosition() const;
	const sf::Vector2u& GetSize() const;
	const sf::Image CopyToImage() const;
	void move(const sf::Vector2f& offset);
	void SetPosition(const sf::Vector2f& position);
	void UpdateRenderTexture();
	void Clear();
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//void updatePositions();
	//void updateTexCoords();
	//operator sf::Drawable&();
};

#endif //__LAYER_H__
