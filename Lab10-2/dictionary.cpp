//--------------------------------------------------------------------------
// File: dictionary.cpp
//--------------------------------------------------------------------------
#include "dictionary.h"
//--------------------------------------------------------------------------
const char *delims = " ,.!?:;/\\|-+=()<>{}[]#'\"";
//--------------------------------------------------------------------------
Word::Word()
{
	if (DEBUG) cout << "[..] ������������� �����\n";
	strcpy_s(en, 1, "");
	strcpy_s(ru, 1, "");
	if (DEBUG) cout << "[OK] ������������� �����\n";
}
//--------------------------------------------------------------------------
Word::Word(const char *eng, const char *rus)
{
	if (DEBUG) cout << "[..] ������������� �����\n";
	unsigned len1 = strlen(eng) + 1, len2 = strlen(rus) + 1;
	strcpy_s(en, len1, eng);
	strcpy_s(ru, len2, rus);
	if (DEBUG) cout << "[OK] ������������� �����\n";
}
//--------------------------------------------------------------------------
Dictionary::Dictionary()
{
	if (DEBUG) cout << "[..] ������������� �������\n";
	count = 0;
	mode = 1;
	if (DEBUG) cout << "[OK] ������������� �������\n";
}
//---------------------------------------------------------------------------
// ����������� ����� �������
//---------------------------------------------------------------------------
char * Dictionary::viewMode() 
{ 
	return (mode) ? "EN-RU" : "RU-EN"; 
}
//---------------------------------------------------------------------------
// ������� ����� �������
//---------------------------------------------------------------------------
void Dictionary::toggleMode()
{
	mode = !mode;
	cout << "������� ����� �������: " << viewMode() << endl;
}
//---------------------------------------------------------------------------
// ���������� �� ��������, ������������ type (0: �-�, 1: �-�)
//---------------------------------------------------------------------------
void Dictionary::sort(bool type)
{
	for (unsigned i = 0; i < count; ++i)
	{
		Word m = w[i];
		unsigned index = i;
		for (unsigned j = i+1; j < count; ++j)
		{
			int cp = mode ? strcmp(w[j].en, m.en) : strcmp(w[j].ru, m.ru);
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
// �������� ���� ���-��� � �������
//---------------------------------------------------------------------------
void Dictionary::add(Word new_word)
{
	if (count >= DICT_LEN) {
		cout << " ������������ ������ ";
		return;
	}
	if (DEBUG) cout << "[..] ���������� ������ �����\n";
	w[count] = new_word;
	count++;
	if (DEBUG) cout << "[OK] ���������� ������ �����\n";
}
//---------------------------------------------------------------------------
// ����� ���������� ����� � �������
//---------------------------------------------------------------------------
int Dictionary::search(const char *word)
{
	if (count == 0) return -1;
	sort(0);
	unsigned a = 0, b = count-1, c = count;
	if (DEBUG) cout << "[..] �������� ����� �����\n";
	while (a <= b && b != c && a != c) 
	{
		c = (a + b) / 2;	
		if (DEBUG) cout << a << " " << c << " " << b << endl;
		int cp = (mode) ? strcmp(word, w[c].en) : strcmp(word, w[c].ru);
		if (cp == 0) {
			if (DEBUG) cout << "[OK] �������� ����� �����\n";
			return c;
		}
		else if (cp > 0) a = c + 1;
		else b = c - 1;
	}
	if (DEBUG) cout << "[NO] �������� ����� �����\n";
	return -1;
}
//---------------------------------------------------------------------------
// ����� � ������� ���� (�� ������)
//---------------------------------------------------------------------------
void Dictionary::translate(istream &in, ostream &out)
{
	char line[MAX_LEN], *token, *next_token;
	if (DEBUG) cout << "[..] ������ ������\n";
	while (in.getline(line, MAX_LEN) && count > 0) 
	{
		if (strlen(line) == 0) break;
		token = strtok_s(line, delims, &next_token);
		while (token != NULL) {
			int ind = search(token);
			if (ind == -1) out << "'" << token << "' ";
			else out << ((mode) ? w[ind].ru : w[ind].en) << " ";
			token = strtok_s(NULL, delims, &next_token);
		}
		out << endl;
	}
	if (DEBUG) cout << "[OK] ������ ������\n";
}
//---------------------------------------------------------------------------
// ������� ��� ��������� � ������ (������� �����) ����� �� �������
//---------------------------------------------------------------------------
void Dictionary::del(istream &in)
{
	if (DEBUG) cout << "[..] ������ ������\n";
	char line[MAX_LEN], *token, *next_token;
	while (in.getline(line, MAX_LEN) && count > 0) 
	{
		if (strlen(line) == 0) break;
		token = strtok_s(line, delims, &next_token);
		while (token != NULL)
		{
			int st = search(token);
			if (DEBUG) cout << "[..] �������� ���� ����� �����\n";
			while (st != -1) {
				for (unsigned i = st; i < count-1; ++i)
					w[i] = w[i+1];
				count--;
				st = search(token);
			}
			if (DEBUG) cout << "[OK] �������� ���� ����� �����\n";
			token = strtok_s(NULL, delims, &next_token);
		}
	}
	if (DEBUG) cout << "[OK] ������ ������\n";
}
//---------------------------------------------------------------------------
// ����������� ���� �������
//---------------------------------------------------------------------------
void Dictionary::print(ostream &output)
{
	for (unsigned i = 0; i < count; ++i)
		if (mode) output << w[i].en << " " << w[i].ru << endl;
		else output << w[i].ru << " " << w[i].en << endl;
}
//---------------------------------------------------------------------------
// ���������� ����� �� ��� �������
//---------------------------------------------------------------------------
void Dictionary::printWord(ostream &output, unsigned index)
{
	if (mode) output << w[index].en << " " << w[index].ru << endl;
	else output << w[index].ru << " " << w[index].en << endl;
}
//---------------------------------------------------------------------------
// ��������� ����� �� ������
//---------------------------------------------------------------------------
void Dictionary::loadWords(istream &in)
{
	if (DEBUG) cout << "[..] ������ ������\n";
	char line[MAX_LEN], *token, *next_token;
	while (in.getline(line, MAX_LEN)) 
	{
		if (strlen(line) == 0) break;
		token = strtok_s(line, delims, &next_token);
		if (!mode) {
			char *buf = token;
			token = next_token;
			next_token = buf;
		}
		Word new_word(token, next_token);
		add(new_word);
	}
	if (DEBUG) cout << "[OK] ������ ������\n";
}
//---------------------------------------------------------------------------