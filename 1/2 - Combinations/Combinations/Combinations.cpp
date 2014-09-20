/*
 * File: Combinations.cpp
 * ----------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Combinations problem.
 * This is a recursive implementation of the combination fuction
 * and print the first 10 lines of the Pascal's Triangle.
 */

#include <iostream>
#include <iomanip>
#include "console.h"
using namespace std;

int c(int n, int k);

int main() {
	cout << "Pascal's Triangle using Recursive Combination" << endl;
	for(int i = 0; i < 16; i++){
		for(int j = 0; j <= i; j++)
			cout << setw(6) << left << c(i,j); //left-justify flag; member of std
		cout << endl;
	}    
    return 0;
}

/* Combination Function
 * -------------------------------
 * return: recursive calls to two entry above it
 * base case: left & right edges = 1 
 */
int c(int n, int k){
	if(k == 0 || n == k)
		return 1;
	else
		return c(n-1,k-1) + c(n-1, k);
}
