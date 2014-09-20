/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Flesch-Kincaid problem.
 */

#include <iostream>
#include <fstream>
#include <ctype.h>
#include "tokenscanner.h"
#include "simpio.h"
#include "console.h"
using namespace std;

int main() {
	ifstream in;
	string filename;
	int word = 0, sentence = 0, syllable = 0;

	string vowels = "aeoiuyAEOIYU";
	while(true){
		filename = getLine("Enter the filename to be read: ");
		in.open(filename.c_str());
		if(in.fail()) {cout << "ERROR: file can't open!\n"; in.clear();} else break;
	}

	TokenScanner scanner(in);
	scanner.addWordCharacters("'");
	scanner.ignoreWhitespace();
	while( scanner.hasMoreTokens() )
	{
		int localSyllable = 0;
		TokenType type = WORD;
		string token = scanner.nextToken();
		
		if(type == scanner.getTokenType(token) && isalpha(token[0])){
			word++;

			if(vowels.find(token[0]) != string::npos) localSyllable++;
			for(int i = 1; i < token.length(); i++)
			{
				if(vowels.find(token[i-1]) == string::npos && vowels.find(token[i]) != string::npos) localSyllable++;
		/*		if(token[i-1] == 'i' && token[i] == 'a') localSyllable++;*/
			}
			if(token[token.length() - 1] == 'e') localSyllable--;
			if(localSyllable == 0) localSyllable = 1;
			syllable += localSyllable;
		}
		else if(token == "." || token == "!" || token == "?") {sentence++;}

	}
	if(word == 0) word = 1;
	if(sentence == 0) sentence = 1;

	double grade = -15.59 + .39*(double(word)/sentence) + 11.8*(double(syllable)/word);

	cout << "Words: " << word << endl;
	cout << "Sentences: " << sentence << endl;
	cout << "Syllables: " << syllable << endl;
	cout << "Grade: " << grade << endl;


    return 0;
}
