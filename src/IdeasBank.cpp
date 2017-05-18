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
	string clearLine;
	string name;
	string temp;
	string lineInput, parsedLineInput;
	vector<string> keywords;
	getline(cin, clearLine);
	cout << "Please enter Proposers name >" << endl;
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
	cout << "Inserted " << file << " to inverted index.";
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
	Idea temp;
	// if idea number is in bank
	if (getIdea(ideaNumber, temp)) {
		vector<string> keys = temp.getKeywords();
		string parsedContent = parseContent(temp.getContent());
		Index out;
		string word;
		for (vector<string>::iterator it = keys.begin(); it != keys.end();
				++it) {
			word = *it;
			invertedIndex.AVL_Retrieve(word, out);
			relatedList.insert(out.idList.begin(), out.idList.end());
		}
		// Print set if size greater than 0 else inform user that the idea is unique
		if (relatedList.size() > 0) {
			cout << "Related ideas of " << ideaNumber << " are: ";
			for (set<int>::iterator i = relatedList.begin();
					i != relatedList.end(); ++i) {
				if (ideaNumber != *i) {
					cout << *i << " ";
				}
			}
			cout << endl;
		} else {
			cout << "Idea number: " << ideaNumber << " is unique." << endl;
		}

	} // Id number is not in bank
	else {
		cout << "Idea number: " << ideaNumber
				<< " does not exist in Invert Index" << endl;
	}

}

bool IdeasBank::getIdea(int id, Idea& results) {
	for (vector<Idea>::iterator i = bank.begin(); i != bank.end(); ++i) {
		if (i->getID() == id) {
			results = *i;
			return true;
		}
	}
	return false;
}

void IdeasBank::displayIdea(int id) {
	for (vector<Idea>::iterator i = bank.begin(); i != bank.end(); ++i) {
		if (i->getID() == id) {
			i->toString();
		}
	}
}

void IdeasBank::removeIdeaFromBank(vector<Idea>& bankOfIdeas, int id) {
	bankOfIdeas.erase(
			std::remove_if(bankOfIdeas.begin(), bankOfIdeas.end(),
					[&]( const Idea& idea ) // lambda
					{	return idea.getID() == id;}), bankOfIdeas.end());
}


void IdeasBank::deleteIdea(int id) {
	Idea beDeleted;

	if (getIdea(id, beDeleted)) {
		string word;
		vector<string> keywords = beDeleted.getKeywords();
		string parsedContent = parseContent(beDeleted.getContent());
		stringstream ss(parsedContent);
		for (vector<string>::iterator i = keywords.begin();
				i != keywords.end(); ++i) {
			word = *i;
			Index temp(word, beDeleted.getID());
			invertedIndex.AVL_Delete(word, temp);
		}
		while (ss >> word) {
			Index temp(word, beDeleted.getID());
			invertedIndex.AVL_Delete(word, temp);
		}
		removeIdeaFromBank(bank, beDeleted.getID());

	} else {
		cout << "Id number " << id << " is not in idea bank or Index List."
				<< endl;
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
	invertedIndex.AVL_Retrieve(parseContent(word), out);
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
		Index first = query(split.at(0));
		if (first.idList.size() > 0) {
			first.toString();
		} else {
			cout << "Not found in inverted index." << endl;
		}
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
		if (intersect.size() > 0) {
			cout << split.at(0) << " AND " << split.at(2) << endl;
			cout << "ID: ";
			for (set<int>::iterator i = intersect.begin(); i != intersect.end();
					++i) {
				cout << *i << " ";
			}
			cout << endl;
		} else {
			cout << split.at(0) << " AND " << split.at(2)
					<< " not in inverted index." << endl;
		}
	} else if (boolCond == "OR") {
		Index first = query(parseContent(split.at(0)));
		Index second = query(parseContent(split.at(2)));
		set<int> unionOfId = first.idList;
		unionOfId.insert(second.idList.begin(), second.idList.end());
		cout << split.at(0) << " OR " << split.at(2) << endl;
		cout << "ID: ";
		if (unionOfId.size() > 0) {
			for (set<int>::iterator i = unionOfId.begin(); i != unionOfId.end();
					++i) {
				cout << *i << " ";
			}
			cout << endl;
		} else {
			cout << split.at(0) << " OR " << split.at(2)
					<< " not in inverted index." << endl;
		}
	} else {
		cout << "Please provided correct argument format. STRING1 BOOL STRING2" << endl;
		return;
	}
}

