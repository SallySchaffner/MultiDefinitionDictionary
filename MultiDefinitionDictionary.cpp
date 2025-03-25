#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

using Dictionary = std::map<std::string, std::vector<std::string>>;

// Helper to get user input safely
std::string getLine(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// Add a definition
void addDefinition(Dictionary& dict) {
    std::string word = getLine("Enter word: ");
    std::string def = getLine("Enter definition: ");
    dict[word].push_back(def);
    std::cout << "Definition added.\n";
}

// View definitions (same as before)
void viewDefinitions(const Dictionary& dict) {
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

// **New Find Function: Searches for a word and displays its definitions**
void findWord(const Dictionary& dict) {
    std::string word = getLine("Enter word to search for: ");
    auto it = dict.find(word);
    if (it != dict.end()) {
        std::cout << "Found \"" << word << "\" with the following definition(s):\n";
        for (const auto& def : it->second) {
            std::cout << " - " << def << "\n";
        }
    }
    else {
        std::cout << "Word \"" << word << "\" not found in the dictionary.\n";
    }
}

// Edit a definition
void editDefinition(Dictionary& dict) {
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

// Delete a definition or entire word
void deleteDefinition(Dictionary& dict) {
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

// View entire dictionary
void viewAll(const Dictionary& dict) {
    if (dict.empty()) {
        std::cout << "Dictionary is empty.\n";
        return;
    }

    for (auto entry : dict)
    {
        std::cout << entry.first << std::endl;
        for (size_t i = 0; i < entry.second.size(); ++i) {
            std::cout << i + 1 << ". " << entry.second[i] << "\n";
        }
    }


}

// Save dictionary to a file
void saveToFile(const Dictionary& dict, const std::string& filename) {
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

// Load dictionary from a file
void loadFromFile(Dictionary& dict, const std::string& filename) {
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

// Display the menu options
void showMenu() {
    std::cout << "\n====== Dictionary Menu ======\n";
    std::cout << "1. Add definition\n";
    std::cout << "2. View definitions\n";
    std::cout << "3. Edit definition\n";
    std::cout << "4. Delete definition\n";
    std::cout << "5. View all entries\n";
    std::cout << "6. Save to file\n";
    std::cout << "7. Load from file\n";
    std::cout << "8. Find (search) word\n";
    std::cout << "0. Exit\n";
    std::cout << "=============================\n";
}

int main() {
    Dictionary dict;
    std::string filename = "dictionary.txt";
    int choice;

    do {
        showMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        switch (choice) {
        case 1: addDefinition(dict); break;
        case 2: viewDefinitions(dict); break;
        case 3: editDefinition(dict); break;
        case 4: deleteDefinition(dict); break;
        case 5: viewAll(dict); break;
        case 6: saveToFile(dict, filename); break;
        case 7: loadFromFile(dict, filename); break;
        case 8: findWord(dict); break;
        case 0: std::cout << "Goodbye!\n"; break;
        default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}