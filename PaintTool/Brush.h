#pragma once

#include "SFML/Graphics.hpp"
#include "InputManager.h"

class Layer;

class Brush
{
	enum Type
	{
		GRAB,
		PENCIL,
		LINE,
		BOX,
		ELLIPSES,
		POLYGON,
		FILL
	};
private:
	//Type type; //TODO unused
protected:
	sf::Color color;
	int size;
	Layer* overlay;
public:
	Brush(int size = 10, sf::Color = sf::Color::Black);
	~Brush();
	void SetColor(const sf::Color color);
	void SetSize(int size);
	const sf::Color& GetColor() const;
	int GetSize() const;
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer) = 0;
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer) = 0;
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer) = 0;
protected:
	static sf::Vector2f Subtract(const sf::Vector2f& a, const sf::Vector2f& b);
	void DrawLine(const sf::Vector2f& a, const sf::Vector2f& b, Layer& layer, sf::Shape& shape);
};

