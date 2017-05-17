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

void print(Index ss) {
	cout << ss.key << " - ";
	for (set<int>::iterator i = ss.idList.begin(); i != ss.idList.end(); ++i) {
		cout << *i << " ";
	}
//	for (vector<int>::iterator i = ss.idList.begin(); i != ss.idList.end(); ++i) {
//		cout << *i << " ";
//	}
	cout << endl;
}

int main() {

	IdeasBank testing;
	testing.insertFile("input.txt");
//	testing.getTree().AVL_Print();
//	testing.insertData();
//	testing.insertData();

//testing.displayBank();
//	testing.getTree().AVL_Print();
//	testing.query2("wife AND THE");
//	testing.query2("A OR kiss");

//	testing.displayBank();
//	testing.getTree().AVL_Traverse(print);
	testing.deleteIdea(1);
	testing.deleteIdea(2);
	testing.deleteIdea(3);
	testing.deleteIdea(4);
//	testing.displayBank();
	testing.getTree().AVL_Traverse(print);
	cout << "finished";
//	testing.getTree().AVL_Print();

//testing.getTree().AVL_Traverse(print);

	return 0;
}
