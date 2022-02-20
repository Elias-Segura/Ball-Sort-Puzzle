#pragma once
#include "stack.h"
#include "space_stack.h"
#include "Element_stack.h"
extern struct Tube {
		Sprite* tube{};
		stack<Element_stack> stack{ 4 };
		space_stack space{ 5 };
		bool state{ false }; 
		bool Up{ false };
};