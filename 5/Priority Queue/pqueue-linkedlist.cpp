/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while(head != NULL){
		Cell* save = head->next;
		delete head;
		head = save;
	}
}

int LinkedListPriorityQueue::size() {
	int count = 0;
	for(Cell* cur = head; cur != NULL; cur = cur->next)
		count++;
	return count;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (head == NULL);
}

void LinkedListPriorityQueue::enqueue(string value) {
	Cell *cur, *prev = NULL, *newOne = new Cell;
	newOne->value = value;
	for(cur = head; cur != NULL; cur = cur->next){
		if(newOne->value < cur->value) break;
		prev = cur;
	}
	newOne->next = cur;
	if(prev == NULL)
		head = newOne;
	else
		prev->next = newOne;
	
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty())
		error("Empty queue");
	else
		return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(isEmpty())
		error("Empty queue");
	else{
	string value = head->value;
	Cell* rm = head;
	head = head->next;
	delete rm;
	return value;
	}
}

