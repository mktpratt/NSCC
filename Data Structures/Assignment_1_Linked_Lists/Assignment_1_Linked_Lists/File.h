/*      Assignment 1 - Linked Lists          **
**                 File.h                    **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#pragma once
#include <string>
#include <sstream> 
#include <vector>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "LinkedList.h"
#include "FileIO.h"

using namespace std;
using namespace boost;

typedef vector<string> ArgumentList;

class File
{
	public:
		File(char* argv[]);

		ArgumentList splitString(string input);

		string listRange();
		string fillList();
		string spacesForLists(int linenum);

		int convertToInt(string input);
		int getCurrentLine();

		void parseCommand(string command);
		void substitute(string newline);
		void addLine(string newline);

		void deleteRange();
		void setCurrentLine();
		void save();
		void exit();

	private:
		FileIO file;
		LinkedList *heapList;
		ArgumentList args;
		string inpath, outpath;
		int currentLine, startingRange, stopRange;
		
};