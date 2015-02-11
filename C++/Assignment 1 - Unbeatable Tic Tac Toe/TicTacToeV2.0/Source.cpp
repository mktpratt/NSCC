/* Assignment 1 - Tic Tac Toe Game
Written by Mike Pratt
NSCC PROG 2100
9/12/2014
*/

#include <iostream>
#include <signal.h>
#include <conio.h>
#include <sstream>
#include "rlutil.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

const int NUM_ROWS = 3;
const int NUM_COLUMNS = 3;
char moves[NUM_ROWS][NUM_COLUMNS] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' } };
char playAgain;
bool gameOver = false;
int turn = 0, playerNum = 1, playerWhoWon = 0, playerMove = 0;
int taken1 = 0, taken2 = 0, taken3 = 0, taken4 = 0, taken5 = 0, 
	taken6 = 0, taken7 = 0, taken8 = 0, taken9 = 0;
int used[9];
int aiChose = 0;


void userMove();
void computerMove();
void drawGameBoard();
void initializeMoves();
void checkForWin();


void drawGameBoard(char board[NUM_ROWS][NUM_COLUMNS])
{
	cout << "\n";
	for (int r = 0; r < NUM_ROWS; r++)
	{
		rlutil::setColor(15);
		cout << "\n" << " _ _ _ _ _ _ _" << "\n\n";
		for (int c = 0; c < NUM_COLUMNS; c++)
		{
			cout << " | ";
			if (board[r][c] == 'X')
			{
				rlutil::setColor(10);
				cout << board[r][c];
			}
			else if (board[r][c] == 'O')
			{
				rlutil::setColor(4);
				cout << board[r][c];
			}
			else
			{
				rlutil::setColor(14);
				cout << board[r][c];
			}
			rlutil::setColor(15);
		}
		cout << " |";
	}
	cout << "\n" << " _ _ _ _ _ _ _" << "\n\n";
}// end drawGameBoard method

// Initialize the moves array as blank
void initializeGame()
{
	char count = 49;
	turn = 0; playerWhoWon = 0; playerNum = 1;
	gameOver = false;
	taken1 = 0, taken2 = 0, taken3 = 0, taken4 = 0,
		taken5 = 0, taken6 = 0, taken7 = 0, taken8 = 0,
		taken9 = 0;

	for (int num = 0; num <= 8; num++)
	{
		used[num] = 0;
	}

	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			moves[i][j] = count;
			count++;
		}
	}
} // end initializeMoves method

void checkForWin()
{
	if ((moves[0][0] == 'X' && moves[0][1] == 'X' && moves[0][2] == 'X')     // Top row
		|| (moves[1][0] == 'X' && moves[1][1] == 'X' && moves[1][2] == 'X')  // Middle row
		|| (moves[2][0] == 'X' && moves[2][1] == 'X' && moves[2][2] == 'X')  // Bottom row
		|| (moves[0][0] == 'X' && moves[1][1] == 'X' && moves[2][2] == 'X')  // Top left to bottom right
		|| (moves[2][0] == 'X' && moves[1][1] == 'X' && moves[0][2] == 'X')  // Bottom left to top right
		|| (moves[0][0] == 'X' && moves[1][0] == 'X' && moves[2][0] == 'X')  // Left column
		|| (moves[0][1] == 'X' && moves[1][1] == 'X' && moves[2][1] == 'X')  // Middle column
		|| (moves[0][2] == 'X' && moves[1][2] == 'X' && moves[2][2] == 'X')) // Right column
	{
		playerWhoWon = 1;
		gameOver = true;
	}
	if ((moves[0][0] == 'O' && moves[0][1] == 'O' && moves[0][2] == 'O')     // Top row
		|| (moves[1][0] == 'O' && moves[1][1] == 'O' && moves[1][2] == 'O')  // Middle row
		|| (moves[2][0] == 'O' && moves[2][1] == 'O' && moves[2][2] == 'O')  // Bottom row
		|| (moves[0][0] == 'O' && moves[1][1] == 'O' && moves[2][2] == 'O')  // Top left to bottom right
		|| (moves[2][0] == 'O' && moves[1][1] == 'O' && moves[0][2] == 'O')  // Bottom left to top right
		|| (moves[0][0] == 'O' && moves[1][0] == 'O' && moves[2][0] == 'O')  // Left column
		|| (moves[0][1] == 'O' && moves[1][1] == 'O' && moves[2][1] == 'O')  // Middle column
		|| (moves[0][2] == 'O' && moves[1][2] == 'O' && moves[2][2] == 'O')) // Right column
	{
		playerWhoWon = 2;
		gameOver = true;
	}

	if (turn >= 9)
		gameOver = true;

	// Check if game is over
}

