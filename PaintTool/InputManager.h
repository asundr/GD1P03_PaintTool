#pragma once

#include "SFML/Graphics.hpp"

class InputManager
{
private:
	static bool LAlt;
	static bool RAlt;
	static bool LControl;
	static bool RControl;
	static bool LShift;
	static bool RShift;
public:
	InputManager();
	~InputManager();
	static void UpdateState(sf::Event& event);
	static void UpdateButtonState(sf::Event& event, bool& state, sf::Keyboard::Key key);
	static bool ShiftPressed();
	static bool ControlPressed();
	static bool AltPressed();
	static bool MouseLeftPressed();
};
