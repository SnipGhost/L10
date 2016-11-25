﻿//--------------------------------------------------------------------------
// File: dictionary.cpp
//--------------------------------------------------------------------------
#include "dictionary.h"
//--------------------------------------------------------------------------
Word::~Word()
{
	if (DEBUG) cout << "[..] Удаление слова (" << en << "/" << ru << ")\n";
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
// Просмотреть режим словаря
//---------------------------------------------------------------------------
char * Dictionary::viewMode() 
{ 
	return (mode) ? "EN-RU" : "RU-EN"; 
}
//---------------------------------------------------------------------------
// Сменить режим словаря
//---------------------------------------------------------------------------
void Dictionary::toggleMode()
{
	mode = !mode;
	cout << "Текущий режим словаря: " << viewMode() << endl;
}
//---------------------------------------------------------------------------
// Сортировка по алфавиту, определяемая type (0: а-я, 1: я-а)
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
// Добавить пару анг-рус в словарь
//---------------------------------------------------------------------------
void Dictionary::add(const char *eng, const char *rus)
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
// Поиск указанного слова в словаре
//---------------------------------------------------------------------------
int Dictionary::search(const char *word)
{
	if (count == 0) return -1;
	sort(0);
	unsigned a = 0, b = count-1, c = -1, c_old = 0;
	if (DEBUG) cout << "[..] Двоичный поиск слова\n";
	int tp = (mode) ? strcmp(w[b]->en, word) : strcmp(w[b]->ru, word);
	if (tp == 0) {
		if (DEBUG) cout << "[OK] Двоичный поиск слова\n";
		return b;
	}
	while (c != c_old) 
	{
		c_old = c;
		c = (a+b)/2+0.5;	
		int cp = (mode) ? strcmp(w[c]->en, word) : strcmp(w[c]->ru, word);
		if (cp == 0) {
			if (DEBUG) cout << "[OK] Двоичный поиск слова\n";
			return c;
		}
		else if (cp < 0) a = c;
		else b = c;
	}
	if (DEBUG) cout << "[NO] Двоичный поиск слова\n";
	return -1;
}
//---------------------------------------------------------------------------
// Поиск и перевод заданного слова
//---------------------------------------------------------------------------
void Dictionary::translate(istream &in, ostream &out)
{
	char word[MAX_LEN];
	in >> word;
	int ind = search(word);
	if (ind == -1) out << "Слово '" << word << "' не найдено\n";
	else out << ((mode) ? w[ind]->ru : w[ind]->en) << endl;
}
//---------------------------------------------------------------------------
// Удалить ВСЕ заданные слова из словаря
//---------------------------------------------------------------------------
void Dictionary::del(istream &in)
{
	if (DEBUG) cout << "[..] Чтение потока\n";
	char line[MAX_LEN], *token, *next_token;
	const char *delims = ":|- =";
	in.ignore(MAX_LEN, '\n');
	in.clear();
	while (in.getline(line, MAX_LEN) && count > 0) 
	{
		if (strlen(line) == 0) break;
		token = strtok_s(line, delims, &next_token);
		while (token != NULL)
		{
			int st = search(token);
			if (DEBUG) cout << "[..] Удаление всех копий слова\n";
			while (st != -1) {
				delete w[st];
				for (int i = st; i < count-1; ++i)
					w[i] = w[i+1];
				count--;
				st = search(token);
			}
			if (DEBUG) cout << "[OK] Удаление всех копий слова\n";
			token = strtok_s(NULL, delims, &next_token);
		}
	}
	if (DEBUG) cout << "[OK] Чтение потока\n";
}
//---------------------------------------------------------------------------
// Распечатать весь словарь
//---------------------------------------------------------------------------
void Dictionary::print(ostream &output)
{
	for (unsigned i = 0; i < count; ++i)
		if (mode) output << w[i]->en << " " << w[i]->ru << endl;
		else output << w[i]->ru << " " << w[i]->en << endl;
}
//---------------------------------------------------------------------------
// Напечатать слово по его индексу
//---------------------------------------------------------------------------
void Dictionary::printWord(ostream &output, unsigned index)
{
	if (mode) output << w[index]->en << " " << w[index]->ru << endl;
	else output << w[index]->ru << " " << w[index]->en << endl;
}
//---------------------------------------------------------------------------
// Загрузить слова из потока
//---------------------------------------------------------------------------
void Dictionary::loadWords(istream &in)
{
	if (DEBUG) cout << "[..] Чтение потока\n";
	char line[MAX_LEN], *token, *next_token;
	const char *delims = ":|- =";
	in.ignore(MAX_LEN, '\n');
	in.clear();
	while (in.getline(line, MAX_LEN)) 
	{
		if (strlen(line) == 0) break;
		token = strtok_s(line, delims, &next_token);
		if (mode) add(token, next_token);
		else add(next_token, token);
	}
	if (DEBUG) cout << "[OK] Чтение потока\n";
}
//---------------------------------------------------------------------------