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
	cout << "================= Словарь =================\n";
	cout << " " << char(ADD_WORDS) << ". Добавить слова в словарь.\n";
	cout << " " << char(DELETE_WORDS) << ". Удалить слова из словаря.\n";
	cout << " " << char(TRANSLATE_WORDS) << ". Перевод указанных слов.\n";
	cout << " " << char(VIEW_DICTIONARY) << ". Просмотр словаря.\n";
	cout << " " << char(SAVE_DICTIONARY) << ". Вывод словаря в файл.\n";
	cout << " " << char(TOGGLE_MODE) << ". Смена режима словаря.\n";
	cout << " " << char(SORT_DICTIONARY) << ". Сортиовка словаря.\n";
	cout << " " << char(END_PROGRAM) << ". Выход\n";
	cout << "===========================================\n";
	cout << " Режим словаря: " << dict.viewMode(); 
	cout << endl;
	cout << "===========================================\n";
	cout << " МГТУ им Н.Э.Баумана ИУ5-14 | By SnipGhost \n";
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
					cout << "Вводите по два слова через пробел, завершите пустой строкой:\n";
					cin.ignore(MAX_LEN, '\n');
					cin.clear();
					dict.loadWords(cin);
				}
				break;

			case DELETE_WORDS:
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
					cout << "Вводите слова, завершите пустой строкой:\n";
					cin.ignore(MAX_LEN, '\n');
					cin.clear();
					dict.del(cin);
				}	
				break;

			case TRANSLATE_WORDS:
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

			case VIEW_DICTIONARY:
				dict.print(cout);
				break;

			case SAVE_DICTIONARY:
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

			case TOGGLE_MODE:
				dict.toggleMode();
				break;

			case SORT_DICTIONARY:
				cout << "По убыванию/возрастанию? (y - по убыванию) ";
				cin >> r;
				dict.sort(!(r == 'y'));
				break;

			case END_PROGRAM:
				cout << "Завершение работы программы\n";
				return 0;
				break;

			default:
				cout << "Нет такой операции ..." << endl;
		}
		cout << endl;
		system("pause");
	}
}
//---------------------------------------------------------------------------