/*
 * Idea.h
 *
 *  Created on: 1May,2017
 *      Author: User
 */

#ifndef IDEA_H_
#define IDEA_H_

#include <iostream>
#include <vector>
using namespace std;

class Idea {
public:
	Idea(string, vector<string>, string);
	Idea(const Idea&);
	virtual ~Idea();
	//Getters
	int getID() const;
	string getContent() const;
	string getProposer() const;
	vector<string> getKeywords() const;
	void toString();
	bool findWord(string);
	bool findContent(string);
	bool findKeyword(string);
private:
	static int id;
	int uniqId;
	string proposer;
	string content;
	vector<string> keywords;


};



#endif /* IDEA_H_ */
