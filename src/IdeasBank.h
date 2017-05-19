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

#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>
#include <fstream>

struct Index {
	string key;
	set<int> idList;
	int getFirstID() {
		return *(idList.begin());
	}
	;
	void toString() {
		cout << "key:" << key << endl;
		cout << "ID: ";
		for (set<int>::iterator it = idList.begin(); it != idList.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}
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

	void insertData();
	void insertIdea(Idea);
	void insertFile(string);
	void findWordInBank(string);
	void findWordInIndexTree(string);
	void findRelatedIdeas(int);
	void displayIdea(int);
	void deleteIdea(int);
	void displayBank();
	void query2(string);

	AvlTree<Index, string> getTree() {
		return invertedIndex;
	}
	;

private:
	void ideaToIndex(Idea);
	bool getIdea(int, Idea&);
	vector<string> stringToKeywords(string);
	string parseContent(string);
	Index query(string);
	void removeIdeaFromBank(vector<Idea>&, int);
	vector<Idea> bank;
	vector<Idea> Ideasvector;
	AvlTree<Index, string> invertedIndex;
};

#endif /* IDEASBANK_H_ */