// Maintain the tic tac toe board
void updateBoard(char num, int player)
{
	int spot;
	if (num == 49)
		spot = 0;
	else if (num == 50)
		spot = 1;
	else if (num == 51)
		spot = 2;
	else if (num == 52)
		spot = 3;
	else if (num == 53)
		spot = 4;
	else if (num == 54)
		spot = 5;
	else if (num == 55)
		spot = 6;
	else if (num == 56)
		spot = 7;
	else if (num == 57)
		spot = 8;

	if ((used[spot] != 0 && num >= 49 && num <= 57) || (num < 49 && num > 57))
	{
		cout << "\n\nThat spot is already occupied.\n";
		if (playerMove % 2 == 1)
		{
			userMove();
			num = 0;
		}
	}

	switch (num)
	{
	case 49:
		if (player == 1 && taken1 == 0)
			moves[0][0] = 'X';
		else if (taken1 == 0)
			moves[0][0] = 'O';
		taken1 = 1;
		break;
	case 50:
		if (player == 1 && taken2 == 0)
			moves[0][1] = 'X';
		else if (taken2 == 0)
			moves[0][1] = 'O';
		taken2 = 1;
		break;
	case 51:
		if (player == 1  && taken3 == 0)
			moves[0][2] = 'X';
		else if (taken3 == 0)
			moves[0][2] = 'O';
		taken3 = 1;
		break;
	case 52:
		if (player == 1 && taken4 == 0)
			moves[1][0] = 'X';
		else if (taken4 == 0)
			moves[1][0] = 'O';
		taken4 = 1;
		break;
	case 53:
		if (player == 1 && taken5 == 0)
			moves[1][1] = 'X';
		else if (taken5 == 0)
			moves[1][1] = 'O';
		taken5 = 1;
		break;
	case 54:
		if (player == 1 && taken6 == 0)
			moves[1][2] = 'X';
		else if (taken6 == 0)
			moves[1][2] = 'O';
		taken6 = 1;
		break;
	case 55:
		if (player == 1 && taken7 == 0)
			moves[2][0] = 'X';
		else if (taken7 == 0)
			moves[2][0] = 'O';
		taken7 = 1;
		break;
	case 56:
		if (player == 1 && taken8 == 0)
			moves[2][1] = 'X';
		else if (taken8 == 0)
			moves[2][1] = 'O';
		taken8 = 1;
		break;
	case 57:
		if (player == 1 && taken9 == 0)
			moves[2][2] = 'X';
		else if (taken9 == 0)
			moves[2][2] = 'O';
		taken9 = 1;
		break;
	}
	drawGameBoard(moves);
	turn++;
	playerMove++;
	used[spot] += num;
}// end updateBoard method

