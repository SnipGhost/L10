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
	cout << "================= Словарь =================\n";
	cout << "1. Добавить слова в словарь.\n";
	cout << "2. Удалить слова из словаря.\n";
	cout << "3. Перевод указанного слова.\n";
	cout << "4. Поиск слова в словаре.\n";
	cout << "5. Просмотр словаря.\n";
	cout << "6. Вывод словаря в файл.\n";
	cout << "7. Смена режима словаря.\n";
	cout << "8. Сортиовка словаря.\n";
	cout << "q. Выход\n";
	cout << "===========================================\n";
	cout << " Режим словаря: " << dict.viewMode(); 
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
				cout << "Добавить слова из файла? (y/n) ";
				cin >> r;
				if (r == 'y') {
					cout << "Введите имя файла: ";		
					cin >> path;
					ifile.clear();
					ifile.open(path);
					if (ifile.fail()) cout << "Ошибка чтения файла\n";
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
				cout << "Не готово\n";
				break;
			case '3':
				cout << "Не готово\n";
				break;
			case '4':
				cout << "Не готово\n";
				break;
			case '5':
				dict.print(cout);
				break;
			case '6':
				cout << "Введите имя файла для вывода: ";		
				cin >> path;
				ofile.clear();
				ofile.open(path);
				if (ofile.fail()) cout << "Ошибка чтения файла\n";
				else {
					dict.print(ofile);
					ofile.close();
				}
				break;
			case '7':
				dict.toggleMode();
				break;
			case '8':
				cout << "По убыванию/возрастанию? (a/z) ";
				cin >> r;
				if (r == 'a') dict.sort(0);
				else dict.sort(1);
				break;
			case 'q':
				cout << "Завершение работы программы\n";
				break;
			default:
				cout << "Нет такой операции ..." << endl;
		}
		system("pause");
	} while (c != 'q');
	return 0;
}
//---------------------------------------------------------------------------