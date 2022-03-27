// Contains a Rendertexture that allows it to be drawn onto
// Is also able to be drawn to other RenderTargets by inheriting from
// sf::Drawable and using a sprite that contians the RenderTexture

#pragma once

#ifndef __LAYER_H__
#define __LAYER_H__

#include "SFML/Graphics.hpp"

class Canvas;

class Layer : public sf::Drawable
{
private:
	sf::Sprite* sprite;
	sf::RenderTexture* rTexture;
	bool hidden;
public:
	Layer(unsigned int width, unsigned int height);
	Layer(Canvas& canvas);
	Layer(Canvas& canvas, const std::string path);
	~Layer();
	const sf::Vector2f& GetPosition() const;
	sf::Vector2u GetSize() const;
	const sf::Image CopyToImage() const;
	const sf::Texture& GetTexture() const;
	void SetHidden(bool hidden = true);
	void move(const sf::Vector2f& offset); // sets position relative to current
	void SetPosition(const sf::Vector2f& position);
	void UpdateRenderTexture();
	void Clear();
	// Used to draw other drawables onto this layer
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
private:
	// Used to draw onto other render targets
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //__LAYER_H__
