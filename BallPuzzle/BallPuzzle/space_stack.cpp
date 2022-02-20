#include "space_stack.h"
space_stack::~space_stack() {
	delete[] rec;
}
int space_stack::getSize() {
	return _size;
}
bool space_stack::isEmpty() {
	return (_size == 0);
}