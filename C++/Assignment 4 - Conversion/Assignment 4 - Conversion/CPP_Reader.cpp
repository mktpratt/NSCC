/*    Assignment 4 - HTML Conversion   **
**            CPP_Reader.cpp           **
**         Written by Mike Pratt       **
**            NSCC PROG 2100           */

#include "CPP_Reader.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <exception>

using namespace std;

// Read in .cpp file
string CPP_Reader::readTextFile(const string filePath) {
	// Current line string
	string line;
	// Entire text string
	string wholeText;
	try {
		// Open the file
		this->inStream.open((this->homeDirectory + filePath).c_str());
		// If file opens, get a line
		if (inStream.is_open()) {
			// Loop while not the end of the file
			while (!inStream.eof()) {
				// Get line of text from file
				getline(inStream, line);
				// Add it to the wholeText string
				wholeText += (line + "\n");
			} // End while loop

			// Close the inStream
			inStream.close();
			// Return the entire text
			return wholeText;
		} // End if

		// Check if reading fails
		if (inStream.fail()) {
			throw(99);
		} // End if

	} // End try block

	// Custom int error catch
	catch (int error) {
		cout << "Reading from file failed. Error#" << error << endl;
	} // End catch

	// Library error catch
	catch (exception& e) {
		cout << "Error reading file: " << e.what() << endl;
	} // End catch

	// Default error catch
	catch (...) {
		cout << "Error reading file." << endl;
	} // End catch

	// Return empty text (No errors)
	return "";
} // End method readTextFile

// Begin method writeToHTML
void CPP_Reader::writeToHTML(const string filePath, string wholeText) {
	// Begin try block
	try {
		// Try and open the file
		this->outStream.open((this->homeDirectory + filePath).c_str(), ios::app);
		// Check if file opens
		if (outStream.is_open()) {
			wholeText = replaceBrackets(wholeText);
			outStream << "<PRE>\n" << endl;
			outStream << wholeText << endl;
			outStream << "</PRE>\n" << endl;
			outStream.close();
		} // End if

		// Throw error if writing fails
		if (outStream.fail()) {
			throw 98;
		} // End if
	} // End try block

	// Custom int error catch
	catch (int errorCode) {
		// Close the outStream
		outStream.close();
		cout << "Cannot write to that file. Error#" << errorCode << endl;
	} // End catch

	// Library error catch
	catch (exception& e) {
		// Close the outStream
		outStream.close();
		cout << "Could not write to file: " << e.what() << endl;
	} // End catch

	// Default error catch
	catch (...) {
		// Close the outStream
		outStream.close();
		cout << "Could not write to file." << endl;
	} // End catch

} // End method writeToHTML

// Begin method replaceBrackets
string CPP_Reader::replaceBrackets(string line) {
	// String for the bracketed string from .cpp file
	string bracketString = "";
	// Loop until at the end of the line
	for (int i = 0; i < line.length(); i++) {
		switch (line[i]) {
		case '<':
			// Add left bracket
			bracketString += "&lt";
			break;
		case '>':
			// Add right bracket
			bracketString += "&gt";
			break;
		default:
			// Single character
			bracketString += line[i];
		}
	} // End for loop

	// Return the string
	return bracketString;
} // End method replaceBrackets

// Begin method getReadFilePath
string CPP_Reader::getReadFilePath(string homeDirectory) {
	// String for file path
	string filePath = "";
	// inStream for testing if file exists
	ifstream inStream;
	// Loop to find valid file name from user
	while (!inStream.is_open()) {
		cout << endl << "*-------------------------------------------*" << endl;
		cout << "| Please enter the location of the CPP File | " << endl;
		cout << "| Relative to your home directory.          | " << endl;
		cout << "| EX: Documents/Test.cpp                    | " << endl;
		cout << "*-------------------------------------------*" << endl << endl;

		// Read in user file path
		cin >> filePath;
		// Trim excess whitespace
		boost::algorithm::trim(filePath);

		// Check if file is valid .cpp file extension
		if (!isValidCPPExtension(filePath)){
			cout << "\n The file you entered is not a .cpp file!\n" << endl;
			continue;
		} // End if

		// Open the file if it exists
		inStream.open((homeDirectory + filePath).c_str());
		// Loop again if we cannot open the file
		if (!inStream.is_open()) {
			cout << endl << (this->homeDirectory + filePath).c_str() << endl;
			cout << "Cannot open this file in this location." << endl << endl;
		} // End if
	} // End while loop

	// Close inStream
	inStream.close();

	// Return the filePath
	return filePath;
}
// Check to see if .cpp file exists
bool CPP_Reader::fileExists(string filePath) {
	ifstream infile(filePath.c_str());
	return infile.good();
}

// returns a file path for writing a file
string CPP_Reader::getWriteFilePath(string homeDirectory) {
	// String for file path
	string filePath = "";
	// outStream for testing if file exists
	ofstream outStream;

	// Loop while file is not open
	while (!outStream.is_open()) {
		cout << endl << "*-------------------------------------------*" << endl;
		cout << "| Please enter location to write HTML file. | " << endl;
		cout << "| Relative to your home directory.          | " << endl;
		cout << "| EX: Documents/Test.html                   | " << endl;
		cout << "*-------------------------------------------*" << endl << endl;

		// Read in user file path
		cin >> filePath;


		boost::algorithm::trim(filePath);
		// Check if file is valid .html file extension
		if (!isValidHTMLExtension(filePath)){
			cout << "\n Not a .html file!\n" << endl;
			continue;
		} // End if

		// Check if file exists already
		if (fileExists(this->homeDirectory + filePath)) {
			cout << endl << "Cannot write to " << (this->homeDirectory + filePath).c_str() << endl;
			cout << "File exists at that location!" << endl << endl;
			continue;
		} // End if

		// Open the file if it doesn't exist already
		outStream.open((homeDirectory + filePath).c_str());
	} // End while loop

	// Close outStream
	outStream.close();

	// Return the filePath
	return filePath;
} // End method getWriteFilePath


// Begin method isValidHTMLExtension
bool CPP_Reader::isValidHTMLExtension(string filePath) {
	// RegEx for anything.html
	boost::regex e("(?i)(^.+\\.html$)");
	return boost::regex_match(filePath, e);
} // End method isValidHTMLExtension

// Begin method isValidCPPExtension
bool CPP_Reader::isValidCPPExtension(string filePath) {
	// RegEx for anything.cpp
	boost::regex e("((?i)^.+\\.cpp$)");
	return boost::regex_match(filePath, e);
} // End method isValidCPPExtension