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
	cout << "8. ��������� �������.\n";
	cout << "q. �����\n";
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
	ifstream ifile;
	ofstream ofile;
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
					ifile.clear();
					ifile.open(path);
					if (ifile.fail()) cout << "������ ������ �����\n";
					else {
						dict.loadWords(ifile);
						ifile.close();
						dict.sort(0);
					}
				} else {
					dict.loadWords(cin);
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
				ofile.clear();
				ofile.open(path);
				if (ofile.fail()) cout << "������ ������ �����\n";
				else {
					dict.print(ofile);
					ofile.close();
				}
				break;
			case '7':
				dict.toggleMode();
				break;
			case '8':
				cout << "�� ��������/�����������? (a/z) ";
				cin >> r;
				if (r == 'a') dict.sort(0);
				else dict.sort(1);
				break;
			case 'q':
				cout << "���������� ������ ���������\n";
				break;
			default:
				cout << "��� ����� �������� ..." << endl;
		}
		system("pause");
	} while (c != 'q');
	return 0;
}
//---------------------------------------------------------------------------