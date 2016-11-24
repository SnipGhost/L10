//--------------------------------------------------------------------------
// File: dictionary.cpp
//--------------------------------------------------------------------------
#include "dictionary.h"
//--------------------------------------------------------------------------
Word::~Word()
{
	if (DEBUG) cout << "[..] �������� ����� (" << ru << "/" << en << ")\n";
	delete [] ru;
	delete [] en;
	if (DEBUG) cout << "[OK] �������� ����� (---/---)\n";
}
//--------------------------------------------------------------------------
Dictionary::Dictionary()
{
	size = DICT_LEN;
	count = 0;
	mode = 0;
	if (DEBUG) cout << "[..] ������������� �������\n";
	w = new Word *[size];
	if (DEBUG) cout << "[OK] ������������� �������\n";
}
//--------------------------------------------------------------------------
Dictionary::~Dictionary()
{
	if (DEBUG) cout << "[..] �������� �������\n";
	for (unsigned i = 0; i < count; ++i) delete w[i];
	if (DEBUG) cout << "[OK] �������� �������\n";
}
//---------------------------------------------------------------------------
char * Dictionary::viewMode() { return (mode) ? "EN-RU" : "RU-EN"; }
//---------------------------------------------------------------------------
void Dictionary::changeMode()
{
	mode = !mode;
	cout << "������� ����� �������: " << viewMode() << endl;
}
//---------------------------------------------------------------------------
void Dictionary::add(char *eng, char *rus)
{
	if (count >= size) {
		if (DEBUG) cout << "[..] ��������� �������������� ������\n";
		Word **buf = new Word *[size + STEP_ALLOC];
		for (int i = 0; i < count; ++i) buf[i] = w[i];
		delete w;
		w = buf;
		size += STEP_ALLOC;
		if (DEBUG) cout << "[OK] ��������� �������������� ������\n";
	}
	if (DEBUG) cout << "[..] �������� ������ �����\n";
	Word *new_word = new Word;
	new_word->en = new char[strlen(eng)+1];
	new_word->ru = new char[strlen(rus)+1];
	strcpy_s(new_word->en, strlen(eng)+1, eng);
	strcpy_s(new_word->ru, strlen(rus)+1, rus);
	w[count] = new_word;
	count++;
	if (DEBUG) cout << "[OK] �������� ������ �����\n";
}
//---------------------------------------------------------------------------
void Dictionary::print(ostream &output)
{
	for (unsigned i = 0; i < count; ++i)
		output << w[i]->en << " - " << w[i]->ru << endl;
}
//---------------------------------------------------------------------------
void loadWords(istream &in, Dictionary &dict)
{
	if (DEBUG) cout << "[..] ������ ������\n";
	const int maxlen = 256;
	char line[maxlen], *token, *next_token;
	const char *delims = ":|- =";
	in.ignore(maxlen, '\n');
	in.clear();
	while (in.getline(line, maxlen)) 
	{
		if (strlen(line) == 0) break;
		token = strtok_s(line, delims, &next_token);
		dict.add(token, next_token);
	}
	if (DEBUG) cout << "[OK] ������ ������\n";
}
//---------------------------------------------------------------------------