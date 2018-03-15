#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;

private:
	vector <char> m_delims; 
	int m_size;

};



TokenizerImpl::TokenizerImpl(string separators= ",;:.!()[]{}-\"#$%^&")
{//Construct tokenizer

//Create separator vector 
	int i = 0;
	for (char c : separators) { //O(P)
		if (!c == '\'') //"Apostrophes must not be used as a separator when tokenizing" 
		{
			m_delims.push_back(c); //All characters input are a separator
			i++;
		}

	}
	m_size = i;
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
	vector<string> tokens;
	string currWord="";

	for(char c: s){//Loop through string
		for (int i = 0; i < m_size; i++) { //Check with all delimeters
			if (c == m_delims[i]) { //O(SP)
				//End of token, add to vector
				tokens.push_back(currWord);
				currWord = "";
			}
		}
		currWord += c; //Keep adding letters to the token were building
	}
    return tokens;  
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
