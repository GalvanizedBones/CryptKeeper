#include "provided.h"
#include <string>
#include <vector>
#include "MyHash.h"
#include <fstream>
#include <locale>         // std::locale, std::isalpha

using namespace std;

class WordListImpl
{
public:
	WordListImpl();
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;

	int hasher(string word); //custom pattern hash
private:
	MyHash<int, string> theList; //Id to string
};

WordListImpl::WordListImpl() 
	: theList() //Use default constrcutro
{
	; //Do nothing
}

bool WordListImpl::loadWordList(string filename)
{
	theList.reset(); //Removes all data, sets to initial hash of 100 buckets

	locale loc;

	ifstream file("wordlist.txt");
	string str;
	bool write = false;
	while (getline(file, str))
	{
		//Check if word contains not a letter or an apostrophe
		bool allGoodChars = true;
		for (char c : str) {
			if (c == '\'' ||  std::isalpha((unsigned char) c, loc) ) {
				allGoodChars = true;
			}
			else {
				allGoodChars = false;
			}
		}
		if (allGoodChars) {
			write = true;
			// Process str

			//We currently have a string
			//Associate a unique ID

			//Associate a pattern ID 
			int ID = hasher(str);

			//For now, lets just use the pattern ID
			//int ID = hash(str);
			theList.associate(ID, str);
		}
	}

	if (write) { return true; }
	else { return false; }
}


int WordListImpl::hasher(string word) {

	////loop through characters of the string
	//int i = 1;
	//vector<int> ID; 
	//vector<char> check;
	//bool unique = true;
	//for (char c : word) {
	//	unique = true;
	//	//Check to see if the word is in the collection of used characters
	//	for (int j = 0; j < check.size(); j++) {
	//		if (c == check[j]) { //if current char has been used before
	//			ID.push_back(j + 1); //Add non-unique number to ID
	//			unique = false;
	//		}
	//	}
	//	//else, add the new unique number to the ID and checker lists
	//	if (unique) {
	//		check.push_back(c);
	//		ID.push_back(i);
	//		i++;
	//	}

	//}

	//int out = 0;
	//for (int k = ID.size()-1; k > 0 ; k--) {
	//	out = pow(10,k)*ID[k] + out; //vector to int
	//}

	//return out; //Return pattern (not unique)
	//********** OVER FLOW ERRORS ON LARGE WORDS
			//64 BIT INT?
				//SENDING 2 INTS?

	int out = std::hash<std::string>()(word) ;

	if (out < 0) {
		return out * -1;
	}
	else {
		return out; 
	}


}

bool WordListImpl::contains(string word) const
{
    return false; // This compiles, but may not be correct
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    return vector<string>();  // This compiles, but may not be correct
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
