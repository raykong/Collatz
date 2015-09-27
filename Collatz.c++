// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;
int maxcounter, counter, x;
int solved[1000001] = {};


// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

int Nextcycle(int x) { //Returns count of next cycle
	if (x == 1) return 1;
	if (x > 1000000) //Check if number can be stored in array
		if (x % 2 == 0) 
			return Nextcycle(x >> 1) + 1;
		else 
			return Nextcycle(x + (x >> 1) + 1) + 2;		
	if (solved[x] != 0) return solved[x]; //Check if number already solved
	if (x % 2 == 0) //Perform algorithm, increment counter, and store result in solved array
		solved[x] = Nextcycle(x >> 1) + 1;	
	else 
		solved[x] = Nextcycle(x + (x >> 1) + 1) + 2;	
	return solved[x];
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    // <your code>
	maxcounter = 0;
	counter = 1;
	if (i > j) {
		x = i;
		i = j;
		j = x;
	}
	for (int a = i; a <= j; ++a) {
		counter = Nextcycle(a);
		if (counter > maxcounter) maxcounter = counter;
	};	
    return maxcounter;}

int collatz_eval1(int i, int j) {
	// <your code>
	maxcounter = 0;
	counter = 1;
	if (i > j) {
		x = i;
		i = j;
		j = x;
	}
	for (int a = i; a <= j; ++a) {
		//cout << a << ": ";
		counter = 1;
		x = a;
		while (x != 1) {
			if (x % 2 == 0) {
				x = x >> 1;
				++counter;
			}
			else {
				x += (x >> 1) + 1;
				counter += 2;
			}
			//cout << x << " ";
		};
		//cout << counter<<" Cycles, ";
		if (counter > maxcounter) maxcounter = counter;
	};
	//cout << "###Largest counter: " << maxcounter<<endl;
	return maxcounter;
}
// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
