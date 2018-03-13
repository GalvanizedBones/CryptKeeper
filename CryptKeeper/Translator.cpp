#include "provided.h"
#include <string>
#include<stack>
#include "MyHash.h"
#include <locale>         // std::locale, std::isalpha
#include <stdio.h>
#include <ctype.h>

using namespace std;


class TranslatorImpl
{
public:
	TranslatorImpl(); 
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
	int m_pushed;
	int m_popped;
	stack<MyHash<char,char>*> m_Codes;
	MyHash<char, char>* m_currTable; 

};

TranslatorImpl::TranslatorImpl() 
	: m_pushed(0),
	m_popped(0)
{
	MyHash<char,char>* def = new MyHash<char,char>(2, 26); //High load factor, 26 letters
	m_Codes.push(def); //The bottom most code, is never deleted
	m_currTable = m_Codes.top();
}


bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    return false;  // This compiles, but may not be correct
}

bool TranslatorImpl::popMapping()
{
	if (m_pushed == m_popped) {
		//an empty stack
		m_pushed = m_popped = 0; //Reset, overflow protection
		return false;
	}
	else {
		MyHash<char, char>* temp = m_Codes.top();
		m_Codes.pop();
		m_popped++;
		delete temp; //Dynamic memory cant just be popped away
		return true;
	}
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	string translated = "";
	locale loc;

	for (char c : ciphertext) {
		if (isalpha((unsigned char)c, loc))
		{
			char decodeC = tolower(*m_currTable->find(c));
			if (isupper(c)) {
				c = toupper(c);
			}
			translated += c;
		}
		else {
			translated += c; //some sort of punctiation
		}
	}

	return translated;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
