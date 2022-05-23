#include <iostream>
#include <Windows.h>
#include "SeparateChainingTable.h"
#include "File.h"
#include <fstream>
#include <conio.h>

using namespace std;
void printMenu();

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SeparateChainingTable<string, size_t> hashTable(6);
	ifstream ifs("A.txt");
	uint8_t c = 0;
	bool isInitialized = 0;
	printMenu();
	while (c != '7') {
		c=_getch();
		switch (c) {
		case '1': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				hashTable.readFromFile(ifs);
				cout << "Таблица прочтена из файла.\n";
				isInitialized = 1;
			}
			else {
				cout << "Таблица уже была прочтена.\n";
			}
			break;
		}
		case '2': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "Таблица не инициализирована.\n";
				break;
			}
			cout << "Введите каталог(в формате /путь/к/директории/):\n";
			File f;
			cin >> f.cat;
			cout << "Введите имя файла:\n";
			cin >> f.name;
			cout << "Введите расширение файла:\n";
			cin >> f.ext;
			cout << "Введите дату создания файла(в формате ДД ММ ГГГГ):\n";
			cin >> f.date.day>>f.date.month>>f.date.year;
			cout << "Введите размер файла(в байтах):\n";
			cin >> f.size;
			hashTable.insert(f.getKey(hashTable.Capacity()), f.getValue());
			cout << "Элемент добавлен.\n";
			break;
		}
		case '3': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "Таблица не инициализирована.\n";
				break;
			}
			File f;
			cout << "Введите директорию:\n";
			cin >> f.cat;
			cout << "Введите имя файла:\n";
			cin >> f.name;
			if (hashTable.remove(f.getKey(hashTable.Capacity())))
				cout << "Элементы с таким ключом успешно удалены.\n";
			else
				cout << "Элемент с таким ключем не найден.\n";
			break;
		}
		case '4': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "Таблица не инициализирована.\n";
				break;
			}
			File f;
			cout << "Введите директорию:\n";
			cin >> f.cat;
			cout << "Введите имя файла:\n";
			cin >> f.name;
			if (hashTable.find(f.getKey(hashTable.Capacity())))
				cout << "Элемент с таким ключем есть в таблице.\n";
			else
				cout << "Элемент с таким ключем не найден.\n";
			break;
		}
		case '5': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "Таблица не инициализирована.\n";
				break;
			}
			hashTable.print();
			break;
		}
		case '6': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "Таблица не инициализирована.\n";
				break;
			}
			hashTable.clear();
			cout << "Таблица очищена.\n";
			break;
		}
		}
	}
	return 0;
}

void printMenu() {
	cout << "Выберите пункт меню:\n";
	cout << "1. Инициализировать таблицу(из файла)\n";
	cout << "2. Добавить элемент.\n";
	cout << "3. Удалить элемент по ключу.\n";
	cout << "4. Найти элемент по ключу.\n";
	cout << "5. Напечатать таблицу.\n";
	cout << "6. Очистить таблицу.\n";
	cout << "7. Завершить работу программы.\n";
}
