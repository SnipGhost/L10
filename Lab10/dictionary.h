//---------------------------------------------------------------------------
// File: dictionary.h
//---------------------------------------------------------------------------
#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H
//---------------------------------------------------------------------------
#include <iostream>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
#define DEBUG 1
#define DICT_LEN 2
#define STEP_ALLOC 5
//--------------------------------------------------------------------------
struct Word
{
	char *en;
	char *ru;
	~Word();
};
//---------------------------------------------------------------------------
class Dictionary
{
	private:
		Word **w;
		unsigned count, size;
		bool mode;

	public:
		Dictionary();
		~Dictionary();
		char *viewMode();
		void changeMode();
		void sort();
		void add(char *eng, char *rus);
		//unsigned search(char *word);
		//void del();
		void print(ostream &out);
		void loadWords(istream &in);
};
//---------------------------------------------------------------------------
#endif /* DICTIONARY_H */
//---------------------------------------------------------------------------