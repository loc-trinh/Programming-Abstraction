/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	//vector-automatic
}

VectorPriorityQueue::~VectorPriorityQueue() {
	//vector-automatic
}

int VectorPriorityQueue::size() {
	return queue.size();
}

bool VectorPriorityQueue::isEmpty() {
	return (queue.size() == 0);
}

void VectorPriorityQueue::enqueue(string value) {
	queue.add(value);
}

string VectorPriorityQueue::peek() {
	int minIndex = 0;
	for(int i = 0; i < queue.size(); i++)
		if(queue[i] < queue[minIndex])
			minIndex = i;
	return queue[minIndex];
}

string VectorPriorityQueue::dequeueMin() {
	int minIndex = 0;
	for(int i = 0; i < queue.size(); i++)
		if(queue[i] < queue[minIndex])
			minIndex = i;
	string word = queue[minIndex];
	queue.remove(minIndex);
	return word;
}

