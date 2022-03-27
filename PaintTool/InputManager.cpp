// Static class used to provide reliable user input

#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::UpdateState(sf::Event& event)
{
	UpdateButtonState(event, LAlt, sf::Keyboard::LAlt);
	UpdateButtonState(event, RAlt, sf::Keyboard::RAlt); 
	UpdateButtonState(event, LControl, sf::Keyboard::LControl);
	UpdateButtonState(event, RControl, sf::Keyboard::RControl);
	UpdateButtonState(event, LShift, sf::Keyboard::LShift);
	UpdateButtonState(event, RShift, sf::Keyboard::RShift);
}

void InputManager::UpdateButtonState(sf::Event& event, bool& state, sf::Keyboard::Key key)
{
	state = sf::Keyboard::isKeyPressed(key);
}

bool InputManager::ShiftPressed()
{
	return LShift || RShift;
}

bool InputManager::ControlPressed()
{
	return LControl || RControl;
}

bool InputManager::AltPressed()
{
	return LAlt || RAlt;
}

bool InputManager::MouseLeftPressed()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool InputManager::LAlt = false;
bool InputManager::RAlt = false;
bool InputManager::LControl = false;
bool InputManager::RControl = false;
bool InputManager::LShift = false;
bool InputManager::RShift = false;
