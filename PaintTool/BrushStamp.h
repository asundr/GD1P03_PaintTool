#pragma once

#include "Brush.h"

class BrushStamp : public Brush
{
private:
	sf::Sprite* sprite;
	sf::Texture* texture;
public:
	BrushStamp();
	~BrushStamp();
	void LoadFromFile(std::string path);
	const sf::Texture& GetTexture() const;
	bool HasSprite() const;
	// Inherited via Brush
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer) override;
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer) override;
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer) override;

};

