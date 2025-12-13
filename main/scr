#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Header.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	string text, command, id; int key = 0;
	vector <string> texts;
	
	cout << setw((118 + 22)/2) << "Программа \"Шифр Цезаря\"\n";
	cout << "Чтобы посмотреть справочник, введите --help\n";
	
	while (true) {
		cin >> command;
		if (command == "--help") {
			cout << "\n--input - ввод текста\n--output - вывод зашифрованного текста по id\n--key - генерация ключа\n--exit - выход из программы\n\n";
		}
		else if (command == "--input") {
			cout << "Введите текст: ";
			cin.ignore();
			getline(cin, text);
			cout << "Введите id текста: ";
			cin >> id;
			create_json(text, id);
			cout << "текст записан\n";
		}
		else if (command == "--output") {
			if (!key) { 
				key = rand_key(); 
				cout << "Ваш ключ : " << key << "\n";
			}
			cout << "Введите id : ";
			cin.ignore();
			cin >> id;
			texts = read_json(id, key);
			for (string text : texts) cout << text << "\n";
			create_log_json(texts, id, key);
		}
		else if (command == "--key") {
			key = rand_key();
			cout << "Ваш ключ : " << key << "\n";
		}
		else if (command == "--exit") {
			break;
		}
		else cout << "Неизвестная комманда\n";
	}
}
