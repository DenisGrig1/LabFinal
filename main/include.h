#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>
#include <vector>
#include <filesystem>
using namespace std;

int rand_key() {
	return 1 + rand() % 25;
}

string rand_text() {
	string result;
	for (int i = 0; i < 1 + (rand() % 1000); i++) {
		result += char(97 + rand() % 26);
	}
	return result;
}

string caesar(string text, int key, bool mode) {
	string new_text = "";
	if (mode) {
		for (char c : text) {
			if (isalpha(c)) {
				char base = islower(c) ? 'a' : 'A';
				new_text += base + (c - base + key) % 26;
			}
			else new_text += c;
		}
	}
	else {
		for (char c : text) {
			if (isalpha(c)) {
				char base = islower(c) ? 'z' : 'Z';
				new_text += base - (base - c + key) % 26;
			}
			else new_text += c;
		}
	}
	return new_text;
}

void create_jsons(int n) {
	filesystem::create_directories("JSON_Files");
	for (int i = 1; i <= n; i++) {
		ofstream json("JSON_Files/file" + to_string(i) + ".json");
		json << "[\n";
		for (int j = 0; j < rand()%1000; j++) {
			json << "\t{\"id\":\"" << char(97 + rand() % 26) + to_string(rand() % 10) << "\",\"content\":\"" << rand_text() << "\"}," << "\n";
		}
		json << "\t{\"id\":\"" << char(97 + rand() % 26) + to_string(rand() % 10) << "\",\"content\":\"" << rand_text() << "\"}" << "\n";
		json << "]";
		json.close();
	}
}

vector <string> read_json(string file, string id, int key) {
	vector<string> texts;
	ifstream json("JSON_Files/" + file); string str, part;
	while (getline(json, str)) {
		if (str != "[" && str != "]") {
			stringstream sstr(str);
			getline(sstr, part, ',');
			if (part.substr(8, id.length()) == id) {
				getline(sstr, part);
				if (part[part.length() - 1] == ',') {
					texts.push_back(part.substr(11, part.length() - 14));
				}
				else {
					texts.push_back(part.substr(11, part.length() - 13));
				}
			}
		}
	}
	json.close();
	return texts;
}

void create_log_json(vector<string> texts, string id, int key) {
	if (ifstream("log.json")) {
		string line; ifstream i_json("log.json");
		ofstream json("log2.json");
		while (getline(i_json, line)) {
			if (line == "]") break;
			if (line[line.length() - 1] == '}') line += ",";
			json << line << "\n";
		}
		for (int i = 0; i < texts.size(); i++) {
			json << "\t\{\n";
			json << "\t\t\"ts\":\"" << texts[i] << "\",\n";
			json << "\t\t\"op\":\"" << caesar(texts[i], key, true) << "\",\n";
			json << "\t\t\"key\":\"" << key << "\",\n";
			json << "\t\t\"id\":\"" << id << "\"\n";
			json << (i == texts.size() - 1 ? "\t}\n" : "\t},\n");
		}
		json << "]";
		json.close(); i_json.close();
		remove("log.json");
		rename("log2.json", "log.json");
	}
	else {
		ofstream json("log.json");
		json << "[\n";
		for (int i = 0; i < texts.size(); i++) {
			json << "\t\{\n";
			json << "\t\t\"ts\":\"" << texts[i] << "\",\n";
			json << "\t\t\"op\":\"" << caesar(texts[i], key, true) << "\",\n";
			json << "\t\t\"key\":\"" << key << "\",\n";
			json << "\t\t\"id\":\"" << id << "\"\n";
			json << (i == texts.size() - 1 ? "\t}\n" : "\t},\n");
		}
		json << "]";
		json.close();
	}
}
