/*      Assignment 2 - Maze Solver           **
**                 Maze.h                    **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#pragma once

#include <fstream>

#include "Stack.cpp"

using namespace std;

class Maze
{

public:
	Maze(const int* entrance, const string& path);
	char getAt(int x, int y);
	void setAt(int x, int y);
	int getXLength();
	int getYLength();
	const int *getEntrance();
	void createSolvedMaze(Stack *stack);
	char getSolvedMazeAt(int x, int y);
	void saveSolvedMaze(const char* inputfile, const char* outputfile);

private:
	int lines, linelength;
	const int *entrance;
	char **maze, **solved_maze;

};