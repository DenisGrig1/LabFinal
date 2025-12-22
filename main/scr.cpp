#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Header.h"
#include <cstdio>
#include <filesystem>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	string text, command, id, file; int key = 0;
	vector <string> texts;
	create_jsons(50);
	
	cout << setw((118 + 22)/2) << "Программа \"Шифр Цезаря\"\n";
	cout << "Чтобы посмотреть справочник, введите --help\n";
	
	while (true) {
		cout << "Введите комманду: ";
		cin >> command;
		if (command == "--help") {
			cout << "\n--output - вывод зашифрованного текста по id\n--key - генерация ключа\n--exit - выход из программы\n\n";
		}
		else if (command == "--output") {
			if (!key) { 
				key = rand_key(); 
				cout << "Ваш ключ : " << key << "\n";
			}
			cout << "Введите название файла: ";
			cin.ignore();
			cin >> file;
			if (!ifstream("JSON_Files/" + file)) {
				cout << "Данного файла не существует. Повторите попытку.\n";
				continue;
			}
			cout << "Введите id : ";
			cin >> id;
			texts = read_json(file, id, key);
			cout << "Зашифрованные тексты: \n";
			for (string text : texts) cout << caesar(text, key, true) << "\n";
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

	filesystem::remove_all("JSON_Files");
}
