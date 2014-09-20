/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3 using recursive backtracking.
 */
#include <iostream>
#include <string>
#include "console.h"
#include "set.h"
#include "vector.h"
#include "simpio.h"

using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result)
{
	if(cities.size() == 0) return true; //if no more cities to cover, return true
	else if(numHospitals == 0) return false;//if hospitals limit reached, return false
	else{
		for(int i = 0; i < locations.size(); i++){
			Set<string> citiesLeftToCover = cities - locations[i]; 
			/* Each hospitaled was tried and result temporarily stored in citiesLeftToCover
			 * so when the choice fail, no unmake-choice is necessary 
			 */

			result.add(locations[i]); //updating result
			if(canOfferUniversalCoverage(citiesLeftToCover, locations, numHospitals - 1, result)) return true; // if works, return true
			result.remove(result.size() - 1);} //updating result if choice failed
	}
	return false;
}


int main() {
	Set<string> cities;
	for(char ch = 'A'; ch <= 'F'; ch++)
		cities.add(string() + ch);

	Vector< Set<string> > locations;
	Set<string> hospitals;
	hospitals.add("A");
	hospitals.add("B");
	hospitals.add("C");
	locations.add(hospitals);
	hospitals.clear();

	hospitals.add("A");
	hospitals.add("D");
	hospitals.add("C");
	locations.add(hospitals);
	hospitals.clear();

	hospitals.add("B");
	hospitals.add("F");
	locations.add(hospitals);
	hospitals.clear();

	hospitals.add("C");
	hospitals.add("F");
	hospitals.add("E");
	locations.add(hospitals);
	hospitals.clear();

	Vector< Set<string> > results;
	while(true){
	int numHospitals = getInteger("Enter the number of hospitals: ");
	if(numHospitals == -1) break;
	if(canOfferUniversalCoverage(cities, locations, numHospitals, results)){
		cout << "FULL Coverage." << endl;
		foreach(Set<string> set in results)
			cout << "\tHospital: " << set << endl;
	}
	else
		cout << "Unable to provide full coverage." << endl;
	}

    return 0;
}
