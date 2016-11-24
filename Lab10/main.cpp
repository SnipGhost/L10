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
	cout << "8. Выход\n";
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
	fstream file;
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
					file.open(path);
					if (file.fail()) cout << "Ошибка чтения файла\n";
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
				file.open(path);
				if (file.fail()) cout << "Ошибка чтения файла\n";
				else {
					dict.print(file);
					file.close();
				}
				break;
			case '7':
				dict.changeMode();
				break;
			case '8':
				cout << "Завершение работы программы\n";
				return 0;
				break;
			default:
				cout << "Нет такой операции ..." << endl;
		}
		system("pause");
	} while (c != '8');
	return 0;
}
//---------------------------------------------------------------------------