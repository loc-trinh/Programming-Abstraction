/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Random Writer problem.
 * The program is a random writer is designed to produce somewhat sensible output by
 * generalizing from patterns found in the input text.
 */

#include <iostream>
#include <string>
#include <fstream>

#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"
#include "console.h"


using namespace std;

/* Main program */
int main() {
    ifstream source;
	string filename;
	int seed;

/* Display interface and asking for filename and seed number */
	while(true){
		filename = getLine("Enter the source text: ");
		source.open(filename.c_str());
		if(source.fail()) {cout << "ERROR: file can't open!\n"; source.clear();} 
		else{ 
			while(true){
			seed = getInteger("Enter the Markov order [1-10]: ");
			if(seed > 10 || seed < 1) cout << "ERROR: invalid order!\n"; else break;}
			break;
		}}

/* Main alorithm to read the data and add to ADT
 * ADT: Map with seed string as keyword and vector to store possible following characters
 */
	char ch;
	Map<string, Vector<char> > data;
	cout << "Processing file..." << endl;

	while(source.get(ch)) {
		string key;
		key += ch;
		int i = 0;
		while(source.get(ch)){
			i++;
			if(i == seed) {data[key].add(ch); break;}
			key += ch;}
		for(i; i > 0; i--)
			source.unget();
	}


/* Determining the initial seed which most frequently appear in the source */
	int max = 0;
	string seeds;
	foreach(string key in data){
		if(data[key].size() > max){
			max = data[key].size();
			seeds = key;
		}
	}

/* Randomly output 2000 characters of random text generated from the model */
	cout << seeds;
	for( int count = 0; (data.containsKey(seeds)) && count < 2000; count++)
	{
		char nextch = data[seeds][randomInteger(0,data[seeds].size() - 1)]; //chose a character to from data[key] vector
		cout << nextch;
		seeds = seeds.substr(1) + nextch; //update the seeds string by remove first character and add nextch
	}
	cout << endl;
	return 0;
}