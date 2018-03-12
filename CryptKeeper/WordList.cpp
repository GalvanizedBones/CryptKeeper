#include "provided.h"
#include <string>
#include <vector>
#include "MyHash.h"
#include <fstream>

using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;

	int hash(string word);
private:
	MyHash<int, string> theList; //Id to string
};

bool WordListImpl::loadWordList(string filename)
{
	//theList.reset(); //Removes all data, sets to initial hash of 100 buckets

	ifstream file("wordlist.txt");
	string str;
	bool write = false;
	while (getline(file, str))
	{
		//Check if word contains not a letter or an apostrophe
		bool allGoodChars = true;
		for (char c : str) {
			if (c != ' \' ' or !isalpha(c)) {
				allGoodChars = false;
			}
		}
		if (allGoodChars) {
			write = true;
			// Process str

			//We currently have a string
			//Associate a unique ID

			//Associate a pattern ID 

			//For now, lets just use the pattern ID
			//int ID = hash(str);
			//theList.associate(ID, str);
		}

		if (write) {return true;}
		else {return false;}
		}
	if (write) { return true; }
	else { return false; }
}


int WordListImpl::hash(string word) {

	//loop through characters of the string
	int i = 1;
	vector<int> ID; 
	vector<char> check;
	bool unique = true;
	for (char c : word) {
		unique = true;
		//Check to see if the word is in the collection of used characters
		for (int j = 0; j < check.size(); j++) {
			if (c == check[j]) { //if current char has been used before
				ID.push_back(j + 1); //Add non-unique number to ID
				unique = false;
			}
		}
		//else, add the new unique number to the ID and checker lists
		if (unique) {
			check.push_back(c);
			ID.push_back(i);
			i++;
		}

	}

	int out = 0;
	for (int k = 0; k < i; k++) {
		out = 10*k * ID[k]; //vector to int
	}

	return out; //Return pattern (not unique)



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
