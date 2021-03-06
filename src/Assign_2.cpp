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
	cout << endl;
}

void performAction(IdeasBank&, int);

int main() {
	IdeasBank globalIndex;

	int input;
	do {
		cout << "Menu" << endl;
		cout << "1. Import ideas from a file" << endl;
		cout << "2. Input idea manually" << endl;
		cout << "3. Print idea bank" << endl;
		cout << "4. Search for related ideas from ideas bank" << endl;
		cout << "5. Search for related ideas from indexing tree" << endl;
		cout << "6. Related ideas of an idea" << endl;
		cout << "7. Delete an idea" << endl;
		cout << "8. Print the word indices" << endl;
		cout << "9. Quit" << endl;
		cin >> input;
		performAction(globalIndex, input);
	} while (input != 9);
    cout << "Pause" << endl;
    cin >> input;
	return 0;
}

void performAction(IdeasBank& globalIndex, int input) {
	switch (input) {
	case 1: {
		string filepath;
		cout
				<< "Please enter file destination of text input, ensure file is formatted correctly."
				<< endl;
		cin >> filepath;
		globalIndex.insertFile(filepath);
	}
		break;
	case 2: {
		globalIndex.insertData();
	}
		break;
	case 3: {
		globalIndex.displayBank();
	}
		break;
	case 4: {
		string word;
		cout << "Please input a word" << endl;
		cin >> word;
		globalIndex.findWordInBank(word);
	}
		break;
	case 5: {
		string word;
		cout << "Please input a word" << endl;
		cin >> word;
		globalIndex.findWordInIndexTree(word);
	}
		break;
	case 6: {
		int ideaNum;
		cout << "Which id number to find related ideas?" << endl;
		cin >> ideaNum;
		globalIndex.findRelatedIdeas(ideaNum);
	}
		break;
	case 7: {
		int ideaNum;
		cout << "Which id number to delete?" << endl;
		cin >> ideaNum;
		globalIndex.deleteIdea(ideaNum);
	}
		break;
	case 8: {
		globalIndex.getTree().AVL_Traverse(print);
	}
		break;
//	case 9: {
//
//	}
//		break;
	default: {
		cout << "Terminated:" << endl;
		break;
	}
	}
}
