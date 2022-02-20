#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;
extern struct Element_stack {
	Sprite* mysprite{};
	int color{0};
	Vector2f lastPos; 
	Vector2f Origen; 
};

