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
#define DEBUG 0        // ����� ���������� ���������� ���/���� (1/0)
#define DICT_LEN 100   // ����������� ����� �������
#define MAX_LEN 64     // ������������ ����� �����
//--------------------------------------------------------------------------
class Word
{
	public:
		char en[MAX_LEN]; // ���������� �����
		char ru[MAX_LEN]; // ������� �����
		Word();
		Word(const char *eng, const char *rus); 
};
//---------------------------------------------------------------------------
class Dictionary
{
	private:
		Word w[DICT_LEN]; // ������ ���� (���� �������� ������:����������)
		unsigned count;   // ���������� ��� �������� ����
		bool mode;        // ����� ������� (1: EN-RU, 0: RU-EN)

	public:
		Dictionary();

		char *viewMode();     // ����������� ����� �������
		void toggleMode();    // ������� ����� �������
		void sort(bool type); // ���������� �� �������� (0: �-�, 1: �-�)

		void add(Word new_word); // �������� �����

		int search(const char *word);              // �������� ����� �����
		void translate(istream &in, ostream &out); // ������� ����

		void del(istream &in);       // ����� � ���������� ��� ����� word

		void print(ostream &output); // ����������� ���� �������
		void printWord(ostream &output, unsigned index); // ���������� �����
		void loadWords(istream &in); // ��������� ����� �� ������
};
//---------------------------------------------------------------------------
#endif /* DICTIONARY_H */
//---------------------------------------------------------------------------