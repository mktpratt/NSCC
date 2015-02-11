/*    Assignment 4 - HTML Conversion   **
**               main.cpp              **
**         Written by Mike Pratt       **
**            NSCC PROG 2100           */

#include "CPP_Reader.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;


bool isValidResponse(string response);
bool convertAnotherFile();

// Begin method main
int main(int argc, char **argv) {

	// CPP_Reader with a local system location
	CPP_Reader cppReader("C:\\Users\\w0267422\\");
	// Boolean to repeat process
	bool goAgain = false;

	while (!goAgain){
		// Read in file path
		string filePath = cppReader.getReadFilePath(cppReader.getHomeDirectory());
		// readTextFile using filePath (read path)
		string inputText = cppReader.readTextFile(filePath);
		// getWriteFilePath location (write path)
		string outFilePath = cppReader.getWriteFilePath(cppReader.getHomeDirectory());
		// Write the file
		cppReader.writeToHTML(outFilePath, inputText);
		// Check if user wants to convert another file
		goAgain = !convertAnotherFile();
	} // End while loop
	return 0;
} // End method main


// Begin method isValidResponse (Check if user's response is valid to repeat)
bool isValidResponse(string response) {


	if (response.length() > 1){
		return false;
	} // End if

	// Check if response matches ascii for Y(89)/y(121) and n(78)/N(110)
	if (!(int(response[0]) == 121 || int(response[0]) == 89
		|| int(response[0]) == 78 || int(response[0]) == 110)) {
		return false;
	} // End if

	return true;
} // End method isValidResponse

// Begin method convertAnotherFile (Determine if user wants to convert another file)
bool convertAnotherFile() {

	string userResponse = "";

	// Loop while user's response isn't valid (yYnN)
	while (!isValidResponse(userResponse)) {
		cout << endl << "*----------------------------------------------*" << endl;
		cout << "| Would you like to convert another CPP (Y/N)  |" << endl;
		cout << "*----------------------------------------------*" << endl;
		cin >> userResponse;
		// Check for Ctrl + Z
		if (cin.eof() == 1) {
			cin.clear();
		} // End if
	} // End while
	if (userResponse == "Y" || userResponse == "y") {
		return(userResponse == "Y" || userResponse == "y");
	}
	else {
		cout << "Thank you for using my program. Now closing..." << endl;
		system("PAUSE");
		return 0;
	}
} // End method convertAnotherFile