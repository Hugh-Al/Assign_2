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

void IdeasBank::findWordInBank(string word) {
	for (vector<Idea>::iterator i = bank.begin(); i != bank.end(); ++i) {
		if (i->findWord(word)) {
			i->toString();
		}
	}
}

void IdeasBank::findWordInIndexTree(string word) {
	Index out;
	invertedIndex.AVL_Retrieve(word, out);
	if (out.idList.size() > 0) {
		for (set<int>::iterator i = out.idList.begin(); i != out.idList.end();
				++i) {
			displayIdea(*i);
		}
	} else {
		cout << "Not found in inverted index tree" << endl;
	}
}

void IdeasBank::findRelatedIdeas(int ideaNumber) {
	set<int> relatedList;
	Idea temp = getIdea(ideaNumber);
	string parsedContent = parseContent(temp.getContent());
	Index out;
	string word;
	for (unsigned int i = 0; i < temp.getKeywords().size(); i++) {
		word = temp.getKeywords().at(i);
		invertedIndex.AVL_Retrieve(word, out);
		relatedList.insert(out.idList.begin(), out.idList.end());
	}
	cout << "Related ideas of " << ideaNumber << " are: ";
	for (set<int>::iterator i = relatedList.begin(); i != relatedList.end();
			++i) {
		if (ideaNumber != *i) {
			cout << *i << " ";
		}
	}
	cout << endl;

}

Idea IdeasBank::getIdea(int id) {
	for (vector<Idea>::iterator i = bank.begin(); i != bank.end(); ++i) {
		if (i->getID() == id) {
			return *i;
		}
	}
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
	Idea beDeleted;
	beDeleted = getIdea(id);
	string word;
	vector<string> keywords = beDeleted.getKeywords();
	string parsedContent = parseContent(beDeleted.getContent());
	stringstream ss(parsedContent);
	for (vector<string>::const_iterator i = keywords.begin(); i != keywords.end();
			++i) {
		word = *i;
		Index temp(word, beDeleted.getID());
		invertedIndex.AVL_Delete(word, temp);
	}
	while (ss >> word) {
		Index temp(word, beDeleted.getID());
		invertedIndex.AVL_Delete(word, temp);
	}
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

Index IdeasBank::query(string word) {
	Index out;
	bool found = false;
//	found = invertedIndex.AVL_Retrieve(word, out);
	invertedIndex.AVL_Retrieve(word, out);
//	if (found) {
//		return out;
//	}else {
//		cout << word << " not found in inverted index: ";
//	}

	cout << " value is " << out.key << endl;
	return out;
}

void IdeasBank::query2(string argument) {
	stringstream ss(argument);
	string word;
	vector<string> split;

	while (ss >> word) {
		split.push_back(word);
	}
	if (split.size() == 1) {
		cout << "1 arg " << split.at(0);
		query(split.at(0));
		return;
	}

	string boolCond = split.at(1);
	if (boolCond == "AND") {
		Index first = query(parseContent(split.at(0)));
		Index second = query(parseContent(split.at(2)));
		set<int> intersect;
		set_intersection(first.idList.begin(), first.idList.end(),
				second.idList.begin(), second.idList.end(),
				std::inserter(intersect, intersect.begin()));
		cout << "Common id is: ";
		for (set<int>::iterator i = intersect.begin(); i != intersect.end();
				++i) {
			cout << *i << ", ";
		}
		cout << endl;
	} else if (boolCond == "OR") {
		Index first = query(parseContent(split.at(0)));
		Index second = query(parseContent(split.at(2)));
		set<int> unionOfId = first.idList;
		unionOfId.insert(second.idList.begin(), second.idList.end());
		cout << "Id are: ";
		for (set<int>::iterator i = unionOfId.begin(); i != unionOfId.end();
				++i) {
			cout << *i << ", ";
		}
		cout << endl;
	} else {
		cout
				<< "Please provided correct argument format replacing boolean with either AND or OR"
				<< endl;
		cout << "word (BOOLEEAN OPERATOR) word" << endl;
	}

//	Index out;
//	bool found = false;
//	found = invertedIndex.AVL_Retrieve(word, out);
//	if (found) {
//		cout << word << " is in idea: ";
//		for (set<int>::iterator i = out.idList.begin(); i != out.idList.end();
//				++i) {
//			cout << *i << ", ";
//		}
//		cout << endl << endl;
//	}else {
//		cout << word << " not found in inverted index: ";
//	}
//	cout << endl  << "------------------------" << endl;
}

