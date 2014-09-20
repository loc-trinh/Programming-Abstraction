/*
 * File: Boggle.cpp
 * ----------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the main starter file for Assignment #4, Boggle.
 * The Boggle game board is a square
 * grid onto which you randomly distribute a set of letter cubes. The goal is to find words on the board by
 * tracing a path through adjoining letters. Two letters adjoin if they are next to each other horizontally,
 * vertically, or diagonally. There are up to eight letters adjoining a cube. Each cube can be used at most
 * once in a word. In the original version, all players work concurrently listing the words they find.
 * When time is called, duplicates are removed from the lists and the players receive points for their
 * remaining words.
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "console.h"
#include "point.h"
#include "map.h"
#include "set.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

//Support and opening functions
void welcome();
void giveInstructions();
string upper(string word);

//Board set-up and manipulating functions
int setupBoard();
Vector<string> shakeCubes(const int boardSize);
Grid<char> fillBoard(const int boardSize, Vector<string>& cubesList);
Grid<char> placeCubes(const int boardSize, Vector<string>& cubesList);
Grid<char> configureCubes(const int boardSize);
void highLight(Map<string, Point> cubesUsed);

//Player-turn functions and recursive word-finding functions
Lexicon playerHuman(const int boardSize, Grid<char> board);
void playerComputer(const int boardSize, Grid<char> board, Lexicon humanList);
bool humanFindWord(const int boardSize, string word, Grid<char> board, int row, int col, int flag, Map<string, Point> &used);
void compFindWord(const int boardSize, Grid<char> board,string word, int row, int col, Set<string> usedCubes, Vector<string>& wordsFound);



/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
	string replay;
	welcome();
	do{
		const int boardSize = setupBoard();
		Vector<string> cubesList = shakeCubes(boardSize);
		Grid<char> board = 	fillBoard(boardSize, cubesList);
		Lexicon humanList = playerHuman(boardSize, board);
		playerComputer(boardSize, board, humanList);
		replay = getLine("Would you like to play again?: ");
	}while(replay[0] != 'n');
	cout << endl << "Thanks for playing!" << endl;
    return 0;
}



/* **************************************************
 *              Welcoming functions
 * **************************************************
 */

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message and prompt for instructions.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;

	while(true)
	{
		string instructions = getLine("Do you need instructions?: ");
		if(instructions[0] == 'y'){giveInstructions(); break;}
		else if(instructions[0] == 'n') break;
		else cout << "Please answer yes or no." << endl;
	}
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions()
{
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/* Function: upper
 * Usage: upper(word);
 * --------------------------
 * Capitalize user input strings to match the cubes
 */

string upper(string word){
	for(int i = 0; i < word.length(); i++)
		word[i] = toupper(word[i]);
	return word;
}






/* **************************************************
 *       Board setup and manipulating functions
 * **************************************************
 */

/*
 * Function: setupBoard
 * Usage: setupBoard();
 * --------------------------
 * Ask for board size and draw board
 */

int setupBoard(){
	cout << endl << "You can choose the standard Boggle(4x4) or the Big Boggle(5x5)" << endl;
	while(true)
	{
		string boardSize = getLine("Would you like the Big Boggle?: ");
		if(boardSize[0] == 'n'){drawBoard(4,4); return 4;}
		else if(boardSize[0] == 'y') {drawBoard(5,5); return 5;}
		else cout << "Please answer yes or no." << endl;
	}

}

/*
 * Function: shakeCubes
 * Usage: shakeCubes(boardSize);
 * --------------------------
 * Read the set of cubes depend on the user-selected size and randomize the cube,
 * Return: the set of cubes are returned in the Vector<string> format
 */

Vector<string> shakeCubes(const int boardSize){
	Vector<string> cubesList;

	if(boardSize == 4) 
		for(int i = 0; i < boardSize*boardSize; i++) cubesList.add(STANDARD_CUBES[i]);
	else 
		for(int i = 0; i < boardSize*boardSize; i++) cubesList.add(BIG_BOGGLE_CUBES[i]);

	for(int i = 0; i < cubesList.size(); i++){
		int r = randomInteger(i, cubesList.size() - 1);
		string temp = cubesList[i];
		cubesList[i] = cubesList[r];
		cubesList[r] = temp;
	}
	return cubesList;
}

/*
 * Function: fillBoard
 * Usage: fillBoard(boardSize, cubesList);
 * --------------------------
 * Fill the board whether the user want to self-pick or randomize
 * Return: Grid representation of the board
 */

Grid<char> fillBoard(const int boardSize, Vector<string>& cubesList){
	Grid<char> board(boardSize, boardSize);
	
	while(true)
	{
		string config = getLine("\nDo you want to force the board configuration?: ");
		if(config[0] == 'n') return placeCubes(boardSize, cubesList);
		else if(config[0] == 'y') return configureCubes(boardSize);
		else cout << "Please answer yes or no." << endl;
	}
}

/*
 * Function: placeCubes
 * Usage: placeCubes(boardSize, cubesList);
 * --------------------------
 * Fill the board with randomization
 * Return: Grid representation of the board
 */

Grid<char> placeCubes(const int boardSize, Vector<string>& cubesList){
	Grid<char> board(boardSize, boardSize);
	for(int i = 0; i < boardSize; i++)
		for(int j = 0; j < boardSize; j++){
			char letter = cubesList[boardSize*i+j][randomInteger(0,5)];
			labelCube(i, j, letter);
			board[i][j] = letter;
		}
	return board;
}

/*
 * Function: placeCubes
 * Usage: placeCubes(boardSize);
 * --------------------------
 * Ask for a string of letters and filled the cubes according to user-input
 * Return: Grid representation of the board
 */

Grid<char> configureCubes(const int boardSize){
	Grid<char> board(boardSize, boardSize);
	cout << "Enter a 16 or 25-character string to identify which letters you want on the cubes. \nThe first 4 or 5 letters are the cubes on the top row from left to right, \nthe next 4 or 5 letters are the second row, and so on." << endl;
	string line;
	while(true){
		line = getLine("Enter a string: ");
		if(boardSize == 5 && line.size() >= 25) break;
		else if(boardSize == 4 && line.size() >= 16) break;
		else cout << "Not enough characters" << endl;
	}

	for(int i = 0; i < boardSize; i++)
		for(int j = 0; j < boardSize; j++){
			char letter = line[boardSize*i+j];
			labelCube(i, j, letter);
			board[i][j] = letter;
		}
	return board;
}
/*
 * Function: highLight
 * Usage: highLight(cubesUsed);
 * --------------------------
 * Highlight the coordinates in cubesUsed
 */
void highLight(Map<string, Point> cubesUsed){
	foreach(string key in cubesUsed)
		highlightCube(cubesUsed[key].getX(), cubesUsed[key].getY(), true);
	pause(800);
	foreach(string key in cubesUsed)
		highlightCube(cubesUsed[key].getX(), cubesUsed[key].getY(), false);
}
/* ****************************************************************
 *       Player functions and Recursive Search Functions
 * ****************************************************************
 */

/* Function: playerHuman
 * Usage: playerHuman(boardSize, board)
 * -----------------------------------------------
 * Ask for a word and check whether it's used, an actual word, or a too short word
 * if a word satisfied the over conditions and is on the board, add it to humanList and highlight it
 * Return: Lexicon of the human word list
 */

Lexicon playerHuman(const int boardSize, Grid<char> board){
	Lexicon Dictionary("EnglishWords.dat"), humanList;
	Map<string, Point> cubesUsed;
	while(true)
	{
		string word = getLine("Enter a word: ");
		word = upper(word);
		if(word == "") break;
		else if(word.size() < 4) 
			cout << "I'm sorry, but we have our standards.\nThat word doesn't meet the minimum word length." << endl;
		else if(humanList.contains(word)) 
			cout << "You've already guessed that!" << endl;
		else if(!Dictionary.contains(word)) 
			cout << "That's not a word!" << endl;
		else if(humanFindWord(boardSize, word, board, 0, 0, 0, cubesUsed)){
			highLight(cubesUsed);
			humanList.add(word);
			recordWordForPlayer(word, HUMAN);
		}
		else
			cout << "word not on board" << endl;
	}
	return humanList;
}

/* Function: humanFindWord
 * Usage: humanFindWord(boardSize, word, board, row, col, 0, usedList)
 * -----------------------------------------------
 * If the first character hadn't been found(flag = 0), find it's location
 * Add the location to the usedLIst
 * If the location has been located, find if it's adjacent neighbor are the next character in the string
 * Return false if the adjacent cubes(flag = 1) doesn't match
 * The adjacent cubes must have been not already used
 */

bool humanFindWord(const int boardSize, string word, Grid<char> board, int row, int col, int flag, Map<string, Point> &used){
	if(board[row][col] != word[0] && flag == 0){
		for(int i = 0; i < boardSize; i++)
			for(int j = 0; j < boardSize; j++){
				used.clear();
				if(humanFindWord(boardSize, word, board, i, j, 1, used)) return true;}
	}
	else if(board[row][col] != word[0] && flag == 1) return false;
	else{
		used[Point(row,col).toString()] = Point(row, col);
		if(word.size() == 1) return true;
		for(int i = row-1; i <= row+1; i++)
			for(int j = col-1; j <= col+1; j++)
				if(i < boardSize && i >= 0 && j < boardSize && j >= 0 && !used.containsKey(Point(i,j).toString())){
					if(humanFindWord(boardSize, word.substr(1), board, i,j, 1, used)) return true;
					used.remove(Point(i,j).toString());
				}
	}
	return false;
}

/* Function: playerComputer
 * Usage: playerComputer(boardSize, board, humanList)
 * -----------------------------------------------
 * Run through each location and find the words that can be formed
 * If words wasn't in the humanList, add to the list and reocrd word for player
 */

void playerComputer(const int boardSize, Grid<char> board, Lexicon humanList){
	for(int i = 0; i < boardSize; i++)
		for(int j = 0; j < boardSize; j++){
			Vector<string> wordsFound;
			Set<string> usedCubes;
			compFindWord(boardSize, board,"", i, j, usedCubes, wordsFound);
			foreach(string word in wordsFound){
				if(!humanList.contains(word)){
					humanList.add(word);
					recordWordForPlayer(word, COMPUTER);	
				}
			}
		}
}

/* Function: compFindWord
 * Usage: compFindWord(boardSize, board, word, row, col, usedList, wordList)
 * -----------------------------------------------
 * Add a character from the board to the string one by one
 * If its length is 4 or more and it's a word, add it to the vector WOrdlist
 * If its prefix is in the lexicon, add its adjacent cubes to form a new string
 * return if prefix wasn't found
 */

void compFindWord(const int boardSize, Grid<char> board, string word, int row, int col, Set<string> usedCubes, Vector<string>& wordsFound){
	Lexicon Dictionary("EnglishWords.dat");
	word += board[row][col];
	usedCubes.add(Point(row, col).toString());
	if(word.length() > 3 && Dictionary.contains(word)) wordsFound.add(word);
	if(Dictionary.containsPrefix(word)){
		for(int i = row-1; i <= row+1; i++)
			for(int j = col-1; j <= col+1; j++)
				if(i < boardSize && i >= 0 && j < boardSize && j >= 0 && !usedCubes.contains(Point(i,j).toString()))
					compFindWord(boardSize, board, word, i, j, usedCubes, wordsFound);
	}
	else return;
}
