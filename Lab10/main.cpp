//---------------------------------------------------------------------------
#include "dictionary.h"
using namespace std;
//---------------------------------------------------------------------------
void menu(char &c, Dictionary &dict)
{
	system("cls");
	system("chcp 1251 > nul");
	cout << "================= ������� =================\n";
	cout << "1. �������� ����� � �������.\n";
	cout << "2. ������� ����� �� �������.\n";
	cout << "3. ������� ���� � ����������� �� �������.\n";
	cout << "4. ������� ���� � �������� �� ����������.\n";
	cout << "5. �������� �������.\n";
	cout << "6. ����� ������� � ����.\n";
	cout << "7. �����\n";
	cout << "===========================================\n";
	cout << " ����� �������: " << dict.viewMode(); 
	cout << endl;
	cout << "===========================================\n";
	if (c != 0) {
		cin.ignore(7777, '\n');
		cin.clear();
	}
	c = cin.get();
}
//---------------------------------------------------------------------------
int main()
{
	char c = 0;
	Dictionary dict;
	do
	{
		menu(c, dict);
		switch (c) {
			case '1':

				break;
			case '2':

				break;
			case '3':

				break;
			case '4':

				break;
			case '5':
				dict.print(cout);
				break;
			case '6':

				break;
			default:
				cout << "No" << endl;
		}
		system("pause");
	} while (c != '7');
	return 0;
}
//---------------------------------------------------------------------------