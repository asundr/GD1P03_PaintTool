// Abstract base class used for all brushes

#pragma once

#include "SFML/Graphics.hpp"
#include "InputManager.h"

class Layer;
class Canvas;

class Brush
{
public:
	enum class Type
	{
		GRAB,
		PENCIL,
		LINE,
		BOX,
		ELLIPSE,
		POLYGON,
		STAMP,
		FILL
	};
protected:
	sf::Color color;
	float size;
	Layer* overlay;
	static const Canvas* canvas;
public:
	Brush(int size = 10, sf::Color = sf::Color::Black);
	~Brush();
	virtual void SetColor(const sf::Color color);
	void SetSize(float size);
	const sf::Color& GetColor() const;
	int GetSize() const;
	static void SetCanvas(const Canvas* canvas);

	// These three functions are used by the child classes to draw to layers
	// and to provide a preview of the tool during use
	virtual void MouseDown(const sf::Vector2f& position, Layer& layer) = 0;
	virtual Layer* Update(const sf::Vector2f& position, Layer& layer) = 0;
	virtual Layer* MouseUp(const sf::Vector2f& position, Layer& layer) = 0;
protected:
	static sf::Vector2f Subtract(const sf::Vector2f& a, const sf::Vector2f& b);
	void DrawLine(const sf::Vector2f& a, const sf::Vector2f& b, Layer& layer, sf::Shape& shape);
};
