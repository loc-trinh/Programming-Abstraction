/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Subsequences problem
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence)
{
	if(subsequence.size() == 0) return true;
	else
	{	
		int i;
		if((i = text.find(subsequence[0])) != string::npos)
			return isSubsequence(text.substr(i+1), subsequence.substr(1));
		else
			return false;
	}
}


int main() {
	while(true){
	string word = getLine("Enter the first string: ");
	if(word == "") {cout << "Goodbye!" << endl; break;}
	string word1 = getLine("Enther the second string: ");
	if(isSubsequence(word, word1)) cout << "The second string is a subsequence of the first" << endl << endl;
	else cout << "The second is not a subquence of the first" << endl << endl;;
	}
	return 0;
}
