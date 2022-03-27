// Handles menu interraction and updates the brushes

#pragma once

#include "SFML/Graphics.hpp"
#include "Brush.h"

class Canvas;

class ToolManager
{
private:
	static const int toolCount = 15;
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
	ToolManager(const Canvas* canvas = nullptr);
	~ToolManager();
	void SetSize(float size);
	void SetColor(sf::Color color);
	Brush& GetCurrentBrush();
	float GetSize() const;
	sf::Color GetColor() const;
	// checks if the point is inside the menu
	bool IsInBounds(const sf::Vector2f position) const;
	void SelectBrush(Brush::Type type);
	void OpenColorWindow();
	void SaveAs(Canvas& canvas, std::vector<Layer*>& layers);
	void Save(Canvas& canvas, std::vector<Layer*>& layers);
	// gets path of file from windows load dialogue
	std::string GetLoadString();
	void LoadLayer(Canvas& canvas, std::vector<Layer*>& layers, int& focusLayer);
	// Next two functions interpret mouse and keyboard input
	void HandleMenuEvent(sf::Event event, Canvas& canvas, int& focusLayer, std::vector<Layer*>& layers, const sf::Vector2f& position);
	void HandleKeyEvent(sf::Event event, Canvas& canvas, std::vector<Layer*>& layers);
	// Maintains the scale of the menu
	void UpdateView(sf::RenderWindow& window);
	void UpdateView(unsigned int width, unsigned int height);
	// Draws the menu to the passed window
	void DisplayUI(sf::RenderWindow& window) const;
private:
	void SetupBrushStamp();
	void InitializeUI();
	void UpdateLayerButton(int currLayer, int totalLayers);
	void AddLayerToIndex(Canvas& canvas, std::vector<Layer*>& layers, int index, Layer* layer = nullptr);
	void DeleteLayerAtIndex(std::vector<Layer*>& layers, int index);
};

