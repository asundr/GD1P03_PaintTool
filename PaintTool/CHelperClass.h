#pragma once
// From class

#include "SFML/Graphics.hpp"
#include <iostream>
#include <Windows.h>
#include <commdlg.h>

class CHelperClass
{
public:

	OPENFILENAME currFileName;
	
	char szFile[100];

	template<typename T>
	static T MaxValue(T x, T y)
	{
		std::cout << sizeof(x) << ", " << sizeof(y) << std::endl;
		return (x > y) ? x : y;
	}

	sf::String SaveFile();
	sf::String LoadFile();
	void Setup();
};

