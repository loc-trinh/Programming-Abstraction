/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
using namespace std;

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
Set<int> randomSubsetOf(Set<int>& s){
	Set<int> sub;
	if(s.size() == 0) return sub;
	else
		if(randomChance(.5)){
			sub.add(s.first());
			s.remove(s.first());
			return sub + randomSubsetOf(s);}
		else{
			s.remove(s.first());
			return sub + randomSubsetOf(s);}
}

/* Main Program */
int main() {
	Set<int> sub;
	for(int i = 0; i < 10; i++)
		sub.add(i);
	cout << sub << endl;
	sub =  randomSubsetOf(sub);
	cout << sub << endl;

    return 0;
}
