/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Consecutive Heads problem.
 * The program will simulate a coin toss until three heads are consecutively tossed.
 * Until then, the number of tosses are reported.
 */

#include <iostream>
#include "random.h"
#include "console.h"
using namespace std;

int main() {
	int count = 0, total = 0;

	while(count != 3){
		if(randomChance(.5)){
			cout << "heads" << endl;
			count++;}
		else{
			cout << "tails" << endl;
			count = 0;}
		total++;
	
	}
    cout <<  "It took " << total << " flips to get 3 consecutive heads" << endl;
    return 0;
}
