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

Idea::Idea(const Idea& copy) {
	uniqId = copy.getID();
	proposer = copy.getProposer();
	keywords = copy.getKeywords();
	content = copy.getContent();
}

int Idea::getID() const {
	return uniqId;
}

string Idea::getContent() const {
	return content;
}

string Idea::getProposer() const {
	return proposer;
}

vector<string> Idea::getKeywords() const {
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

bool Idea::findWord(string word) {
	return (findContent(word) || findKeyword(word));
}

bool Idea::findContent(string word) {
	string parsedString;
	remove_copy_if(content.begin(), content.end(),
			std::back_inserter(parsedString), //Store output
			std::ptr_fun<int, int>(&std::ispunct));
	transform(parsedString.begin(), parsedString.end(), parsedString.begin(),
			::tolower);
	string buf;
	stringstream ss(parsedString);
	while (ss >> buf) {
		if (buf == word) {
			return true;
		}
	}
	return false;
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
