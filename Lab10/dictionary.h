﻿//---------------------------------------------------------------------------
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
#define DEBUG 1        // Вывод отладочной информации вкл/выкл (1/0)
#define DICT_LEN 2     // Изначальная длина словаря
#define STEP_ALLOC 5   // Кол-во довыделяемой памяти за раз
//--------------------------------------------------------------------------
struct Word
{
	char *en; // Английское слово
	char *ru; // Русское слово
	~Word();  // Следит за принудительным очищением памяти КАЖДОГО слова
};
//---------------------------------------------------------------------------
class Dictionary
{
	private:
		Word **w;        // Массив слов (пары значений руское:английское)
		unsigned count;  // Количество уже заданных слов
		unsigned size;   // Текущее кол-во выделенной памяти
		bool mode;       // Режим словаря (1: EN-RU, 0: RU-EN)

	public:
		Dictionary();
		~Dictionary();
		char *viewMode();     // Просмотреть режим словаря
		void toggleMode();    // Сменить режим словаря
		void sort(bool type); // Сортировка по алфавиту (0: а-я, 1: я-а)
		void add(char *eng, char *rus); // Добавить пару анг-рус в словарь
		unsigned search(char *word);    // Поиск указанного слова в словаре
		//void del(char *word);         // Найти и уничтожить все слова word
		void print(ostream &output); // Распечатать весь словарь
		void printWord(ostream &output, unsigned index); // Напечатать слово
		void loadWords(istream &in); // Загрузить слова из потока
};
//---------------------------------------------------------------------------
#endif /* DICTIONARY_H */
//---------------------------------------------------------------------------