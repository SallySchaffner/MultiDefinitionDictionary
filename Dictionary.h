#ifndef __dictionary__
#define __dictionary__

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

class Multi_Def_Dictionary
{
private:
	std::map<std::string, std::vector<std::string>> dict;

public:

	// Helper to get user input safely
	std::string getLine(const std::string& prompt); 

	/*
	* Description: Adds a definition to the given word.
	* Behavior: If the word exists, appends the new definition; otherwise, creates a new word entry.
	* Preconditions: word and definition are valid strings.
	* Postconditions: definition is included in the word's list of definitions.
	*/
	void addDefinition(); 

	/* 
	 * Description: Displays all definitions for a given word.
	 * Behavior: Lists definitions if the word exists, otherwise notifies the user.
	 * Preconditions: word is a valid string.
	 * Postconditions: No change to the dictionary.
	*/
	void viewDefinitions(); 
	
	/*
	 * Description: Searches for a given word in the dictionary.
	 * Preconditions: word is a valid string.
	 * Postconditions: Returns the list of definitions associated with the word if found; otherwise, returns an empty vector.
	 * This operation is combined with user feedback (printing the definitions or a "not found" message).
	*/
	void findWord(); 

	/*
	 * Description: Replaces the definition at the specified index for a given word.
	 * Behavior: Updates the definition if the word and index are valid.
	 * Preconditions: word exists, and index is within bounds.
	 * Postconditions: Replaces the old definition with newDef.
	*/
	void editDefinition(); 

	/*
	 * Description: Removes a specific definition from a word.
	 * Behavior: If the last definition is deleted, the word itself is removed.
	 * Preconditions: word exists and index is valid.
	 * Postconditions: The selected definition (or entire word) is removed.
	*/
	void deleteDefinition(); 

	/*
	 * Description: Displays all words and their definitions.
	 * Behavior: Iterates through the dictionary and prints each word with its definitions.
	 * Preconditions: None.
	 * Postconditions: No change to the dictionary.
	*/
	void viewAll(); 

	/*
	 * Description: Saves the dictionary to a text file.
	 * Behavior: Writes each (word, definition) pair as word|definition on separate lines.
	 * Preconditions: filename is a valid path.
	 * Postconditions: File contains the serialized dictionary data.
	 */
	void saveToFile(const std::string& filename); 

	// Load dictionary from a file
	/*
	 * Description: Loads dictionary data from a file.
	 * Behavior: Clears current data and populates from the file.
	 * Preconditions: File exists and is properly formatted.
	 * Postconditions: Dictionary is replaced with the contents of the file.
	*/
	void loadFromFile(const std::string& filename); 

};

#endif
