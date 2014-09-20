/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Word Ladder problem.
 * This program will find a minimal word ladder between two words.
 * The codes will make use of several of the ADTs, along with a powerful algorithm
 * called breadth-first search to find the shortest such sequence.
 */

#include <iostream>

#include "simpio.h"
#include "console.h"
#include "lexicon.h"
#include "vector.h"
#include "queue.h"

using namespace std;

typedef Vector<string> Ladder;

Ladder wordLadder(string start, string end);

int main() {
	while(true){
		string start = getLine("Enter the starting word (or nothing to quit): ");
		if(start == "") break;
		string end = getLine("Enter the ending word: ");
		cout << "Searching..." << endl;


		Ladder result = wordLadder(start, end);	
		if(result.size() == 0)
			 cout << "No word ladder could be found." << endl << endl; 
		else{
			cout << "Ladder found: " << result[0];
			for(int i = 1; i < result.size(); i++) 
				cout << " -> "<< result[i];
			cout << endl << endl;}
	}
	cout << "Goodbye!" << endl;
	return 0;
}





/* Ladder wordLadder(string start, string end)
 * --------------------------------------------------------
 * This function takes two words and find the shortest possible ladder between them.
 * A queue with vector<string> is used as the data structure
 * Each character the starting word is changed to get to the final word.
 * Repetition of words are saved in Ladder usedWords in order to prevent circle loop
 */

Ladder wordLadder(string start, string end){
	Lexicon wordList("EnglishWords.dat"), usedWords;
	Ladder null; //empty ladder will be return to report no ladder
/*
 *code: if(start.size() != end.size() || !wordList.contains(end)) return null; 
 *can be used to eliminate pointless case:
 * 1) two words with different lengths can't have a ladder
 * 2) if ending word weren't a word in the lexicon, there won't be a ladder
 */
	usedWords.add(start);
	Ladder begin(1,start);
	Queue<Ladder> queue;
	queue.enqueue(begin); //enqueue the start word

	while(!queue.isEmpty()){
		Ladder ladder = queue.dequeue(); //get the first ladder in line, check whether the last word in the ladder
										 // is the final word, continue changing the character without repeating words
		string currentWord = ladder[ladder.size()-1];
		if(currentWord == end) return ladder;
					
		for(int i = 0; i < currentWord.size(); i++)
		{
			char perserve = currentWord[i]; //used to perserve the character because only one char can be change
			for(int j = 0; j < 26; j++)
			{
				currentWord[i] = 'a' + j; 
				if(wordList.contains(currentWord) && !usedWords.contains(currentWord))
				{
					Ladder newLadder = ladder; //create and new ladder and push into queue
					newLadder.add(currentWord);
					queue.enqueue(newLadder);
					usedWords.add(currentWord);
				}
			}
			currentWord[i] = perserve;
		}
	}
	return null;
}