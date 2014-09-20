/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"

using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
	int num = getInteger("Enter an integer to be converted to a string: ");
	cout << "Converting..." << endl;
	cout << "The number: " << num << " is converted to this string: \"" << intToString(num) << "\"" << endl << endl;
	string line = getLine("Enter a number string to be converted to an integer: ");
	cout << "Converting..." << endl;
	cout << "The string \"" << line << "\" is converted to this integer: " << stringToInt(line) << endl;

    return 0;
}

/* intToString function
 * -----------------------------------
 * Test whether int is negative(if so, perserve it and make string positive)
 * If int is negative, add final to final string "-"
 *
 * Recursive method: Get last digit, convert to string, concatenate to others
 */
string intToString(int n){
	bool negative = false;

	if(n < 0){ n *= -1; negative = true;}
	if( n/10 == 0 )
			return (string() + char(n + '0'));
	else{
		if(negative)
			return "-" + intToString(n/10) + (string() + char(n%10 + '0'));
		else
			return intToString(n/10) + (string() + char(n%10 + '0'));
	}
}

/* stringToInt function
 * -----------------------------------
 * Test whether string is negative(if so, perserve it and make string positive)
 * If string is negative, multiply final int by -1
 *
 * Recursive method: Convert to c-string, get last letter, convert to int, add to the rest
 * NOTE: Multiply by 10 per recursive to perserve digit placement
 */
int stringToInt(string str){
	bool negative = false;
	if(str[0] == '-'){str = str.substr(1); negative = true;}


	if(str.length() == 1){
		if(negative)
			return -1 * (str.c_str()[str.length() - 1] - '0');
		else
			return (str.c_str()[str.length() - 1] - '0');
	}
	else{
		if(negative)
			return -1 * (stringToInt(str.substr(0,str.length() -1 ))*10 + (str.c_str()[str.length() - 1] - '0'));
		else
			return stringToInt(str.substr(0,str.length()-1))*10 + (str.c_str()[str.length() - 1] - '0');
	}


}
