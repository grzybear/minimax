#include "Queue.h"

Queue::Queue() : size(0) {
	first = (Element*)malloc(sizeof(Element));
	first->map = nullptr;
	first->next = nullptr;
	last = first;
}
Queue::~Queue() {
	Element* element = first;
	while (element != nullptr) {
		Element* toDelete;
		toDelete = element;
		element = element->next;
		if (toDelete->map != nullptr)free(toDelete->map);
		free(toDelete);
	}
}
void Queue::Add(Map* map) {
	Element* newElement = (Element*)malloc(sizeof(Element));
	newElement->map = new Map(map);
	newElement->next = nullptr;
	last->next = newElement;
	last = last->next;
	size++;
}
Map* Queue::Pop() {
	if (first->next == nullptr) {
		return nullptr;
	}
	else {
		Element* toDelete = first->next;
		Map* toReturn = toDelete->map;
		first->next = toDelete->next;
		free(toDelete);
		size--;
		return toReturn;
	}
}
void Queue::Print() {
	Element* element = first->next;
	printf("%d\n", size);
	while (element != nullptr) {
		element->map->Print();
		printf("\n");
		element = element->next;
	}
}