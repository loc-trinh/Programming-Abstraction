/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Sierpinski problem
 * A program that asks the user for an edge length and a fractal order and draws the resulting 
 * Sierpinski Triangle in the center of the graphics window.
 */

#include <iostream>
#include <math.h>
#include "simpio.h"
#include "gwindow.h"


using namespace std;

/* Constants */
const double wSize = 400; // window-size

/* drawTriangle function 
 * -------------------------------------------
 * Helper function provide clarity.
 * Draw three segments to form a triangle
 */

void drawTriangle(GWindow& gw, double x, double y, double length)
{
	GPoint pt(x, y); //pt used as starting point and endpoint of last drawn line
	pt = gw.drawPolarLine(pt, length, 60);
	pt = gw.drawPolarLine(pt, length, -60);
	pt = gw.drawPolarLine(pt, length, 180);
}


/* Recursive drawSierpinkski function 
 * ---------------------------------------------
 * When base case/ 0-order is reach, draw a triangle
 * Recursively called the drawing of the left, then right, then top triangles of the fractals
 */
void drawSierpinski(GWindow& gw, double x, double y, double length, double height, int n)
{
	if(n == 0) drawTriangle(gw, x, y, length); // base case
	else
	{
		drawSierpinski(gw, x, y, length/2, height/2, n - 1); // left recursive of n-1 order
		drawSierpinski(gw, x + length/2, y, length/2, height/2, n - 1); // right
		drawSierpinski(gw, x + length/4, y - height/2, length/2, height/2, n - 1); // top
	}
}

/* Main Program */
int main() {
	GWindow gw(wSize, wSize); //set up a square window, sized must be pre-set and not by user-input
	while(true){
		double length = getReal("Enter a length: ");
		double height = length/2.0 * sqrt(3.0); // height provided for positioning
												// height of equilateral triangle = half-side * rad(3)
		if(length == 0) { gw.close(); break; }
		int n = getInteger("Enter the order: ");

		gw.clear();
		// Added padding to centralized the Sierpinski triangle
		drawSierpinski(gw, 0 + (wSize - length)/2, wSize - (wSize-height)/2, length, height, n);
	}
	
    return 0;
}
