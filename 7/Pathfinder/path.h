/*
 * File: path.h
 * ------------
 * This file is the interface for a Path class, which consists of a
 * sequence of arcs.
 */

#ifndef _path_h
#define _path_h
#include "vector.h"
#include "graphtypes.h"
#include "error.h"

class Path {
public:
	Path();
	~Path();

	void add(Arc *newArc);
	void remove(int index);
	int size();
	bool isEmpty();
	void clear();

	double getCost();
	Vector<Arc *> getPath();
	string toString();

private:
	Vector<Arc *> route;
	double cost;
};
#endif
