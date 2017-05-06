/*
 * Idea.cpp
 *
 *  Created on: 1May,2017
 *      Author: User
 */

#include "Idea.h"

Idea::Idea(string proposer, vector<string> keywords, string content) {
	uniqId = ++id;
	this->proposer = proposer;
	this->keywords = keywords;
	this->content = content;
}

Idea::~Idea() {
	// TODO Auto-generated destructor stub
}

int Idea::id = 0;

Idea::Idea(const Idea& copy){
	uniqId = copy.getID();
	proposer = copy.getProposer();
	keywords = copy.getKeywords();
	content = copy.getContent();
}

int Idea::getID() const{
	return uniqId;
}

string Idea::getContent() const{
	return content;
}

string Idea::getProposer() const{
	return proposer;
}

vector<string> Idea::getKeywords() const{
	return keywords;
}
void Idea::toString() {
	cout << "ID: " << getID() << endl;
	cout << "Proposer: " << proposer << endl;
	cout << "Keywords: ";
	for (vector<string>::const_iterator i = keywords.begin();
			i != keywords.end(); ++i) {
		std::cout << *i << ' ';
	}
	cout << endl;
	cout << "Content: " << content << endl;
}

bool Idea::findContent(string word) {
	return content.find(word);
}

bool Idea::findKeyword(string word) {
	for (vector<string>::const_iterator i = keywords.begin();
			i != keywords.end(); ++i) {
		if (word == *i) {
			return true;
		}
	}
	return false;
}
