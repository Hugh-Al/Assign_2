/*
 * IdeasBank.h
 *
 *  Created on: 1May,2017
 *      Author: User
 */

#ifndef IDEASBANK_H_
#define IDEASBANK_H_

#include "Idea.h"
#include "AVL_ADT.h"
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>

class IdeasBank {
public:
	IdeasBank();
	virtual ~IdeasBank();

	// Data insertion, user input, existing idea, file input
	void insertData();
	void insertIdea(Idea);
	void insertFile(string);
	vector<string> stringToKeywords(string);
	string parseContent(string);


	void displayIdea(int);
	void deleteIdea(int);
	void displayBank();

	void ideaToIndex(Idea, string);

	struct Index{
		string key;
		vector<int> idList;
	};


private:
	vector<Idea> bank;
	vector<Idea> Ideasvector;
	AvlTree<Index, string> invertedIndex;
};

#endif /* IDEASBANK_H_ */
