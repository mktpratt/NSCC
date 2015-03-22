/*      Assignment 2 - Maze Solver           **
**                Solver.h                   **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#pragma once

#include "Stack.cpp"
#include "Coordinates.cpp"
#include "Maze.h"

using namespace std;

class Solver
{

public:
	void Solve(Maze *maze);
	bool moveAvailible(int x, int y, Maze * maze);
	void makeMove(int x, int y, Maze * maze);

private:
	Stack stack;

};
