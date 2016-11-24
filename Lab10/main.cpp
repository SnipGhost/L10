//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "dictionary.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
void menu(char &c, Dictionary &dict)
{
	system("cls");
	system("chcp 1251 > nul");
	cout << "================= ������� =================\n";
	cout << "1. �������� ����� � �������.\n";
	cout << "2. ������� ����� �� �������.\n";
	cout << "3. ������� ���������� �����.\n";
	cout << "4. ����� ����� � �������.\n";
	cout << "5. �������� �������.\n";
	cout << "6. ����� ������� � ����.\n";
	cout << "7. ����� ������ �������.\n";
	cout << "8. �����\n";
	cout << "===========================================\n";
	cout << " ����� �������: " << dict.viewMode(); 
	cout << endl;
	cout << "===========================================\n";
	cin >> c;
}
//---------------------------------------------------------------------------
int main()
{
	char c, r;
	char path[256] = "";
	fstream file;
	Dictionary dict;
	do {
		menu(c, dict);
		switch (c) {
			case '1':
			{
				cout << "�������� ����� �� �����? (y/n) ";
				cin >> r;
				if (r == 'y') {
					cout << "������� ��� �����: ";		
					cin >> path;
					file.open(path);
					if (file.fail()) cout << "������ ������ �����\n";
					else {
						loadWords(file, dict);
						file.close();
					}
				} else {
					loadWords(cin, dict);
				}
				break;
			}
			case '2':
				cout << "�� ������\n";
				break;
			case '3':
				cout << "�� ������\n";
				break;
			case '4':
				cout << "�� ������\n";
				break;
			case '5':
				dict.print(cout);
				break;
			case '6':
				cout << "������� ��� ����� ��� ������: ";		
				cin >> path;
				file.open(path);
				if (file.fail()) cout << "������ ������ �����\n";
				else {
					dict.print(file);
					file.close();
				}
				break;
			case '7':
				dict.changeMode();
				break;
			case '8':
				cout << "���������� ������ ���������\n";
				return 0;
				break;
			default:
				cout << "��� ����� �������� ..." << endl;
		}
		system("pause");
	} while (c != '8');
	return 0;
}
//---------------------------------------------------------------------------