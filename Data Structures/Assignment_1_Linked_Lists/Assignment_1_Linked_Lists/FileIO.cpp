/*      Assignment 1 - Linked Lists          **
**                FileIO.cpp                   **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#include "FileIO.h"

FileIO::FileIO(){}
FileIO::~FileIO(){}

void FileIO::open(string path)
{
	inStream.open(path, std::fstream::in);
}

void FileIO::makeLinkedList(LinkedList *list)
{
	std::string line;

	if (inStream.is_open())
	{
		while (!inStream.eof())
		{
			getline(inStream, line);
			list->add(line);
		}
		inStream.close();

	}
}

void FileIO::save(string path, LinkedList *list){
	outStream.open(path, std::fstream::out);

	if (outStream.is_open()) {

		outStream << *list;
		outStream.close();

	}
}