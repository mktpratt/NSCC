/*      Assignment 2 - Maze Solver           **
**               Solver.cpp                  **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#include "Solver.h"

void Solver::Solve(Maze *maze){

	// Entrance coordinates
	stack.Push(Coordinates(maze->getEntrance()[0], maze->getEntrance()[1]));
	maze->setAt(stack.GetTop().getX(), stack.GetTop().getY());

	// While the current position is not the end of the maze
	// 
	while (stack.GetTop().getY() != maze->getYLength() - 2){

		// If there is a move available
		if (moveAvailible(stack.GetTop().getX(), stack.GetTop().getY(), maze)) 
		{
			// Move through maze
			makeMove(stack.GetTop().getX(), stack.GetTop().getY(), maze);

			// Mark that you've been to this location
			maze->setAt(stack.GetTop().getX(), stack.GetTop().getY());			
		} 		
		// If couldn't find the exit, impossible maze
		else if (stack.GetTop().getX() == maze->getEntrance()[0] && stack.GetTop().getY() == maze->getEntrance()[1])
		{
				throw ImpossibleMazeException("Maze does not have a path to an exit.");
		} 
		// Go back if there are no moves
		else 
		{
			stack.Pop();
		}		
	}

	// Create the solved maze
	maze->createSolvedMaze(&stack);
}

bool Solver::moveAvailible(int x, int y, Maze * maze) 
{
	try 
	{
		if (x > 0 && maze->getAt(x - 1, y) == ' ') 
		{
			return true;
		} 
		else if (x < maze->getXLength() && maze->getAt(x + 1, y) == ' ') 
		{
			return true;
		}
		else if (y > 0 && maze->getAt(x, y - 1) == ' ') 
		{
			return true;
		}
		else if (y < maze->getYLength() && maze->getAt(x, y + 1) == ' ') 
		{
			return true;
		}

	} 
	catch(...) 
	{
		throw OutOfBoundsException("Attempted to read elements outside the bounds of the Maze array.");
	}
	return false;
}

void Solver::makeMove(int x, int y, Maze * maze) 
{
	if (x > 0 && maze->getAt(x - 1, y) == ' ') 
	{
		stack.Push(Coordinates(x - 1, y));
	} 
	else if (x < maze->getXLength() && maze->getAt(x + 1, y) == ' ') 
	{
		stack.Push(Coordinates(x + 1, y));
	} 
	else if (y > 0 && maze->getAt(x, y - 1) == ' ') 
	{
		stack.Push(Coordinates(x, y - 1));
	} 
	else if (y < maze->getYLength() && maze->getAt(x, y + 1) == ' ') 
	{
		stack.Push(Coordinates(x, y + 1));
	} 
	else 
	{
		throw FalsePositiveException("Solver::MoveAvailible returned a false positive.");
	}
}