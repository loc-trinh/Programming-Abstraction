/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3 using recursive calls.
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
	cout << "RNA Strands for the Protein KWS" << endl;
    Map<char, Set<string> > codons = loadCodonMap();
	listAllRNAStrandsFor("KWS", codons);
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

/* listAllRNAStrandsFor 
 * ---------------------------------------
 * Recursively pick each protein and locate the matching RNA
 * Since functions parameters are forbidden from changes, the resulting RNA is added to the protein strand for
 * easy pass-by. The period is used as seperators between proteins and RNA strings.
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	if(protein.find(".") == string::npos) protein += '.'; //Add "." seperator if not already existed
	if(protein[0] == '.'){ cout << protein.substr(1) << endl; return; } //When the seperator is reached, print the RNA
	else{
		int i = 0;
		foreach(string codon in codons[protein[0]]){
			if(i == 0){
				protein += codon; i++;} // if a codon was previously attached, add one to counter
			else
				protein = protein.substr(0, protein.size() - 3) + codon; //if a codon was previously tried, replace with new codon
			listAllRNAStrandsFor(protein.substr(1), codons);
		}
	}
}