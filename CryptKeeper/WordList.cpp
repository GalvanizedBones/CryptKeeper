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


private:
	MyHash<int, string> theList; //Id to string
	MyHash<unsigned long long int, vector<string>  > patternList;

	int  hasher(string word) const;  //stl hash
	unsigned long long int patternhasher(string word) const; //custom pattern hash
};

WordListImpl::WordListImpl()
	: theList(), //Use default constrcutro
	patternList()
{
	; //Do nothing
}

bool WordListImpl::loadWordList(string filename)
{
	theList.reset(); //Removes all data, sets to initial hash of 100 buckets

	locale loc;

	ifstream file(filename);
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
			int ID = hasher(str);
			//Associate a pattern ID 
			unsigned long long int patternID = patternhasher(str);

			//Update lists
			theList.associate(ID, str);
			
			vector<string> *  patternWords =(vector<string> *) patternList.find(patternID);

			if (patternWords != nullptr) { //If a pattern vector already exists, add to it
				(patternWords)->push_back(str);
			}
			else { //Else, make a new pattern vector from scratch
				vector<string>* newBucket = new vector<string>;
				newBucket->push_back(str);
				patternList.associate(patternID, *newBucket);
			}
			//patternList.associate(patternID, str);
		}
	}

	if (write) { return true; }
	else { return false; }
}



unsigned long long int WordListImpl::patternhasher(string word) const {
	//loop through characters of the string

	int i = 1;
	vector<int> id; 
	vector<char> check;
	bool unique = true;
	for (char c : word) {
		unique = true;
		//check to see if the word is in the collection of used characters
		for (unsigned int j = 0; j < check.size(); j++) {
			if (c == check[j]) { //if current char has been used before
				id.push_back(j + 1); //add non-unique number to id
				unique = false;
			}
		}
		//else, add the new unique number to the id and checker lists
		if (unique) {
			check.push_back(c);
			id.push_back(i);
			i++;
		}

	}

	unsigned long long int out = 0;
	for (int k = 0; k < id.size() ; k++) {
		out = (unsigned long long int)(pow(10,id.size()-1 - k)*id[k] + out); //vector to int
	}

	if (out < 0) {
		return out * -1;
	}
	else {
		return out;
	}
	//return pattern (not unique)
	//********** OVER FLOW ERRORS ON LARGE WORDS
	//64 BIT INT?
}

int WordListImpl::hasher(string word) const {

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
	//Check with theList, opposed to patternList for better speed

	int key = hasher(word); //stl hash should have unique keys
	const string * pt =  theList.find(key);

	if (pt == nullptr) {
		return false; //Key not found
	}
	else {
		return true;
	}
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	vector<string> out; 

//#1 patternize the cipherWord
	unsigned long long int patternID = patternhasher(cipherWord);

//#2 find the corresponding vector for the pattern 
	vector<string> * samePatternWords = (vector<string> *) patternList.find(patternID);

	for (int i = 0; i < samePatternWords->size(); i++) {
		//For all possible translations	
			//Make translations!
				//pushMap returns a true/false
					//Push the current cipher with the matchingWordPattern[i]
						//If true, add samePatternWord to out vector



	}




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
