#pragma once

#include "SFML/Graphics.hpp"
#include "Brush.h"

class Canvas;

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
	std::string filePath;
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
	void SaveAs(Canvas& canvas, std::vector<Layer*>& layers);
	void HandleMenuEvent(sf::Event event, Canvas& canvas, std::vector<Layer*>& layers, const sf::Vector2f& position);
	void HandleKeyEvent(sf::Event event, Canvas& canvas, std::vector<Layer*>& layers);
	void Save(Canvas& canvas, std::vector<Layer*>& layers);
	std::string GetLoadString();
	void LoadLayer(Canvas& canvas, std::vector<Layer*>& layers);
	void UpdateView(sf::RenderWindow& window);
	void UpdateView(unsigned int width, unsigned int height);
	void DisplayUI(sf::RenderWindow& window) const;
private:
	void SetupBrushStamp();
	void InitializeUI();
};

