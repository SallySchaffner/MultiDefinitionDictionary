/*#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
*/
#include "Dictionary.h"


// Display the menu options
void showMenu() {
    std::cout << "\n====== Dictionary Menu ======\n";
    std::cout << "1. Add definition\n";
    std::cout << "2. View definitions\n";
    std::cout << "3. Edit definition\n";
    std::cout << "4. Delete definition\n";
    std::cout << "5. View all entries\n";
    std::cout << "6. Find (search) word\n";
    std::cout << "0. Exit\n";
    std::cout << "=============================\n";
}

int main() {
    //Dictionary dict;
    Multi_Def_Dictionary dict;
    std::string filename = "dictionary.txt";
    dict.loadFromFile(filename);
    int choice;

    do {
        showMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        switch (choice) {
        case 1: dict.addDefinition(); break;
        case 2: dict.viewDefinitions(); break;
        case 3: dict.editDefinition(); break;
        case 4: dict.deleteDefinition(); break;
        case 5: dict.viewAll(); break;
        case 6: dict.findWord(); break;
        case 0: std::cout << "Goodbye!\n"; break;
        default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    dict.saveToFile(filename);

    return 0;
}