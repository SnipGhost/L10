//---------------------------------------------------------------------------
// File: dictionary.cpp
//---------------------------------------------------------------------------
#include "dictionary.h"
//---------------------------------------------------------------------------
Dictionary::Dictionary()
{
	w = NULL;
	size = 100;
	count = 0;
	mode = 0;	
	w = new Word[size];
}
//---------------------------------------------------------------------------
Dictionary::~Dictionary()
{
	if (w != NULL) delete [] w;
	if (DEBUG) cout << "���������� ���������" << endl;
}
//---------------------------------------------------------------------------
char * Dictionary::viewMode()
{
	return (mode) ? "EN-RU" : "RU-EN";
}
//---------------------------------------------------------------------------
void Dictionary::print(ostream &out)
{
	out << endl;
}
//---------------------------------------------------------------------------