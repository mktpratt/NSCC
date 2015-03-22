/*      Assignment 2 - Maze Solver           **
**                Stack.cpp                  **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#pragma once

#include <cstring>
#include <iostream>
#include "Coordinates.cpp"
#include "Exceptions.cpp"

using namespace std;

class Stack
{

public:

	// Default constructor
	Stack()
	{
		size = 0;
		array = new Coordinates[size];
	}

	void Pop()
	{
		size--;

		if (size < 0)
		{
			throw StackUnderflowException("Stack underflow exception. Back-tracked out of bounds.");
		}

		Coordinates *newArray = new Coordinates[size];
		memcpy(newArray, array, size * sizeof(Coordinates));

		delete[] array;
		array = newArray;
	}

	void Push(Coordinates item)
	{
		size++;

		Coordinates * newArray = new Coordinates[size];
		memcpy(newArray, array, size * sizeof(Coordinates));

		delete[] array;
		array = newArray;
		array[size - 1] = Coordinates(item);
	}

	Coordinates GetTop()
	{
		return array[size - 1];
	}

	int GetSize(){
		return size;
	}

	private:
		int size;
		Coordinates * array;
};