/**
 * File: path.cpp
 * --------------
 * This file implements the Path class.
 */

#include "path.h"

Path::Path(){
	cost = 0;
}

Path::~Path(){
}

void Path::add(Arc *newArc){
	route.add(newArc);
	cost += newArc->cost;
}

void Path::remove(int index){
	if(index < route.size()){
	cost -= route[index]->cost;
	route.remove(index);
	}
	else error("index out of bounds");
}

int Path::size(){
	return route.size();
}

void Path::clear(){
	route.clear();
	cost = 0;
}

bool Path::isEmpty(){
	return (size() == 0);
}

double Path::getCost(){
	return cost;
}

Vector<Arc *> Path::getPath(){
	Vector<Arc *> path = route;
	return path;
}
	
string Path::toString(){
	string line;
	int i;
	if(!isEmpty()){
	line = route[0]->start->name;
	for( i = 1; i < route.size(); i++)
		line += (" -> " + route[i]->start->name);
	}
	line += (" -> " + route[i-1]->finish->name);
	return line;
}