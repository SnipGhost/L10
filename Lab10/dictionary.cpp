//--------------------------------------------------------------------------
// File: dictionary.cpp
//--------------------------------------------------------------------------
#include "dictionary.h"
//--------------------------------------------------------------------------
Word::~Word()
{
	if (DEBUG) cout << "[..] Удаление слова (" << ru << "/" << en << ")\n";
	delete [] ru;
	delete [] en;
	if (DEBUG) cout << "[OK] Удаление слова (---/---)\n";
}
//--------------------------------------------------------------------------
Dictionary::Dictionary()
{
	size = DICT_LEN;
	count = 0;
	mode = 1;
	if (DEBUG) cout << "[..] Инициализация словаря\n";
	w = new Word *[size];
	if (DEBUG) cout << "[OK] Инициализация словаря\n";
}
//--------------------------------------------------------------------------
Dictionary::~Dictionary()
{
	if (DEBUG) cout << "[..] Удаление словаря\n";
	for (unsigned i = 0; i < count; ++i) delete w[i];
	if (DEBUG) cout << "[OK] Удаление словаря\n";
}
//---------------------------------------------------------------------------
char * Dictionary::viewMode() { return (mode) ? "EN-RU" : "RU-EN"; }
//---------------------------------------------------------------------------
void Dictionary::toggleMode()
{
	mode = !mode;
	cout << "Текущий режим словаря: " << viewMode() << endl;
}
//---------------------------------------------------------------------------
void Dictionary::sort(bool type)
{
	for (unsigned i = 0; i < count; ++i)
	{
		Word *m = w[i];
		unsigned index = i;
		for (unsigned j = i+1; j < count; ++j)
		{
			int cp = (mode) ? strcmp(w[j]->en, m->en) : strcmp(w[j]->ru, m->ru);
			if ((type) ? cp > 0 : cp < 0) {
				m = w[j];
				index = j;
			}
		}
		w[index] = w[i];
		w[i] = m;
	}
}
//---------------------------------------------------------------------------
void Dictionary::add(char *eng, char *rus)
{
	if (count >= size) {
		if (DEBUG) cout << "[..] Выделение дополнительной памяти\n";
		Word **buf = new Word *[size + STEP_ALLOC];
		for (unsigned i = 0; i < count; ++i) buf[i] = w[i];
		delete w;
		w = buf;
		size += STEP_ALLOC;
		if (DEBUG) cout << "[OK] Выделение дополнительной памяти\n";
	}
	if (DEBUG) cout << "[..] Создание нового слова\n";
	Word *new_word = new Word;
	new_word->en = new char[strlen(eng)+1];
	new_word->ru = new char[strlen(rus)+1];
	strcpy_s(new_word->en, strlen(eng)+1, eng);
	strcpy_s(new_word->ru, strlen(rus)+1, rus);
	w[count] = new_word;
	count++;
	if (DEBUG) cout << "[OK] Создание нового слова\n";
}
//---------------------------------------------------------------------------
void Dictionary::print(ostream &output)
{
	for (unsigned i = 0; i < count; ++i)
		output << w[i]->en << " " << w[i]->ru << endl;
}
//---------------------------------------------------------------------------
void Dictionary::loadWords(istream &in)
{
	if (DEBUG) cout << "[..] Чтение потока\n";
	const int maxlen = 256;
	char line[maxlen], *token, *next_token;
	const char *delims = ":|- =";
	in.ignore(maxlen, '\n');
	in.clear();
	while (in.getline(line, maxlen)) 
	{
		if (strlen(line) == 0) break;
		token = strtok_s(line, delims, &next_token);
		add(token, next_token);
	}
	if (DEBUG) cout << "[OK] Чтение потока\n";
}
//---------------------------------------------------------------------------