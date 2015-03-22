/*      Assignment 1 - Linked Lists          **
**               Source.cpp                  **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#include "File.h"
#include <regex>
#include <string>
#include <iostream>
using namespace std;

string getLine();
string getCommand(int currline);
string command, error;

// Begin method main
int main(int argc, char* argv[])
{
	File poem(argv);
	cout << poem.fillList();

	while (true)
	{
		command = getCommand(poem.getCurrentLine());

		if (regex_match(command, regex("^[A-Z]([ ][0-9]+)?([ ][0-9]+)?"))){
			poem.parseCommand(command);
			error = "";

			// Insert line
			if (starts_with(command, "I"))
			{
				poem.addLine(getLine());
				cout << poem.fillList();
			}
			// Delete lines
			else if (starts_with(command, "D"))
			{
				poem.deleteRange();
				cout << poem.fillList();
			}
			// Display entire set of lines in buffer
			else if (starts_with(command, "V"))
			{
				cout << poem.fillList();
			}
			// Goes to the line in buffer
			else if (starts_with(command, "G"))
			{
				poem.setCurrentLine();
				cout << poem.fillList();
			}
			// Lists the lines of the buffer
			else if (starts_with(command, "L"))
			{
				cout << poem.listRange();
			}
			// Substitute lines
			else if (starts_with(command, "S"))
			{
				poem.substitute(getLine());
				cout << poem.fillList();
			}
			// Quit and save to file
			else if (starts_with(command, "E"))
			{
				poem.save();
				poem.exit();
				return 0;
			}
			// Quit without saving
			else if (starts_with(command, "Q"))
			{
				poem.exit();
				return 0;
			}
		}
		else {
			error = "Invalid command. ";
			cout << poem.fillList();
		}
	}
} // End method main

string getLine()
{
	string newline;
	cout << endl << "Enter a line to be inserted into the text." << endl << endl;
	getline(cin, newline);
	system("cls");
	return newline;
}

string getCommand(int currentLine)
{
	string cmd;

	
	cout << endl << error << "You are currently on line: " << currentLine << "." << endl;
	getline(cin, cmd);
	trim(cmd);
	to_upper(cmd);
	system("cls");
	return cmd;
}