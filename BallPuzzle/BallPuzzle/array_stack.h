#pragma once
#include <SFML/Graphics.hpp>
#include "IndexOutOfBoundsException.h"
using namespace sf; 
using namespace std;

template<typename T>
class array_stack
{
private:
	T* m_ptr{ nullptr };
	int m_size{ 0 };
	bool IsValidIndex(int index) const {
		return (index >= 0) && (index < m_size);
	}
public:
	array_stack() = default;

	explicit array_stack(int size) {
		if (size != 0) {
			m_ptr = new T[size]{};
			m_size = size;
		}
	}

	~array_stack() {
		delete[] m_ptr;
	}
	int Size() const {
		return m_size;
	}

	bool IsEmpty() const {
		return (m_size == 0);
	}
	array_stack(const array_stack& source) {
		if (!source.IsEmpty()) {
			m_size = source.m_size;
			m_ptr = new T[m_size]{};
			for (int i = 0; i < m_size; i++) {
				m_ptr[i] = source.m_ptr[i];
			}

		}
	}
	T& operator[](int index) {
		if (!IsValidIndex(index)) {
			throw IndexOutOfBoundsException{};
		}
		return m_ptr[index];
	}

};
