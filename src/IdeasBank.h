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
#include <set>
#include <string>
#include <fstream>

struct Index {
	string key;
	set<int> idList;
	Index() {
	}
	Index(string value, int id) {
		key = value;
		idList.insert(id);
	}
	Index(const Index& copy) {
		key = copy.key;
		idList = copy.idList;
	}
};

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

	void ideaToIndex(Idea);
	void query(string);

	AvlTree<Index, string> getTree() {
		return invertedIndex;
	}
	;

private:
	vector<Idea> bank;
	vector<Idea> Ideasvector;
	AvlTree<Index, string> invertedIndex;
};

#endif /* IDEASBANK_H_ */
