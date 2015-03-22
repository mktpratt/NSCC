/*      Assignment 2 - Maze Solver           **
**             Coordinates.cpp               **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#pragma once
class Coordinates
{

public:
	Coordinates()
	{
		this->x = 0;
		this->y = 0;
	}

	Coordinates(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Coordinates(const Coordinates& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

private:
	int x, y;

};