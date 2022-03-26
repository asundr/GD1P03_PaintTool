#include "BrushMove.h"
#include "BrushPencil.h"
#include "BrushLine.h"
#include "BrushBox.h"
#include "BrushEllipse.h"
#include "BrushPolygon.h"
#include "BrushStamp.h"
#include "BrushFill.h"

#include "InputManager.h"
#include "ToolManager.h"

ToolManager::ToolManager() : selectedBrush(0), size(5)
{
	if (!font.loadFromFile("FreeSans.otf"))
	{
	}
	brushes.push_back(new BrushMove()	);	
	brushes.push_back(new BrushPencil()	);
	brushes.push_back(new BrushLine()	);	
	brushes.push_back(new BrushBox()	);	
	brushes.push_back(new BrushEllipse());	
	brushes.push_back(new BrushPolygon());	
	brushes.push_back(new BrushStamp());
	brushes.push_back(new BrushFill()	);	
	InitializeUI();
	toolbarView = sf::View(sf::FloatRect(0, 0, 150, 50.f * toolCount));
	SelectBrush(Brush::Type::PENCIL);
	SetSize(5);
	SetColor(sf::Color::Black);
}

ToolManager::~ToolManager()
{
	for (Brush* brush : brushes)
	{
		delete brush;
	}
	for (sf::Shape* button : buttons)
	{
		delete button;
	}
	for (sf::Text* text : textBoxes)
	{
		delete text;
	}
}

void ToolManager::SetSize(float size)
{
	this->size = fmaxf(size, 1.f);
	selectedBrush->SetSize(size);
	textBoxes[8]->setString("Size: " + std::to_string((int)size));
}

void ToolManager::SetColor(sf::Color color)
{
	this->color = color;
	selectedBrush->SetColor(color);
	buttons[9]->setFillColor(color);
}

float ToolManager::GetSize() const
{
	return size;
}

sf::Color ToolManager::GetColor() const
{
	return color;
}

Brush& ToolManager::GetCurrentBrush()
{
	return *selectedBrush;
}

void ToolManager::SelectBrush(Brush::Type type)
{
	int index = (int)type;
	selectedBrush = brushes[index];
	sf::Color grey = sf::Color(50, 50, 50, 255), dgrey = sf::Color(25, 25, 25, 255);
	if (index < 8)
	{
		for (int i = 0; i < 8; ++i)
		{
			buttons[i]->setFillColor(grey);
		}
		buttons[index]->setFillColor(dgrey);
		selectedBrush->SetColor(color);
		selectedBrush->SetSize(size);
	}
}

#include <iostream> // TODO remove
void ToolManager::HandleMenuEvent(sf::Event event, const sf::Vector2f& position)
{
	int index = 0;
	for (; index < toolCount; ++index)
	{
		if (buttons[index]->getGlobalBounds().contains(position))
		{
			break;
		}
	}
	if (index == toolCount)
	{
		return;
	}

	
	std::cout <<  index << std::endl;

	if (event.type == sf::Event::MouseButtonReleased)
	{
		switch (index)
		{
		case 0: case 1: case 2: case 3: case 4: case 5:	case 6: case 7:
			// if mousedown
			SelectBrush((Brush::Type)index);
			break;
		case 9:
			// color selector
			break;
		case 10:
			// load 
			break;
		case 11:
			// save
			break;
		}
	}

	if (index == 8 && event.type == sf::Event::MouseWheelScrolled
			&& event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		SetSize(size + event.mouseWheelScroll.delta);
	}

}

void ToolManager::DisplayUI(sf::RenderWindow& window) const
{
	sf::View documentView = window.getView();
	window.setView(toolbarView);
	//(window.getDefaultView());
	for (int i = 0; i < toolCount; ++i)
	{
		window.draw(*buttons[i]);
		window.draw(*textBoxes[i]);
		//sf::Text label();

		
	}
	//window.display();
	window.setView(documentView);
}

bool ToolManager::IsInBounds(const sf::Vector2f mousePos) const
{
	//sf::Vector2f bounds = toolbarView.getSize();
	sf::FloatRect rect(sf::Vector2f(0, 0), toolbarView.getSize());
	return rect.contains(mousePos);
}


void ToolManager::InitializeUI()
{
	float buttonWidth = 150.f, buttonHeight = 50.f;
	sf::Color grey(50, 50, 50, 255),  lgrey(200, 200, 200, 255);

	for (int i = 0; i < toolCount; ++i)
	{
		sf::RectangleShape* button = new sf::RectangleShape();
		button->setSize(sf::Vector2f(150.f, 50.f));
		button->setPosition(sf::Vector2f(0.f, i * 50.f));
		button->setFillColor(grey);
		button->setOutlineColor(lgrey);
		button->setOutlineThickness(1.f);
		buttons.push_back(button);
	}

	static const char* labels[] = { "Move", "Pencil", "Line", "Box", "Ellipse", "Polygon",
	   "Stamp", "Fill", "Thickness", "Colour",  "Load", "Save" };

	
	for (int i = 0; i < toolCount; ++i)
	{
		sf::Text* labelText = new sf::Text();
		labelText->setFont(font);
		labelText->setFillColor(sf::Color::White);
		labelText->setCharacterSize(25);
		labelText->setPosition(sf::Vector2f(10.f, 10.f + i * 50.f));
		labelText->setString(labels[i]);
		textBoxes.push_back(labelText);
	}
}

void ToolManager::UpdateView(sf::RenderWindow& window)
{
	UpdateView(window.getSize().x, window.getSize().y);
}

void ToolManager::UpdateView(unsigned int width, unsigned int height)
{
	float toolbarHeight = 50.f * toolCount;
	toolbarView.setViewport(sf::FloatRect(0.f, 0.f, 150.f / width, toolbarHeight / height));
}