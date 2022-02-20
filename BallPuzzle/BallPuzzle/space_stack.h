#pragma once
#include <SFML/Graphics.hpp>
#include "IndexOutOfBoundsException.h"
using namespace sf; 

class space_stack
{
private: 
	
	RectangleShape* rec{ nullptr }; 
	int _size{ 0 }; 
	bool isValidIndex(int index) const {
		return (index >= 0) && (index < _size);
	}
public: 


	
	space_stack() = default;
	explicit space_stack(int size) {
		if (size != 0) {
			rec = new RectangleShape[size]{};
			_size = size;
		}
	}
	~space_stack();

	int getSize();

	bool isEmpty();
	RectangleShape & operator[](int index) {
		if (!isValidIndex(index)) {
			throw IndexOutOfBoundsException{};
		}
		return rec[index];
	}

};

