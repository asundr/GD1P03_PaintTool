#pragma once

#include "SFML/Graphics.hpp"
#include "Brush.h"

class ToolManager
{
private:
	static const int toolCount = 12;
	std::vector<Brush*> brushes;
	std::vector<sf::Shape*> buttons;
	std::vector<sf::Text*> textBoxes;
	Brush* selectedBrush;
	float size;
	sf::Color color;
	sf::View toolbarView;
	sf::Font font;
public:
	ToolManager();
	~ToolManager();
	void SetSize(float size);
	void SetColor(sf::Color color);
	Brush& GetCurrentBrush();
	float GetSize() const;
	sf::Color GetColor() const;
	bool IsInBounds(const sf::Vector2f position) const;
	void SelectBrush(Brush::Type type);
	void HandleMenuEvent(sf::Event event, const sf::Vector2f& position);
	void UpdateView(sf::RenderWindow& window);
	void UpdateView(unsigned int width, unsigned int height);
	void DisplayUI(sf::RenderWindow& window) const;
private:
	void InitializeUI();
};
