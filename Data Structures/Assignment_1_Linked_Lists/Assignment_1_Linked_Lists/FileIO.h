/*      Assignment 1 - Linked Lists          **
**                FileIO.h                   **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#pragma once
#include <fstream>
#include <string>
#include "LinkedList.h"

class FileIO
{
public:
	FileIO();
	~FileIO();
	void open(std::string path);
	void makeLinkedList(LinkedList *list);
	void save(string path, LinkedList *list);

private:
	std::ifstream inStream;
	std::ofstream outStream;

};