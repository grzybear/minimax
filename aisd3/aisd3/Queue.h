#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Map.h"

struct Element {
	Map* map;
	Element* next;
};

class Queue
{
private:
	Element* first;
	Element* last;
	int size;
public:
	Queue();
	~Queue();
	void Add(Map* map);
	Map* Pop();
	void Print();
};

