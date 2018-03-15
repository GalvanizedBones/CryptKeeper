#include "provided.h"
#include <string>
#include <vector>

using namespace std;

class DecrypterImpl
{
public:
	bool load(string filename);
	vector<string> crack(const string& ciphertext);
private:
	WordList * m_list;
	vector<Tokenizer*> m_tables; 

	//unsigned long long int patternize(string word);

};

bool DecrypterImpl::load(string filename)
{
	bool p = true;
	WordList* newList = new WordList();
	p = newList->loadWordList(filename);

	WordList * temp = m_list;
	m_list = newList;
	delete temp;
    
	return p;  
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	vector<string> tokens;

	Tokenizer t(",;:.!()[]{}-\"#$%^&");

	//#1) Get Cipher Tokens
	tokens = t.tokenize(ciphertext);

	//For each token
	for (int i = 0; i < tokens.size(); i++) {
		//#2) Find Cipher Pattern
		
		//unsigned long long int pattern = patternize(tokens[i]);
			//Give to word list to do 

		//#3 Get vector of potential words
		string curTrans = ""; // EMPTY, BUT SIZE OF TOKEN[i]
			for (char c : tokens[i]) {
				curTrans += "?";
			}

			//Just initializing first tranlsator now
			vector<string> potenWord = m_list->findCandidates(tokens[i], curTrans);



	}
		
	//#3) Find all Hash Matches
	//vector<string> hashMatches = t.tokenize(m_list->findCandidates(pattern));


	//#4 Generate initial translator tables 
	bool valid = true;
	int i = 0;
	for (i = 0; i < tokens.size(); i++) {
		valid = true;
		Translator* genTable = new Translator;
		//valid = genTable->pushMapping(tokens[i],hashMatches[j] )
		if (!valid) {
			continue; //Dont add non-valid translator to validOut 
		}
		//m_tables.push_back(genTable);

	}


	vector<Translator> validTrans;
	vector<string> out;
	//string curTrans = "";
	//while (!validTrans.empty())
	//{
	//	curTrans = validTrans.back();
	//	out.push_back(curTrans);
	//	validTrans.pop_back();
	//}

	return out;



}



//unsigned long long int DecrypterImpl::patternize(string word) {
//
//	int i = 1;
//	vector<int> id;
//	vector<char> check;
//	bool unique = true;
//	for (char c : word) {
//		unique = true;
//		//check to see if the word is in the collection of used characters
//		for (unsigned int j = 0; j < check.size(); j++) {
//			if (c == check[j]) { //if current char has been used before
//				id.push_back(j + 1); //add non-unique number to id
//				unique = false;
//			}
//		}
//		//else, add the new unique number to the id and checker lists
//		if (unique) {
//			check.push_back(c);
//			id.push_back(i);
//			i++;
//		}
//
//	}
//
//	unsigned long long int out = 0;
//	for (int k = 0; k < id.size(); k++) {
//		out = (unsigned long long int)(pow(10, id.size() - 1 - k)*id[k] + out); //vector to int
//	}
//
//	if (out < 0) {
//		return out * -1;
//	}
//	else {
//		return out;
//	}
//
//}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
