/*      Assignment 2 - Maze Solver           **
**                Maze.cpp                   **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Maze.h"
#include "rlutil.h"

Maze::Maze(const int* entrance, const string& path):lines(0), linelength(0), entrance(entrance)
{
	ifstream inStream;
	char templine[1024];	

	try
	{
		inStream.open(path, std::fstream::in);
	}
	catch (...)
	{
		throw FileTypeException("Cannot read file.");
	}

	// Loop to determine number of lines
	while (!inStream.eof())
	{
		try 
		{
			inStream.getline(templine, 1024);
		} 
		catch (...)
		{
			throw FileTypeException("Unable to read line: " + to_string(lines) + " of the text file.");
		}

		lines++;
	}

	// Get length of row
	linelength = strlen(templine) + 1;

	// Go back to beginning of file
	inStream.clear();
	inStream.seekg(0, ios::beg);

	maze = new char*[lines];
	solved_maze = new char*[lines];
	for (int i = 0; i < lines; i++)
	{
		maze[i] = new char[linelength];
		solved_maze[i] = new char[linelength];
	}

	// Write the file
	int x = 0;
	while (!inStream.eof())
	{
		inStream.getline(templine, 1024);
		strcpy(solved_maze[x], templine);
		strcpy(maze[x], templine);
		x++;
	}
	// Close instream
	inStream.close();
}

void Maze::setAt(int x, int y)
{
	maze[x][y] = '"\u2764"';
}

char Maze::getAt(int x, int y)
{
	return maze[x][y];
}


int Maze::getXLength()
{
	return lines;
}

int Maze::getYLength()
{
	return linelength;
}

const int* Maze::getEntrance()
{
	return entrance;
}

char Maze::getSolvedMazeAt(int x, int y)
{
	return solved_maze[x][y];
}

void Maze::createSolvedMaze(Stack * stack)
{
	int coordinates = stack->GetSize();

	for (int i = 0; i < coordinates; i++)
	{
		solved_maze[stack->GetTop().getX()][stack->GetTop().getY()] = '"\u2764"';
		stack->Pop();
	}
}

void Maze::saveSolvedMaze(const char* inputfile, const char* outputfile)
{
	wofstream outStream;

	try
	{
		outStream.open(outputfile);
	}
	catch (...)
	{
		throw FileTypeException("Can't create file.");
	}

	try
	{
		outStream << inputfile << "\n\n";

		for (int x = 0; x < lines; x++)
		{
			outStream << solved_maze[x] << endl;
		}
	} 
	catch (...)
	{
		throw FileTypeException("Cannot save the maze.");
	}
	outStream.close();
}