// AI move
void computerMove()
{
	srand(time(NULL));	

	// If AI goes first
	if (turn == 0 || (turn == 1 && moves[1][1] == 88))
	{
		// Randomly pick a corner
		int randNum = rand() % 4 + 1;
		if (randNum == 1)
		{
			aiChose = 1;
			updateBoard(49, 2);
			
		}
		else if (randNum == 2)
		{
			aiChose = 3;
			updateBoard(51, 2);
			
		}
		else if (randNum == 3)
		{
			aiChose = 7;
			updateBoard(55, 2);
			
		}
		else
		{
			aiChose = 9;
			updateBoard(57, 2);
			
		}

	}// end turn 0 if
	else if (turn == 1 && moves[1][1] != 88)
	{
		aiChose = 5;
		updateBoard(53, 2);
		
	}// end turn 1 if
	// turn 2 if
	else if (turn == 2)
		{
		if (moves[0][0] == 79)
		{
			aiChose = 9;
			updateBoard(57, 2);
			
		}
		else if (turn == 2 && moves[2][0] == 79)
		{
			aiChose = 7;
			updateBoard(51, 2);
			
		}
		else if (turn == 2 && moves[0][2] == 79)
		{
			aiChose = 3;
			updateBoard(55, 2);
			
		}
		else if (turn == 2 && moves[2][2] == 79)
		{
			aiChose = 1;
			updateBoard(49, 2);			
		}
	}// end turn 2 if
	else if (turn >= 3)
	{
		// CHECK FOR WIN
		// TOP ROW
		if (moves[0][0] == 79 && moves[0][1] == 79 && taken3 == 0)
		{
			aiChose = 3;
			updateBoard(51, 2);
			
		}
		else if (moves[0][0] == 79 && moves[0][2] == 79 && taken2 == 0)
		{
			aiChose = 2;
			updateBoard(50, 2);
			
		}
		else if (moves[0][1] == 79 && moves[0][2] == 79 && taken1 == 0)
		{
			aiChose = 1;
			updateBoard(49, 2);
			
		} // END TOP ROW
		// MIDDLE ROW
		else if (moves[1][0] == 79 && moves[1][1] == 79 && taken6 == 0)
		{
			aiChose = 6;
			updateBoard(54, 2);
			
		}
		else if (moves[1][0] == 79 && moves[1][2] == 79 && taken5 == 0)
		{
			aiChose = 5;
			updateBoard(53, 2);
			
		}
		else if (moves[1][1] == 79 && moves[1][2] == 79 && taken4 == 0)
		{
			aiChose = 4;
			updateBoard(52, 2);
			
		}// END MIDDLE ROW
		// BOTTOM ROW
		else if (moves[2][0] == 79 && moves[2][1] == 79 && taken9 == 0)
		{
			aiChose = 9;
			updateBoard(57, 2);
			
		}
		else if (moves[2][0] == 79 && moves[2][2] == 79 && taken8 == 0)
		{
			aiChose = 8;
			updateBoard(56, 2);
			
		}
		else if (moves[2][1] == 79 && moves[2][2] == 79 && taken7 == 0)
		{
			aiChose = 7;
			updateBoard(55, 2);
			
		} // END BOTTOM ROW
		// LEFT COLUMN
		else if (moves[0][0] == 79 && moves[1][0] == 79 && taken7 == 0)
		{
			aiChose = 7;
			updateBoard(55, 2);
			
		}
		else if (moves[0][0] == 79 && moves[2][0] == 79 && taken4 == 0)
		{
			aiChose = 4;
			updateBoard(52, 2);
			
		}
		else if (moves[1][0] == 79 && moves[2][0] == 79 && taken1 == 0)
		{
			aiChose = 1;
			updateBoard(49, 2);
			
		}// END LEFT COLUMN
		// MIDDLE COLUMN
		else if (moves[0][1] == 79 && moves[1][1] == 79 && taken8 == 0)
		{
			aiChose = 8;
			updateBoard(56, 2);
			
		}
		else if (moves[0][1] == 79 && moves[2][1] == 79 && taken5 == 0)
		{
			aiChose = 5;
			updateBoard(53, 2);
			
		}
		else if (moves[1][1] == 79 && moves[2][1] == 79 && taken2 == 0)
		{
			aiChose = 2;
			updateBoard(50, 2);
			
		}// END MIDDLE COLUMN
		// RIGHT COLUMN
		else if (moves[0][2] == 79 && moves[1][2] == 79 && taken9 == 0)
		{
			aiChose = 9;
			updateBoard(57, 2);
			
		}
		else if (moves[0][2] == 79 && moves[2][2] == 79 && taken6 == 0)
		{
			aiChose = 6;
			updateBoard(54, 2);
			
		}
		else if (moves[1][2] == 79 && moves[2][2] == 79 && taken3 == 0)
		{
			aiChose = 3;
			updateBoard(51, 2);
			
		}// END RIGHT COLUMN
		// RIGHT DIAGONAL
		else if (moves[0][0] == 79 && moves[1][1] == 79 && taken9 == 0)
		{
			aiChose = 9;
			updateBoard(57, 2);
			
		}
		else if (moves[0][0] == 79 && moves[2][2] == 79 && taken5 == 0)
		{
			aiChose = 5;
			updateBoard(53, 2);
			
		}
		else if (moves[1][1] == 79 && moves[2][2] == 79 && taken1 == 0)
		{
			aiChose = 1;
			updateBoard(49, 2);
			
		}// END RIGHT DIAGONAL
		// LEFT DIAGONAL
		else if (moves[0][2] == 79 && moves[1][1] == 79 && taken7 == 0)
		{
			aiChose = 7;
			updateBoard(55, 2);
			
		}
		else if (moves[0][2] == 79 && moves[2][0] == 79 && taken5 == 0)
		{
			aiChose = 5;
			updateBoard(53, 2);
			
		}
		else if (moves[1][1] == 79 && moves[2][0] == 79 && taken3 == 0)
		{
			aiChose = 3;
			updateBoard(51, 2);
			
		}// END LEFT DIAGONAL

		// END CHECK FOR WIN
	

		// CHECK FOR BLOCK
		// TOP ROW
		else if (moves[0][0] == 88 && moves[0][1] == 88 && taken3 == 0)
		{
			aiChose = 3;
			updateBoard(51, 2);

		}
		else if (moves[0][0] == 88 && moves[0][2] == 88 && taken2 == 0)
		{
			aiChose = 2;
			updateBoard(50, 2);

		}
		else if (moves[0][1] == 88 && moves[0][2] == 88 && taken1 == 0)
		{
			aiChose = 1;
			updateBoard(49, 2);

		} // END TOP ROW
		// MIDDLE ROW
		else if (moves[1][0] == 88 && moves[1][1] == 88 && taken6 == 0)
		{
			aiChose = 6;
			updateBoard(54, 2);

		}
		else if (moves[1][0] == 88 && moves[1][2] == 88 && taken5 == 0)
		{
			aiChose = 5;
			updateBoard(53, 2);

		}
		else if (moves[1][1] == 88 && moves[1][2] == 88 && taken4 == 0)
		{
			aiChose = 4;
			updateBoard(52, 2);

		}// END MIDDLE ROW
		// BOTTOM ROW
		else if (moves[2][0] == 88 && moves[2][1] == 88 && taken9 == 0)
		{
			aiChose = 9;
			updateBoard(57, 2);

		}
		else if (moves[2][0] == 88 && moves[2][2] == 88 && taken8 == 0)
		{
			aiChose = 8;
			updateBoard(56, 2);

		}
		else if (moves[2][1] == 88 && moves[2][2] == 88 && taken7 == 0)
		{
			aiChose = 7;
			updateBoard(55, 2);

		} // END BOTTOM ROW
		// LEFT COLUMN
		else if (moves[0][0] == 88 && moves[1][0] == 88 && taken7 == 0)
		{
			aiChose = 7;
			updateBoard(55, 2);

		}
		else if (moves[0][0] == 88 && moves[2][0] == 88 && taken4 == 0)
		{
			aiChose = 4;
			updateBoard(52, 2);

		}
		else if (moves[1][0] == 88 && moves[2][0] == 88 && taken1 == 0)
		{
			aiChose = 1;
			updateBoard(49, 2);

		}// END LEFT COLUMN
		// MIDDLE COLUMN
		else if (moves[0][1] == 88 && moves[1][1] == 88 && taken8 == 0)
		{
			aiChose = 8;
			updateBoard(56, 2);

		}
		else if (moves[0][1] == 88 && moves[2][1] == 88 && taken5 == 0)
		{
			aiChose = 5;
			updateBoard(53, 2);

		}
		else if (moves[1][1] == 88 && moves[2][1] == 88 && taken2 == 0)
		{
			aiChose = 2;
			updateBoard(50, 2);

		}// END MIDDLE COLUMN
		// RIGHT COLUMN
		else if (moves[0][2] == 88 && moves[1][2] == 88 && taken9 == 0)
		{
			aiChose = 9;
			updateBoard(57, 2);

		}
		else if (moves[0][2] == 88 && moves[2][2] == 88 && taken6 == 0)
		{
			aiChose = 6;
			updateBoard(54, 2);

		}
		else if (moves[1][2] == 88 && moves[2][2] == 88 && taken3 == 0)
		{
			aiChose = 3;
			updateBoard(51, 2);

		}// END RIGHT COLUMN
		// RIGHT DIAGONAL
		else if (moves[0][0] == 88 && moves[1][1] == 88 && taken9 == 0)
		{
			aiChose = 9;
			updateBoard(57, 2);

		}
		else if (moves[0][0] == 88 && moves[2][2] == 88 && taken5 == 0)
		{
			aiChose = 5;
			updateBoard(53, 2);

		}
		else if (moves[1][1] == 88 && moves[2][2] == 88 && taken1 == 0)
		{
			aiChose = 1;
			updateBoard(49, 2);

		}// END RIGHT DIAGONAL
		// LEFT DIAGONAL
		else if (moves[0][2] == 88 && moves[1][1] == 88 && taken7 == 0)
		{
			aiChose = 7;
			updateBoard(55, 2);

		}
		else if (moves[0][2] == 88 && moves[2][0] == 88 && taken5 == 0)
		{
			aiChose = 5;
			updateBoard(53, 2);

		}
		else if (moves[1][1] == 88 && moves[2][0] == 88 && taken3 == 0)
		{
			aiChose = 3;
			updateBoard(51, 2);

		}// END LEFT DIAGONAL
		// END BLOCKING
		else if (moves[0][0] == 88 && moves[1][2] == 88 && taken3 == 0)
		{
			aiChose = 3;
			updateBoard(51, 2);
		}
		else if (moves[0][2] == 88 && moves[1][0] == 88 && taken1 == 0)
		{
			aiChose = 1;
			updateBoard(49, 2);
		}
		else if (moves[2][2] == 88 && moves[1][0] == 88 && taken7 == 0)
		{
			aiChose = 7;
			updateBoard(54, 2);
		}
		else if (moves[2][0] == 88 && moves[1][2] == 88 && taken9 == 0)
		{
			aiChose = 9;
			updateBoard(57, 2);
		}
		else if (moves[0][0] == 88 && moves[1][1] == 88 && taken7 == 0)
		{
			aiChose = 7;
			updateBoard(55, 2);
		}
		else if (moves[1][1] == 88 && moves[2][2] == 88 && taken3 == 0)
		{
			aiChose = 3;
			updateBoard(51, 2);
		}
		else if (moves[1][1] == 88 && moves[0][2] == 88 && taken9 == 0)
		{
			aiChose = 9;
			updateBoard(57, 2);
		}

		else if ((moves[0][0] == 88 && moves[2][2] == 88)
			|| (moves[0][2] == 88 && moves[2][0] == 88))
		{
			int randNum = rand() % 4 + 1;
			if (randNum == 1 && taken2 == 0)
			{
				aiChose = 2;
				updateBoard(50, 2);
			}
			else if (randNum == 2 && taken4 == 0)
			{
				aiChose = 4;
				updateBoard(52, 2);
			}
			else if (randNum == 3 && taken6 == 0)
			{
				aiChose = 6;
				updateBoard(54, 2);
			}
			else if (randNum == 4 && taken8 == 0)
			{
				aiChose = 8;
				updateBoard(56, 2);
			}
		}

		else if (taken1 == 0 || taken3 == 0 || taken7 == 0 || taken9 == 0)
		{
			if (taken1 == 1 && taken7 == 0)
			{
				aiChose = 7;
				updateBoard(55, 2);

			}
			else if (taken3 == 1 && taken9 == 0)
			{
				aiChose = 9;
				updateBoard(57, 2);

			}
			else if (taken7 == 1 && taken1 == 0)
			{
				aiChose = 1;
				updateBoard(49, 2);

			}
			else if (taken9 == 1 && taken3 == 0)
			{
				aiChose = 3;
				updateBoard(51, 2);

			}
			else
			{
				bool breakLoop = false;
				for (int i = 0; i < 3 && !breakLoop; i++)
				{
					for (int j = 0; j < 3 && !breakLoop; j++)
					{
						if (moves[i][j] != 79 && moves[i][j] != 88)
						{
							if (i == 0 && j == 0)
							{
								updateBoard(49, 2);
							}
							else if (i == 0 && j == 1)
							{
								updateBoard(50, 2);
							}
							else if (i == 0 && j == 2)
							{
								updateBoard(51, 2);
							}
							else if (i == 1 && j == 0)
							{
								updateBoard(52, 2);
							}
							else if (i == 1 && j == 1)
							{
								updateBoard(53, 2);
							}
							else if (i == 1 && j == 2)
							{
								updateBoard(54, 2);
							}
							else if (i == 2 && j == 0)
							{
								updateBoard(55, 2);
							}
							else if (i == 2 && j == 1)
							{
								updateBoard(56, 2);
							}
							else if (i == 2 && j == 2)
							{
								updateBoard(57, 2);
							}
							breakLoop = true;
						}
					}
				}
			}
		}
			
		else
		{
			bool breakLoop = false;
			for (int i = 0; i < 3 && !breakLoop; i++)
			{
				for (int j = 0; j < 3 && !breakLoop; j++)
				{
					if (moves[i][j] != 79 && moves[i][j] != 88)
					{
						if (i == 0 && j == 0)
						{
							updateBoard(49, 2);
						}
						else if (i == 0 && j == 1)
						{
							updateBoard(50, 2);
						}
						else if (i == 0 && j == 2)
						{
							updateBoard(51, 2);
						}
						else if (i == 1 && j == 0)
						{
							updateBoard(52, 2);
						}
						else if (i == 1 && j == 1)
						{
							updateBoard(53, 2);
						}
						else if (i == 1 && j == 2)
						{
							updateBoard(54, 2);
						}
						else if (i == 2 && j == 0)
						{
							updateBoard(55, 2);
						}
						else if (i == 2 && j == 1)
						{
							updateBoard(56, 2);
						}
						else if (i == 2 && j == 2)
						{
							updateBoard(57, 2);
						}
						breakLoop = true;
					}
				}
			}
		}
	}// end of turn 3 if

	cout << "\nThe AI chose spot: " << aiChose;
	checkForWin();
}

