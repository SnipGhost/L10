//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "dictionary.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
enum Action {
	ADD_WORDS = '1',
	DELETE_WORDS,
	TRANSLATE_WORDS,
	VIEW_DICTIONARY,
	SAVE_DICTIONARY,
	TOGGLE_MODE,
	SORT_DICTIONARY,
	END_PROGRAM = 'q'
};
//---------------------------------------------------------------------------
Action menu(Dictionary &dict)
{
	system("cls");
	system("chcp 1251 > nul");
	cout << "================= ������� =================\n";
	cout << " " << char(ADD_WORDS) << ". �������� ����� � �������.\n";
	cout << " " << char(DELETE_WORDS) << ". ������� ����� �� �������.\n";
	cout << " " << char(TRANSLATE_WORDS) << ". ������� ��������� ����.\n";
	cout << " " << char(VIEW_DICTIONARY) << ". �������� �������.\n";
	cout << " " << char(SAVE_DICTIONARY) << ". ����� ������� � ����.\n";
	cout << " " << char(TOGGLE_MODE) << ". ����� ������ �������.\n";
	cout << " " << char(SORT_DICTIONARY) << ". ��������� �������.\n";
	cout << " " << char(END_PROGRAM) << ". �����\n";
	cout << "===========================================\n";
	cout << " ����� �������: " << dict.viewMode(); 
	cout << endl;
	cout << "===========================================\n";
	cout << " ���� �� �.�.������� ��5-14 | By SnipGhost \n";
	cout << "===========================================\n";
	char c;
	cin >> c;
	return Action(c);
}
//---------------------------------------------------------------------------
int main()
{
	char c = 0, r, t;
	char path[MAX_LEN] = "";
	ifstream ifile;
	ofstream ofile;
	Dictionary dict;
	while (true) {
		switch (menu(dict)) 
		{
			case ADD_WORDS:
				cout << "�������� ����� �� �����? (f/-) ";
				cin >> r;
				if (r == 'f') {
					cout << "������� ��� �����: ";		
					cin >> path;
					ifile.clear();
					ifile.open(path);
					if (ifile.fail()) cout << "������ ������ �����\n";
					else {
						dict.loadWords(ifile);
						ifile.close();
						dict.sort(0);
					}
				} else {
					cout << "������� �� ��� ����� ����� ������, ��������� ������ �������:\n";
					cin.ignore(MAX_LEN, '\n');
					cin.clear();
					dict.loadWords(cin);
				}
				break;

			case DELETE_WORDS:
				cout << "������� ��� �����, ������� ���� � �����? (f/-) ";
				cin >> r;
				if (r == 'f') {
					cout << "������� ��� �����: ";		
					cin >> path;
					ifile.clear();
					ifile.open(path);
					if (ifile.fail()) cout << "������ ������ �����\n";
					else {
						dict.del(ifile);
						ifile.close();
					}
				} else {
					cout << "������� �����, ��������� ������ �������:\n";
					cin.ignore(MAX_LEN, '\n');
					cin.clear();
					dict.del(cin);
				}	
				break;

			case TRANSLATE_WORDS:
			{
				cout << "���� �� �����? (f/-) ";
				cin >> r;
				cout << "�������� � ����? (f/-) ";
				cin >> t;
				if (r == 'f') {
					cout << "\n������� ��� �������� �����: ";		
					cin >> path;
					ifile.clear();
					ifile.open(path);
					if (ifile.fail()) {
						cout << "������ ������ �������� �����\n";
						break;
					}
				} else {
					cin.ignore(MAX_LEN, '\n');
					cin.clear();
				}
				if (t == 'f') {
					cout << "\n������� ��� ����� ��� ������: ";		
					cin >> path;
					ofile.clear();
					ofile.open(path);
					if (ofile.fail()) {
						cout << "������ ������ ��������� �����\n";
						break;
					}
				}
				if (r == 'f' && t == 'f') dict.translate(ifile, ofile);
				else if (r == 'f' && t != 'f') dict.translate(ifile, cout);
				else if (r != 'f' && t == 'f') dict.translate(cin, ofile);
				else dict.translate(cin, cout);
				ifile.close();
				ofile.close();
				break;
			}

			case VIEW_DICTIONARY:
				dict.print(cout);
				break;

			case SAVE_DICTIONARY:
				cout << "������� ��� ����� ��� ������: ";		
				cin >> path;
				ofile.clear();
				ofile.open(path);
				if (ofile.fail()) cout << "������ ������ �����\n";
				else {
					dict.print(ofile);
					ofile.close();
				}
				break;

			case TOGGLE_MODE:
				dict.toggleMode();
				break;

			case SORT_DICTIONARY:
				cout << "�� ��������/�����������? (y - �� ��������) ";
				cin >> r;
				dict.sort(!(r == 'y'));
				break;

			case END_PROGRAM:
				cout << "���������� ������ ���������\n";
				return 0;
				break;

			default:
				cout << "��� ����� �������� ..." << endl;
		}
		cout << endl;
		system("pause");
	}
}
//---------------------------------------------------------------------------