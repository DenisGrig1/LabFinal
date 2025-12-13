#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>
#include <vector>
using namespace std;

int rand_key() {
	return 1 + rand() % 25;
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

void create_json(string text, string id) {
	if (ifstream("main.json")) {
		string line; ifstream i_json("main.json");
		ofstream json("main2.json");
		while (getline(i_json, line)) {
			if (line == "]") break;
			if (line[line.length() - 1] == '}') line += ",";
			json << line << "\n";
		}
		json << "\t{\"id\":\"" << id << "\",\"content\":\"" << text << "\"}" << "\n";
		json << "]";
		i_json.close(); json.close();
		remove("main.json");
		rename("main2.json", "main.json");
	}
	else {
		ofstream json("main.json");
		json << "[\n";
		json << "\t{\"id\":\"" << id << "\",\"content\":\"" << text << "\"}" << "\n";
		json << "]";
		json.close();
	}
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
			json << "\t\t\"ts\":\"" << caesar(texts[i], key, false) << "\",\n";
			json << "\t\t\"op\":\"" << texts[i] << "\",\n";
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
			json << "\t\t\"ts\":\"" << caesar(texts[i], key, false) << "\",\n";
			json << "\t\t\"op\":\"" << texts[i] << "\",\n";
			json << "\t\t\"key\":\"" << key << "\",\n";
			json << "\t\t\"id\":\"" << id << "\"\n";
			json << (i == texts.size() - 1 ? "\t}\n" : "\t},\n");
		}
		json << "]";
		json.close();
	}
}

vector <string> read_json(string id, int key) {
	vector<string> v;
	ifstream json("main.json"); string str, part;
	while (getline(json, str)) {
		if (str != "[" && str != "]") {
			stringstream sstr(str);
			getline(sstr, part, ',');
			if (part.substr(8, id.length()) == id) {
				getline(sstr, part);
				if (part[part.length() - 1] == ',') {
					v.push_back(caesar(part.substr(11, part.length() - 14), key, true));
				}
				else {
					v.push_back(caesar(part.substr(11, part.length() - 13), key, true));
				}
			}
		}
	}
	json.close();
	return v;
}
