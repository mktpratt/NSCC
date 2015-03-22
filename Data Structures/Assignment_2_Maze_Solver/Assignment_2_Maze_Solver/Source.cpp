/*      Assignment 2 - Maze Solver           **
**               Source.cpp                  **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */


// To run, you must provide two files as command line arguments:
// Assignment_2_Maze_Solver.exe (INPUT FILE WITH MAZE DIRECTORY) (OUTPUT FILE TO SAVE DIRECTORY)
// Ex. Assignment_2_Maze_Solver.exe C:\Users\w0267422\Desktop\School\Maze1.txt C:\Users\w0267422\Desktop\School\SolvedMaze1.txt


/* References: 
http://codereview.stackexchange.com/questions/48909/recursive-maze-solver
http://www.dreamincode.net/forums/topic/328670-cases-for-right-hand-rule-maze-solver/
*/

#include <conio.h>
#include <sys/stat.h>
#include <boost/regex.hpp>

#include "Maze.h"
#include "Solver.h"

using namespace boost;
using namespace std;

void print(Maze *maze);
void printSolvedMaze(Maze *maze);
inline bool fileExists (const string& name);

int main(int argc, char* argv[])
{
	// Bool for completing maze
	bool success = false;
	const static int entrance[2] = { 1, 0 };

	// Validate input file name
	if (!regex_match(argv[1], regex("([a-z]|[A-Z]):\\\\(([a-z]|[A-Z]|[0-9]|[ ]|[_])+(\\\\))*([a-z]|[A-Z]|[0-9]|[ ]|[_])+\\.txt")) || !fileExists(argv[1])){
		cout << argv[1] << endl;
		cout << "\nInvalid input file. Must be a full path to a text file.\n";
		return 1;
	}

	// Validate output file name
	if (!regex_match(argv[2], regex("([a-z]|[A-Z]):\\\\(([a-z]|[A-Z]|[0-9]|[ ]|[_])+(\\\\))*([a-z]|[A-Z]|[0-9]|[ ]|[_])+\\.txt"))){
		cout << "\nInvalid output file. Must be a full path to a text file.\n";
		return 1;
	}

	// Create maze objects
	Maze maze(entrance, argv[1]);
	Maze *pointerToMaze = &maze;

	// Create solver object
	Solver solver;

    // Try and solve maze
	try 
	{
		solver.Solve(pointerToMaze);
		success = true;
	}
	// Failed
	catch (std::exception &e)
	{
		cout << e.what() << endl;
		return 1;
	}

	// Display prompt if maze was able to be solved
	if (success)
	{
		printSolvedMaze(pointerToMaze);
		cout << "\nMaze completed!\n";
		cout << "\nEnter 's' to save the solved maze, 'p' to display the poison pill trail \n"
			"or any other key to exit the program.\n\n";

		// Check for poison pill display, or to save a solved copy of the maze
		switch (_getch())
		{
			// Poison pill trail
			case 'p':
			{
				print(pointerToMaze);
				cout << endl;
				system("PAUSE");
				break;
			}
			// Save
			case 's':
			{
				try 
				{
					maze.saveSolvedMaze(argv[1], argv[2]);
				}
				catch (std::exception &e)
				{
					cout << e.what() << endl;
					return 1;
				}
				cout << endl << "The maze solution has been save in: " << argv[2] << endl;
				system("PAUSE");
				break;
			}
			
			default:
			{
				cout << "The program will now close.\n";
				system("PAUSE");
				break;
			}
		}
		return 0;
	}
}

// Print method
void print(Maze *maze)
{
	for(int x = 0; x < maze->getXLength(); x++)
	{
		for(int y = 0; y < maze->getYLength(); y++)
		{
			cout << maze->getAt(x, y);
		}
		cout << endl;
	}
}

// Print solved maze method
void printSolvedMaze(Maze *maze){
	for(int x = 0; x < maze->getXLength(); x++)
	{
		for(int y = 0; y < maze->getYLength(); y++)
		{
			cout << maze->getSolvedMazeAt(x, y);
		}
		cout << endl;
	}
}

// File exists method
inline bool fileExists(const string& name) {
	struct stat buffer;   
	return (stat (name.c_str(), &buffer) == 0); 
}