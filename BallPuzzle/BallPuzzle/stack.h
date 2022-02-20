#pragma once
#include "array_stack.h"
#include "StackOverFlow.h"
#include <iostream>
using namespace std; 
template<typename T>
class stack
{
private: 
	array_stack<T> sprites; 
	int top; 
public: 
	stack() = default;
	explicit stack(int size)
		:sprites{ size }, top{ -1 }
	{}
	void Push(const T& element) {
		
		if (Size() >= maxSize()) {
			throw StackOverflowException{};
		}
		top++;
		
		sprites[top] = element;
	}
	 T Pop() {
		T TopSprite = sprites[top];
		top--;
		return TopSprite;
	}

	T& Top() {
		return sprites[top];
	}
	bool isEmpty() {
		return (Size() == 0);
	}
	bool isFull() {
		return (Size() >= maxSize());
	}
	int Size() {
		return (top + 1);
	}

	int maxSize() {
		return sprites.Size();
	}

};

