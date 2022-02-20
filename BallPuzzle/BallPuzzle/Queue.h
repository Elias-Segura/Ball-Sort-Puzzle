#pragma once
extern struct Queue {
	int id; 
	int lastId;
	int newId;
	bool state{ false };
	Queue* next;
};