/*    Assignment 4 - HTML Conversion   **
**              CPP_Reader.h           **
**         Written by Mike Pratt       **
**            NSCC PROG 2100           */

#ifndef CPPREADER_H //if not defined
#define CPPREADER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <exception>

using boost::algorithm::trim;
using namespace std;

// Begin class CPP_Reader
class CPP_Reader {

public:
	// Constructor given a directory
	CPP_Reader(string homeDirectory) {
		this->homeDirectory = homeDirectory;
	}
	// Return home directory
	string getHomeDirectory() {
		return this->homeDirectory;
	}
	// Get the read path
	string getReadFilePath(string homeDirectory);
	// Read in the cpp file
	string readTextFile(const string filePath);
	// Get the write path
	string getWriteFilePath(string homeDirectory);
	// Write the html file
	void writeToHTML(const string filePath, string wholeText);
	// Replace the brackets (< || >) with &lt and &rt
	string replaceBrackets(string inputText);

	// Check if user entered proper file path (cpp file exists)
	bool isValidReadFilePath();
	// Check if user entered proper cpp extension
	bool isValidCPPExtension(string filePath);
	// Check if file name already exists
	bool fileExists(string filePath);
	// Check if user entered proper html extension
	bool isValidHTMLExtension(string filePath);

private:

	// Set the default directory (home)
	void setHomeDirectory(string homeDirectory) {
		this->homeDirectory = "C:\\Users\\w0267422\\";
	}
	// User's home directory
	string homeDirectory;
	// Create stream to read file in
	ifstream inStream;
	// Create stream to write file out
	ofstream outStream;

}; // End class CPP_Reader

#endif