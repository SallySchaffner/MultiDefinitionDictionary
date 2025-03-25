#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "Dictionary.h"

std::string Multi_Def_Dictionary::getLine(const std::string& prompt) {
	std::cout << prompt;
	std::string input;
	std::getline(std::cin, input);
	return input;
}


void Multi_Def_Dictionary::addDefinition() {
	std::string word = getLine("Enter word: ");
	std::string def = getLine("Enter definition: ");
	dict[word].push_back(def);
	std::cout << "Definition added.\n";
}

void Multi_Def_Dictionary::viewDefinitions() {
	std::string word = getLine("Enter word to view definitions: ");
	auto it = dict.find(word);
	if (it != dict.end()) {
		std::cout << word << " has " << it->second.size() << " definition(s):\n";
		for (size_t i = 0; i < it->second.size(); ++i) {
			std::cout << i + 1 << ". " << it->second[i] << "\n";
		}
	}
	else {
		std::cout << "Word not found.\n";
	}
}

void Multi_Def_Dictionary::findWord() {
	std::string word = getLine("Enter word to search for: ");
	auto it = dict.find(word);
	if (it != dict.end()) {
		std::cout << "+-----" << std::endl;
		std::cout << "Found \"" << word << "\" with the following definition(s):\n";

		for (const auto& def : it->second) {
			std::cout << " - " << def << "\n";
		}
		std::cout << "+-----" << std::endl;
	}
	else {
		std::cout << "Word \"" << word << "\" not found in the dictionary.\n";
	}
}

void Multi_Def_Dictionary::editDefinition() {
	std::string word = getLine("Enter word to edit: ");
	auto it = dict.find(word);
	if (it == dict.end() || it->second.empty()) {
		std::cout << "Word not found or no definitions available.\n";
		return;
	}

	for (size_t i = 0; i < it->second.size(); ++i) {
		std::cout << i + 1 << ". " << it->second[i] << "\n";
	}

	std::cout << "Choose definition number to edit: ";
	size_t choice;
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush input

	if (choice == 0 || choice > it->second.size()) {
		std::cout << "Invalid choice.\n";
		return;
	}

	std::string newDef = getLine("Enter new definition: ");
	it->second[choice - 1] = newDef;
	std::cout << "Definition updated.\n";
}

void Multi_Def_Dictionary::deleteDefinition() {
	std::string word = getLine("Enter word to delete from: ");
	auto it = dict.find(word);
	if (it == dict.end()) {
		std::cout << "Word not found.\n";
		return;
	}

	if (it->second.size() == 1) {
		dict.erase(word);
		std::cout << "Word and its definition removed.\n";
		return;
	}

	for (size_t i = 0; i < it->second.size(); ++i) {
		std::cout << i + 1 << ". " << it->second[i] << "\n";
	}

	std::cout << "Choose definition number to delete (0 to cancel): ";
	size_t choice;
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (choice == 0 || choice > it->second.size()) {
		std::cout << "Cancelled.\n";
		return;
	}

	it->second.erase(it->second.begin() + choice - 1);
	std::cout << "Definition deleted.\n";

	if (it->second.empty()) {
		dict.erase(word);
		std::cout << "All definitions removed. Word deleted.\n";
	}
}

void Multi_Def_Dictionary::viewAll() {
	if (dict.empty()) {
		std::cout << "Dictionary is empty.\n";
		return;
	}

	for (auto entry : dict)
	{
		std::cout << "+-----" << std::endl;
		std::cout << entry.first << std::endl;
		int i = 1;
		for (auto def : entry.second)
		{
			std::cout << i++ << ". " << def << "\n";
		}
	}
	std::cout << "+-----" << std::endl;

}

void Multi_Def_Dictionary::saveToFile(const std::string& filename) {
	std::ofstream out(filename);
	if (!out) {
		std::cerr << "Error saving to file.\n";
		return;
	}

	for (auto entry : dict)
	{
		for (size_t i = 0; i < entry.second.size(); ++i) {
			out << entry.first << "|" << entry.second[i] << "\n";
		}
	}

	std::cout << "Dictionary saved to " << filename << "\n";
}

void Multi_Def_Dictionary::loadFromFile(const std::string& filename) {
	std::ifstream in(filename);
	if (!in) {
		std::cerr << "Error loading from file.\n";
		return;
	}

	dict.clear();
	std::string line;
	while (std::getline(in, line)) {
		std::istringstream ss(line);
		std::string word, def;
		if (std::getline(ss, word, '|') && std::getline(ss, def)) {
			dict[word].push_back(def);
		}
	}

	std::cout << "Dictionary loaded from " << filename << "\n";
}