// Add the move to the board
void userMove()
{
	cout << "\n\nEnter the space you'd like to place an 'X': ";

	char tempChar;
	tempChar = _getch();
	if ((tempChar >= 49 && tempChar <= 57))//ascii range 1 to 9
	{
		updateBoard(tempChar, 1);
		checkForWin();
	}



}// end userMove method

// Main method
int main()
{

	rlutil::setColor(15);
	cout << "Welcome to Mike's Tic Tac Toe Game!\n\n";
	do
	{

		cout << "Would you like to go first? (y/n): ";
		char response;
		cin >> response;

		if (response == 'y')
		{
			cout << "\nYour move first!\n";
			playerMove = 1;
		}
		else
		{
			cout << "\nAI will go first!\n";
			playerMove = 2;
		}

		cout << "\nPress any key to continue...\n";
		_getch();

		initializeGame();
		while (!gameOver)
		{
			if (playerMove % 2 == 1)
			{
				drawGameBoard(moves);
				userMove();
			}
			else
			{
				computerMove();
			}
		}

		if (playerWhoWon == 1)
		{
			cout << "\n\nYou win!";
		}
		else if (playerWhoWon == 2)
		{
			cout << "\n\nThe AI wins!";
		}
		else
		{
			cout << "\n\nIt's a draw!";
		}
		
		cout << "\n\nWould you like to play again? (y/n): ";
		cin >> playAgain;
		if (playAgain == 121 || playAgain == 89)
		{
			playAgain = 121;
		}
	} while (playAgain == 121);

	cout << "\n\nThanks for playing! Press any key to exit...";
	_getch();
	


	return 0;
} // end main