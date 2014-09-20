/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	arry = new string[10];
	numAllocated = 10;
	numUsed = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] arry;
}

int HeapPriorityQueue::size() {
	return numUsed;
}

bool HeapPriorityQueue::isEmpty() {
	return (numUsed == 0);
}

void HeapPriorityQueue::Swap(string& cell1, string& cell2) {
	string temp = cell1;
	cell1 = cell2;
	cell2 = temp;
}

void HeapPriorityQueue::bubbleUp(int index){
	int parent;
	
	if(index == 0) return;
	else if(index%2 == 0) parent = index/2-1;
	else parent = index/2;
	
	if(arry[index] < arry[parent]) Swap(arry[index], arry[parent]);
	else return;

	bubbleUp(parent);
}

void HeapPriorityQueue::bubbleDown(int index){
	int child, child1 = index*2+1, child2 = index*2+2;
	
	if(child1 >= size() && child2 >= size()) return;
	else if(child1 < size() && child2 >= size()) child = child1;
	else if(child1 >= size() && child2 < size()) child = child2;
	else{
		if(arry[child1] <= arry[child2]) child = child1;
		else child = child2;
	}
	
	if(arry[child] < arry[index]) Swap(arry[child], arry[index]);
	else return;

	bubbleDown(child);
}

void HeapPriorityQueue::enqueue(string value) {
	if(numUsed == numAllocated)
		expandArry();
	arry[numUsed++] = value;
	bubbleUp(numUsed-1);
}

void HeapPriorityQueue::expandArry() {
	string *newArry = new string[numAllocated*2];
	for(int i = 0; i < numUsed; i++)
		newArry[i] = arry[i];
	delete[] arry;
	arry = newArry;
	numAllocated *= 2;
}


string HeapPriorityQueue::peek() {
	if(isEmpty())
		error("empty queue");
	else
		return arry[0];
}

string HeapPriorityQueue::dequeueMin() {
	if(isEmpty())
		error("empty queue");
	else{
		string word = arry[0];
		Swap(arry[0], arry[size()-1]);
		numUsed--;
		bubbleDown(0);
		return word;
	}
}

