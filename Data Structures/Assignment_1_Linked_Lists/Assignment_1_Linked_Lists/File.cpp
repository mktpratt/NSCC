/*      Assignment 1 - Linked Lists          **
**                File.cpp                   **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#include "File.h"

File::File(char* paths[]) : heapList(new LinkedList())
{
	this->inpath = paths[2];
	this->outpath = paths[3];

	this->file.open(inpath);
	this->file.makeLinkedList(heapList);

	this->currentLine = heapList->getNumLines();
	this->startingRange = 0;
	this->stopRange = 0;
}

// Add the line
void File::addLine(string newline){
	heapList->insertAtIndex(currentLine, newline);
}

// Substitute the line
void File::substitute(string newline){
	heapList->deleteNode(currentLine);
	heapList->insertAtIndex(currentLine, newline);
}

// Delete lines (range)
void File::deleteRange(){
	for (int x = startingRange; x <= stopRange; x++){
		heapList->deleteNode(startingRange);
	}
}

// List the range
string File::listRange(){
	ostringstream tempList;

	for (int x = startingRange; x <= stopRange; x++){
		tempList << x << ":" << spacesForLists(x) << heapList->getValue(x) << "\n";
	}
	tempList << "\n";

	return tempList.str();
}

// Set current line
void File::setCurrentLine(){
	if (stopRange > this->heapList->getNumLines()){
		currentLine = this->heapList->getNumLines() + 1;
	}
	else {
		currentLine = stopRange;
	}
}

// Get current line
int File::getCurrentLine(){
	return this->currentLine;
}

// Fill the list
string File::fillList(){
	ostringstream templist;

	for (int x = 0; x <= heapList->getNumLines(); x++){
		templist << x << ":" << spacesForLists(x) << heapList->getValue(x) << "\n";
	}
	templist << "\n";

	return templist.str();
}

// Return spaces
string File::spacesForLists(int linenum){
	string spaces;
	if (linenum < 10){
		spaces = "   ";
	}
	else if (linenum < 100){
		spaces = "  ";
	}
	else if (linenum < 1000){
		spaces = " ";
	}
	return spaces;
}

// Parse the command
void File::parseCommand(string command)
{
	ArgumentList temp;
	int numArgs = (args = split(temp, command, is_any_of(" "))).size();
	int numLines = this->heapList->getNumLines();

	// 1 arg means the start and stop line are the same
	if (numArgs > 1)
	{
		this->startingRange = (this->stopRange = (convertToInt(args.at(1)) > numLines ? numLines : convertToInt(args.at(1))));
	}
	// 2 args means a range of lines
	if (numArgs > 2)
	{
		this->startingRange = (convertToInt(args.at(1)) > numLines ? numLines : convertToInt(args.at(1)));
		this->stopRange = (convertToInt(args.at(2)) > numLines ? numLines : convertToInt(args.at(2)));
	}
	setCurrentLine();
}

// Save
void File::save()
{
	file.save(outpath, heapList);
}

// Exit
void File::exit()
{
	heapList->~LinkedList();
}

// Convert to integer
int File::convertToInt(string input)
{
	int i;
	try 
	{
		i = boost::lexical_cast<int>(input);
	}
	catch (boost::bad_lexical_cast) 
	{

	}
	return i;
}

// Split the string
ArgumentList File::splitString(string input)
{
	ArgumentList temp;
	return split(temp, input, is_any_of(" "));
}