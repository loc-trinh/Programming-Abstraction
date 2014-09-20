/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while(head != NULL){
		Cell* save = head->next;
		delete head;
		head = save;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	int count = 0;
	for(Cell* cur = head; cur != NULL; cur = cur->next)
		count++;
	return count;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return (head == NULL);
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Cell* newOne = new Cell;
	newOne->value = value;
	newOne->prev = NULL;
	newOne->next = head;
	if(!isEmpty())
		head->prev = newOne;
	head = newOne;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty())
		error("Empty queue");
	else{
		Cell* minCell = head;
		for(Cell* cur = head; cur != NULL; cur = cur->next)
			if(cur->value < minCell->value) 
				minCell = cur;
		return minCell->value;
	}

}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(isEmpty())
		error("Empty queue");
	else{
		Cell* minCell = head;
		for(Cell* cur = head; cur != NULL; cur = cur->next)
			if(cur->value < minCell->value) 
				minCell = cur;

		string word = minCell->value;
		if(minCell == head)
			head = minCell->next;
		else{
			if(minCell->next != NULL)
				(minCell->next)->prev = minCell->prev;
			if(minCell->prev != NULL)
				(minCell->prev)->next = minCell->next;
		}
		delete minCell;
		return word;
	}
}

