#include "Layer.h"
#include "Canvas.h"
#include "BrushBox.h"

BrushBox::BrushBox() : start(0)
{
}

BrushBox::~BrushBox()
{
	delete start;
}

void BrushBox::MouseDown(const sf::Vector2f& position, Layer& layer)
{
	delete start;
	start = new sf::Vector2f(position);
	delete overlay;
	overlay = new Layer(canvas->Width(), canvas->Height());
}

Layer* BrushBox::Update(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		MouseDown(position, layer);
		return nullptr;
	}
	overlay->Clear();
	DrawBox(position, *overlay);
	return overlay;
}

Layer* BrushBox::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	if (start == 0)
	{
		return nullptr;
	}
	DrawBox(position, layer);
	delete start;
	start = 0;
	delete overlay;
	overlay = 0;
	return nullptr;
}

void BrushBox::DrawBox(const sf::Vector2f& position, Layer& layer) const
{
	sf::Vector2f dif = Subtract(position, *start);
	sf::Vector2f origin = sf::Vector2f(fminf(start->x, position.x), fminf(start->y, position.y));
	sf::RectangleShape box;
	box.setOutlineColor(color);
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineThickness(size);
	box.setPosition(origin);
	box.setSize(sf::Vector2f(fabsf(dif.x), fabsf(dif.y)));
	layer.draw(box);
}
