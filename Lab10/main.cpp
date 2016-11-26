//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "dictionary.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
char menu(Dictionary &dict)
{
	system("cls");
	system("chcp 1251 > nul");
	cout << "================= Словарь =================\n";
	cout << "1. Добавить слова в словарь.\n";
	cout << "2. Удалить слова из словаря.\n";
	cout << "3. Перевод указанных слов.\n";
	cout << "4. Просмотр словаря.\n";
	cout << "5. Вывод словаря в файл.\n";
	cout << "6. Смена режима словаря.\n";
	cout << "7. Сортиовка словаря.\n";
	cout << "q. Выход\n";
	cout << "===========================================\n";
	cout << " Режим словаря: " << dict.viewMode(); 
	cout << endl;
	cout << "===========================================\n";
	char c;
	cin >> c;
	return c;
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
		switch (menu(dict)) {
			case '1':
				cout << "Добавить слова из файла? (f/-) ";
				cin >> r;
				if (r == 'f') {
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
					cin.ignore(MAX_LEN, '\n');
					cin.clear();
					dict.loadWords(cin);
				}
				break;
			case '2':
				cout << "Удалить все слова, которые есть в файле? (f/-) ";
				cin >> r;
				if (r == 'f') {
					cout << "Введите имя файла: ";		
					cin >> path;
					ifile.clear();
					ifile.open(path);
					if (ifile.fail()) cout << "Ошибка чтения файла\n";
					else {
						dict.del(ifile);
						ifile.close();
					}
				} else {
					cin.ignore(MAX_LEN, '\n');
					cin.clear();
					dict.del(cin);
				}	
				break;
			case '3':
			{
				cout << "Ввод из файла? (f/-) ";
				cin >> r;
				cout << "Выводить в файл? (f/-) ";
				cin >> t;
				if (r == 'f') {
					cout << "\nВведите имя входного файла: ";		
					cin >> path;
					ifile.clear();
					ifile.open(path);
					if (ifile.fail()) {
						cout << "Ошибка чтения входного файла\n";
						break;
					}
				} else {
					cin.ignore(MAX_LEN, '\n');
					cin.clear();
				}
				if (t == 'f') {
					cout << "\nВведите имя файла для вывода: ";		
					cin >> path;
					ofile.clear();
					ofile.open(path);
					if (ofile.fail()) {
						cout << "Ошибка чтения выходного файла\n";
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
			case '4':
				dict.print(cout);
				break;
			case '5':
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
			case '6':
				dict.toggleMode();
				break;
			case '7':
				cout << "По убыванию/возрастанию? (y - по убыванию) ";
				cin >> r;
				dict.sort(!(r == 'y'));
				break;
			case 'q':
				cout << "Завершение работы программы\n";
				return 0;
				break;
			default:
				cout << "Нет такой операции ..." << endl;
		}
		system("pause");
	}

}
//---------------------------------------------------------------------------