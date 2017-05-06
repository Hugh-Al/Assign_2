/*
 * IdeasBank.cpp
 *
 *  Created on: 1May,2017
 *      Author: User
 */

#include "IdeasBank.h"
#include <sstream>

IdeasBank::IdeasBank() {
	// TODO Auto-generated constructor stub

}

IdeasBank::~IdeasBank() {
	// TODO Auto-generated destructor stub
}

void IdeasBank::insertData() {
	string name;
	string temp;
	string lineInput, parsedLineInput;
	vector<string> keywords;
	cout << "Please enter Proposers name\n>";
	getline(cin, name);
	cout
			<< "Please insert keywords. Each new keyword must be followed by entering the RETURN key.\nTo quit, please enter '\\'"
			<< endl;
	while (true) {
		getline(cin, temp);
		if (temp.compare("\\") == 0) {
			break;
		}
		keywords.push_back(temp);
	}
	cout << "Please enter content\n>";
	getline(cin, lineInput);
	remove_copy_if(lineInput.begin(), lineInput.end(),
			std::back_inserter(parsedLineInput), //Store output
			std::ptr_fun<int, int>(&std::ispunct));
	Idea newIdea(name, keywords, parsedLineInput);
	bank.push_back(newIdea);
	ideaToIndex(newIdea);

}

void IdeasBank::insertIdea(Idea newIdea) {
	bank.push_back(newIdea);
	ideaToIndex(newIdea);
}

void IdeasBank::insertFile(string file) {
	ifstream dataInput(file.c_str());
	string word, propName, stringKeyword, tempContent, clearLine;

	while (!dataInput.eof()) {
		getline(dataInput, propName, ';');
		getline(dataInput, stringKeyword, ';');
		getline(dataInput, tempContent, ';');
		getline(dataInput, clearLine);
		getline(dataInput, clearLine);

		//convert string to keyword, keep content with punctuations? function ready to remove it
		vector<string> tempKeyword = stringToKeywords(stringKeyword);

		Idea tempIdea(propName, tempKeyword, tempContent);
		bank.push_back(tempIdea);
		ideaToIndex(tempIdea);
	}
}

//Converts string to vector<string> O(n)
vector<string> IdeasBank::stringToKeywords(string keywordString) {
	stringstream keywordStream(keywordString);
	istream_iterator<string> begin(keywordStream);
	istream_iterator<string> end;
	vector<string> keywordVector(begin, end);
	return keywordVector;
}

//Parse content removing punctuation and capital, O(n)
string IdeasBank::parseContent(string unparsedString) {
	string parsedString;
	remove_copy_if(unparsedString.begin(), unparsedString.end(),
			std::back_inserter(parsedString), //Store output
			std::ptr_fun<int, int>(&std::ispunct));
	transform(parsedString.begin(), parsedString.end(), parsedString.begin(),
			::tolower);
	return parsedString;
}

//Do binary search here // make binary search function?? to find idea faster
void IdeasBank::displayIdea(int id) {
	for (vector<Idea>::iterator i = bank.begin(); i != bank.end(); ++i) {
		if (i->getID() == id) {
			i->toString();
		}
	}
}

//Do binary search here // make binary search function?? to find idea faster
void IdeasBank::deleteIdea(int id) {
	for (vector<Idea>::iterator i = bank.begin(); i != bank.end(); ++i) {
		if (i->getID() == id) {
			bank.erase(i);
		}
	}
}

void IdeasBank::displayBank() {
	for (vector<Idea>::iterator i = bank.begin(); i != bank.end(); ++i) {
		i->toString();
	}
}

void IdeasBank::ideaToIndex(Idea idea) {
	//tokenise everything
	int indexID = idea.getID();
	vector<string> test = idea.getKeywords();
	for (vector<string>::const_iterator i = test.begin(); i != test.end();
			++i) {
		string value = *i;
		Index item(value, indexID);
		invertedIndex.AVL_Insert(item);
	}

	string parsedContent = parseContent(idea.getContent());
	string buf;
	stringstream ss(parsedContent);
	while (ss >> buf) {
		Index item(buf, indexID);
		invertedIndex.AVL_Insert(item);
	}
}
