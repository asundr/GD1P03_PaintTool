// Class that manages Windows save and load dialogues

#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <Windows.h>
#include <commdlg.h>

class WindowsHelper
{
public:

	OPENFILENAME currFileName;
	char szFile[100];
	sf::String SaveFile();
	sf::String LoadFile();
	void Setup();
};

