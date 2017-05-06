//============================================================================
// Name        : Assignment_2.cpp
// Author      : Huy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Idea.h"
#include "IdeasBank.h"
using namespace std;

int main() {
//	vector<string> keyword;
//	vector<string> k2, k3;
//	keyword.push_back("alphabet");
//	keyword.push_back("typing");
//	keyword.push_back("animals");
//	k2.push_back("hello");
//	k2.push_back("world");
//	k3.push_back("Goodbye humans");
//
//	Idea test("Huy", keyword, "The quick brown fox jumps over the lazy dog.");
//	Idea test2("Monkey", k2, "Why dear god, why");
//	Idea test3("Taxi", k3, "I didn't ask to be born.");
//
//	IdeasBank please;
//	please.insertIdea(test);
//	please.insertIdea(test2);
//	please.insertIdea(test3);
//
//	please.insertData();
//	please.displayBank();
//	please.deleteIdea(2);
//	please.displayBank();

//	IdeasBank example;
//	example.ideaFile();

	IdeasBank testing;
	testing.insertFile("input.txt");
	testing.displayBank();

	return 0;
}
