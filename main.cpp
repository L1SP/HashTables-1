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
				cout << "������� �������� �� �����.\n";
				isInitialized = 1;
			}
			else {
				cout << "������� ��� ���� ��������.\n";
			}
			break;
		}
		case '2': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "������� �� ����������������.\n";
				break;
			}
			cout << "������� �������(� ������� /����/�/����������/):\n";
			File f;
			cin >> f.cat;
			cout << "������� ��� �����:\n";
			cin >> f.name;
			cout << "������� ���������� �����:\n";
			cin >> f.ext;
			cout << "������� ���� �������� �����(� ������� �� �� ����):\n";
			cin >> f.date.day>>f.date.month>>f.date.year;
			cout << "������� ������ �����(� ������):\n";
			cin >> f.size;
			hashTable.insert(f.getKey(hashTable.Capacity()), f.getValue());
			cout << "������� ��������.\n";
			break;
		}
		case '3': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "������� �� ����������������.\n";
				break;
			}
			File f;
			cout << "������� ����������:\n";
			cin >> f.cat;
			cout << "������� ��� �����:\n";
			cin >> f.name;
			if (hashTable.remove(f.getKey(hashTable.Capacity())))
				cout << "�������� � ����� ������ ������� �������.\n";
			else
				cout << "������� � ����� ������ �� ������.\n";
			break;
		}
		case '4': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "������� �� ����������������.\n";
				break;
			}
			File f;
			cout << "������� ����������:\n";
			cin >> f.cat;
			cout << "������� ��� �����:\n";
			cin >> f.name;
			if (hashTable.find(f.getKey(hashTable.Capacity())))
				cout << "������� � ����� ������ ���� � �������.\n";
			else
				cout << "������� � ����� ������ �� ������.\n";
			break;
		}
		case '5': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "������� �� ����������������.\n";
				break;
			}
			hashTable.print();
			break;
		}
		case '6': {
			system("CLS");
			printMenu();
			if (!isInitialized) {
				cout << "������� �� ����������������.\n";
				break;
			}
			hashTable.clear();
			cout << "������� �������.\n";
			break;
		}
		}
	}
	return 0;
}

void printMenu() {
	cout << "�������� ����� ����:\n";
	cout << "1. ���������������� �������(�� �����)\n";
	cout << "2. �������� �������.\n";
	cout << "3. ������� ������� �� �����.\n";
	cout << "4. ����� ������� �� �����.\n";
	cout << "5. ���������� �������.\n";
	cout << "6. �������� �������.\n";
	cout << "7. ��������� ������ ���������.\n";
}