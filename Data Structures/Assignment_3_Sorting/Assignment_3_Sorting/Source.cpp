/*       Assignment 3 - Sorting        **
**               Source.cpp            **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <conio.h>
#include <iomanip>

using namespace std;

/*
RESOURCES:
Bubble Sort - Hal's powerpoint slides
Selection Sort - Hal's powerpoint slides
Insertion Sort - Hal's powerpoint slides
Shell Sort - Hal's powerpoint slides
Merge Sort - http://rosettacode.org/wiki/Sorting_algorithms/Merge_sort
Quick Sort - http://en.wikipedia.org/wiki/Quicksort
*/

// Declare constant variables
const int NUMSORTS = 6;
const int ARRAYSIZE = 10000;
const int RANGEMAX = 32767;
const int BLOCKSIZEFORMERGE = 1000;

// Have a welcoming prompt that explains the program
void welcomePrompt()
{
	cout << "Welcome to our sorting program!." << endl;
	cout << "This program will sort " << ARRAYSIZE << " random numbers by various methods." << endl;
}

// Menu prompt that displays the available sorts
string promptMenu()
{
	string response = "";
	cout << endl;
	cout << "Please view the menu below and enter a sorting method." << endl;
	cout << "===============================================" << endl;
	cout << "=   bu - Bubble Sort                          =" << endl;
	cout << "=   se - Selection Sort                       =" << endl;
	cout << "=   in - Insertion Sort                       =" << endl;
	cout << "=   sh - Shell Sort                           =" << endl;
	cout << "=   me - Merge Sort                           =" << endl;
	cout << "=   qu - Quick Sort                           =" << endl;
	cout << "=                                             =" << endl;
	cout << "=   all - View All Sorts                      =" << endl;
	cout << "=                                             =" << endl;
	cout << "=   exit - Euit the program                   =" << endl;
	cout << "===============================================" << endl;

	do
	{
		cout << endl << "Which type of sort would you like to use?: ";
		getline(cin, response);
	} while (response != "bu" && response != "se" && response != "in" && response != "sh"
		&& response != "me" && response != "qu" && response != "all" && response != "exit");

	return response;
}

// Bubble sort
long double bubbleSort(int numbers[][NUMSORTS], int arraySize, int column)
{
	// Start the timer
	clock_t startTime = clock();

	int compareTo = arraySize;//start by going all the way through

	// Do the bubble sort
	// While there may be numbers left to sort
	do
	{
		int counterPoint = 0;
		for (int i = 1; i < compareTo; i++)
		{
			// Check if the number behind is greater than number ahead
			if (numbers[i - 1][column] > numbers[i][column])
			{
				int holder = numbers[i][column];
				numbers[i][column] = numbers[i - 1][column];
				numbers[i - 1][column] = holder;
				counterPoint = i;
			}
		}
		compareTo = counterPoint;
	} while (compareTo != 0);

	// Stop timer and return the time
	clock_t endTime = clock();
	clock_t clockTicksTaken = endTime - startTime;
	long double elapsedTime = (clockTicksTaken / (double)CLOCKS_PER_SEC) * 1000;

	return elapsedTime;
}

// Selection sort
long double selectionSort(int numbers[][NUMSORTS], int arraySize, int column)
{
	// Start the timer
	clock_t startTime = clock();

	int pos_min, temp;

	// Do the selection sort
	for (int i = 0; i < arraySize; i++)
	{
		// Set to the current index
		pos_min = i;

		for (int j = i + 1; j < arraySize; j++)
		{

			// Find the minimum
			if (numbers[j][column] < numbers[pos_min][column])
				pos_min = j;
		}

		// Swap
		if (pos_min != i)
		{
			temp = numbers[i][column];
			numbers[i][column] = numbers[pos_min][column];
			numbers[pos_min][column] = temp;
		}
	}

	// Stop timer and return the time
	clock_t endTime = clock();
	clock_t clockTicksTaken = endTime - startTime;
	long double elapsedTime = (clockTicksTaken / (double)CLOCKS_PER_SEC) * 1000;
	return elapsedTime;
}

// Insertion sort
long double insertionSort(int numbers[][NUMSORTS], int arraySize, int column)
{
	// Start the timer
	clock_t startTime = clock();

	// Do the insertion sort
	for (int i = 1; i < arraySize; i++)
	{
		int valuePickedUp = numbers[i][column];
		int hole = i;

		while ((hole > 0)
			&& (valuePickedUp < numbers[hole - 1][column]))
		{
			// Shift the larger number further into the array
			numbers[hole][column] = numbers[hole - 1][column];
			// Move the hole
			hole = hole - 1;
		}

		// Insert the number
		numbers[hole][column] = valuePickedUp;
	}

	// Stop timer and return the time
	clock_t endTime = clock();
	clock_t clockTicksTaken = endTime - startTime;
	long double elapsedTime = (clockTicksTaken / (double)CLOCKS_PER_SEC) * 1000;

	return elapsedTime;
}

// Shell sort
long double shellSort(int numbers[][NUMSORTS], int arraySize, int column)
{
	// Start the timer
	clock_t startTime = clock();
	int j;
	// Do the shell sort
	for (int increment = arraySize / 2; increment > 0; increment /= 2)
	{
		for (int i = increment; i < arraySize; i++)
		{
			int temp = numbers[i][column];
			for (j = i; j >= increment; j -= increment)
			{
				if (temp < numbers[j - increment][column])
				{
					numbers[j][column] = numbers[j - increment][column];
				}
				else
				{
					break;
				}
			}
			numbers[j][column] = temp;
		}
	}

	// Stop timer and return the time
	clock_t endTime = clock();
	clock_t clockTicksTaken = endTime - startTime;
	long double elapsedTime = (clockTicksTaken / (double)CLOCKS_PER_SEC) * 1000;
	return elapsedTime;
}

// Min used by merge sort
int min(int x, int y)
{
	if (x < y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

// Handle recursion for merge sort
void mergeSortRec(int numbers[][NUMSORTS], int column, int left, int right, int* tempIntArray)
{
	if (right == left + 1)
	{
		return;
	}
	else
	{
		int length = right - left;
		int middlePoint = length / 2;
		// posLeft is position in left sub-array
		int posLeft = left;
		// posRight is position in right sub-array
		int posRight = left + middlePoint;

		// Sort the sub-arrays recursively
		mergeSortRec(numbers, column, left, left + middlePoint, tempIntArray);
		mergeSortRec(numbers, column, left + middlePoint, right, tempIntArray);

		// Merge the arrays together into tempIntArray
		for (int i = 0; i < length; i++)
		{
			// If there are still more elements in left, check for right elements.
			// If there are, compare them and see if left is smaller.
			// If it isn't, use the element in right array.
			if ((posLeft < left + middlePoint) &&
				((posRight == right)
				|| (min(numbers[posLeft][column], numbers[posRight][column]) == numbers[posLeft][column])))
			{
				tempIntArray[i] = numbers[posLeft][column];
				posLeft++;
			}
			else
			{
				tempIntArray[i] = numbers[posRight][column];
				posRight++;
			}
		}

		// Copy the temp array back into numbers array
		for (int i = left; i < right; i++)
		{
			numbers[i][column] = tempIntArray[i - left];
		}
	}
}

// Merge sort
long double mergeSort(int numbers[][NUMSORTS], int arraySize, int column)
{
	// Start the timer
	clock_t startTime = clock();

	// Create a temp array pointer
	int* temp = new int[arraySize];

	// Do the recursive merge sort
	mergeSortRec(numbers, column, 0, arraySize, temp);

	// Stop timer and return the time
	clock_t endTime = clock();
	clock_t clockTicksTaken = endTime - startTime;
	long double elapsedTime = (clockTicksTaken / (double)CLOCKS_PER_SEC) * 1000;
	return elapsedTime;
}

// Handle pivot for quickSort
int pivot(int numbers[][NUMSORTS], int column, int left, int right, int pivotIndex)
{
	int pivotValue = numbers[pivotIndex][column];
	// Move pivoted number to end
	numbers[pivotIndex][column] = numbers[right][column];
	numbers[right][column] = pivotValue;
	int storeIndex = left;

	for (int i = left; i < right; i++)
	{
		if (numbers[i][column] <= pivotValue)
		{
			// Swap the values
			int valueHolder = numbers[i][column];
			numbers[i][column] = numbers[storeIndex][column];
			numbers[storeIndex][column] = valueHolder;
			storeIndex++;
		}
	}

	// Move the pivot point to final place
	int valueHolder = numbers[storeIndex][column];
	numbers[storeIndex][column] = numbers[right][column];
	numbers[right][column] = valueHolder;
	return storeIndex;
}

// Handle recursion for quick sort
void quickSortRec(int numbers[][NUMSORTS], int column, int left, int right)
{
	// If there are 2 or more items
	if (left < right)
	{
		int pivotIndex = right;

		// Separate bigger and smaller numbers to get final position
		int pivotNewIndex = pivot(numbers, column, left, right, pivotIndex);
		// Sort elements below pivot
		quickSortRec(numbers, column, left, pivotNewIndex - 1);
		// Sort elements = or > than pivot
		quickSortRec(numbers, column, pivotNewIndex + 1, right);
	}
}

// Quick sort
long double quickSort(int numbers[][NUMSORTS], int arraySize, int column)
{
	// Start the timer
	clock_t startTime = clock();

	// Send numbers to recursive sorting
	quickSortRec(numbers, column, -1, (arraySize - 1));

	// Stop timer and return the time
	clock_t endTime = clock();
	clock_t clockTicksTaken = endTime - startTime;
	long double elapsedTime = (clockTicksTaken / (double)CLOCKS_PER_SEC) * 1000;
	return elapsedTime;
}

// Generate NUMSORTS (6) sets of ARRAYSIZE (10000) numbers and store them into a 2-D array - [10000][7]
void generateNumbers(int numbers[][NUMSORTS], int arraySize, int rangeMax){

	// Initalize random seed
	srand(time(NULL));

	for (int i = 0; i < arraySize; i++)
	{
		// Random between 0 and 32767
		int number = rand() % (rangeMax + 1);
		for (int j = 0; j < NUMSORTS; j++)
		{
			numbers[i][j] = number;
		}
	}
}

// Display the numbers
void viewNumbers(int numbers[][NUMSORTS], int arraySize, int arrayChoice, int displayCount, int page, int start)
{
	cout << "===============================================" << endl;
	cout << "        SORTED NUMBERS  " << start + 1 << "-" << displayCount * page << "/" << arraySize << endl;
	cout << "===============================================" << endl;

	// Display 3 numbers per row
	for (int i = start; i < start + displayCount; i += 3)
	{
		cout << setw(10) << numbers[i][arrayChoice] << setw(10) << numbers[i + 1][arrayChoice] << setw(10) << numbers[i + 2][arrayChoice];
		cout << endl;
	}
	cout << endl;

	cout << "Displaying numbers " << (displayCount * page - (displayCount - 1)) << " to " <<
		displayCount * page << " out of " << arraySize << " numbers that have been sorted." << endl << endl;

}

// Save the sorted files with Time included at thet top
void saveToFile(long double time, int numbers[][NUMSORTS], int arraySize, int arrayChoice, string outFileName)
{
	// Open the stream
	ofstream outStream(outFileName.c_str());
	if (outStream.fail())
	{
		cerr << "Couldn't open output stream." << endl;
	}
	else
	{
		// Write the file
		outStream << "Time taken to sort (nanoseconds): " << time << endl << endl;
		for (int i = 0; i < arraySize; i++)
		{
			outStream << "Line " << (i + 1) << ":" << numbers[i][arrayChoice];
			if (i < (arraySize - 1))
			{
				outStream << endl;
			}
		}

	}
	// Close the stream
	outStream.close();
}

// Save the default unsorted file
void saveUnsortedFile(int numbers[][NUMSORTS], int arraySize, int arrayChoice, string outFileName)
{
	// Open the stream
	ofstream outStream(outFileName.c_str());
	if (outStream.fail())
	{
		cerr << "Couldn't open output stream." << endl;
	}
	else
	{
		// Write the lines to the file
		for (int i = 0; i < arraySize; i++)
		{
			outStream << "Line " << (i + 1) << ":" << numbers[i][arrayChoice];
			if (i < (arraySize - 1))
			{
				outStream << endl;
			}
		}

	}
	// Close the stream
	outStream.close();
}

// Main method
int main(int argc, char** argv) {

	int nWays = ARRAYSIZE / BLOCKSIZEFORMERGE;
	int displayCount = 50;
	int page = 1;
	int startPoint = 0;

	string input;

	welcomePrompt();

	do
	{
		// Prompt the menu
		input = promptMenu();

		// Numbers array
		int numbers[ARRAYSIZE][NUMSORTS];

		// Timer timings
		long double timings[NUMSORTS];

		// Sorting names
		string sortNames[] = {
			"Bubble Sort",
			"Selection Sort",
			"Insertion Sort",
			"Shell Sort",
			"Merge Sort",
			"Quick Sort"
		};

		// Generate the random numbers
		generateNumbers(numbers, ARRAYSIZE, RANGEMAX);
		// Save the random file
		saveUnsortedFile(numbers, ARRAYSIZE, 0, "unsortedNumbers.txt");

		// Bubble Sort - DONE
		if (input == "bu")
		{
			timings[0] = bubbleSort(numbers, ARRAYSIZE, 1);
			viewNumbers(numbers, ARRAYSIZE, 1, displayCount, page, startPoint);
			cout << "Time taken to perform Bubble Sort (ns): " << timings[0] << endl << endl;
			cout << "Would you like to save the file? (y/n): ";
			getline(cin, input);
			if (input == "y")
			{
				saveToFile(timings[0], numbers, ARRAYSIZE, 1, "bubbleSortSorted.txt");
				cout << "File saved as bubbleSortSorted.txt!" << endl;
			}
		}
		// Selection Sort - DONE
		else if (input == "se")
		{
			timings[1] = selectionSort(numbers, ARRAYSIZE, 2);
			viewNumbers(numbers, ARRAYSIZE, 2, displayCount, page, startPoint);
			cout << "Time taken to perform Selection Sort (ns): " << timings[1] << endl << endl;
			cout << "Would you like to save the file? (y/n): ";
			getline(cin, input);
			if (input == "y")
			{
				saveToFile(timings[1], numbers, ARRAYSIZE, 2, "selectionSortSorted.txt");
				cout << "File saved as selectionSortSorted.txt!" << endl;
			}
		}
		// Insertion Sort - DONE
		else if (input == "in")
		{
			timings[2] = insertionSort(numbers, ARRAYSIZE, 3);
			viewNumbers(numbers, ARRAYSIZE, 3, displayCount, page, startPoint);
			cout << "Time taken to perform Insertion Sort (ns): " << timings[2] << endl << endl;
			cout << "Would you like to save the file? (y/n): ";
			getline(cin, input);
			if (input == "y")
			{
				saveToFile(timings[2], numbers, ARRAYSIZE, 3, "insertionSortSorted.txt");
				cout << "File saved as insertionSortSorted.txt!" << endl;
			}
		}
		// Shell Sort - DONE
		else if (input == "sh")
		{
			timings[3] = shellSort(numbers, ARRAYSIZE, 4);
			viewNumbers(numbers, ARRAYSIZE, 4, displayCount, page, startPoint);
			cout << "Time taken to perform Shell Sort (ns): " << timings[3] << endl << endl;
			cout << "Would you like to save the file? (y/n): ";
			getline(cin, input);
			if (input == "y")
			{
				saveToFile(timings[3], numbers, ARRAYSIZE, 4, "shellSortSorted.txt");
				cout << "File saved as shellSortSorted.txt!" << endl;
			}
		}
		// Merge Sort - DONE
		else if (input == "me")
		{
			timings[4] = mergeSort(numbers, ARRAYSIZE, 5);
			viewNumbers(numbers, ARRAYSIZE, 5, displayCount, page, startPoint);
			cout << "Time taken to perform Merge Sort (ns): " << timings[4] << endl << endl;
			cout << "Would you like to save the file? (y/n): ";
			getline(cin, input);
			if (input == "y")
			{
				saveToFile(timings[4], numbers, ARRAYSIZE, 5, "mergeSortSorted.txt");
				cout << "File saved as mergeSortSorted.txt!" << endl;
			}
		}
		// Quick Sort - DONE
		else if (input == "qu")
		{
			timings[5] = quickSort(numbers, ARRAYSIZE, 6);
			viewNumbers(numbers, ARRAYSIZE, 6, displayCount, page, startPoint);
			cout << "Time taken to perform Quick Sort (ns): " << timings[5] << endl << endl;
			cout << "Would you like to save the file? (y/n): ";
			getline(cin, input);
			if (input == "y")
			{
				saveToFile(timings[5], numbers, ARRAYSIZE, 6, "quickSortSorted.txt");
				cout << "File saved as quickSortSorted.txt!" << endl;
			}
		}
		// Display all
		else if (input == "all")
		{
			cout << endl;
			timings[0] = bubbleSort(numbers, ARRAYSIZE, 1);
			timings[1] = selectionSort(numbers, ARRAYSIZE, 2);
			timings[2] = insertionSort(numbers, ARRAYSIZE, 3);
			timings[3] = shellSort(numbers, ARRAYSIZE, 4);
			timings[4] = mergeSort(numbers, ARRAYSIZE, 5);
			timings[5] = quickSort(numbers, ARRAYSIZE, 6);

			for (int i = 0; i < NUMSORTS; i++)
			{
				cout << sortNames[i] << " time taken: " << timings[i] << "ns" << endl;
			}

			cout << endl << "Would you like to save all the files? : ";
			getline(cin, input);
			if (input == "y")
			{
				// Save all the files
				saveToFile(timings[0], numbers, ARRAYSIZE, 1, "bubbleSortSorted.txt");
				cout << "File saved as bubbleSortSorted.txt!" << endl;
				saveToFile(timings[1], numbers, ARRAYSIZE, 2, "selectionSortSorted.txt");
				cout << "File saved as selectionSortSorted.txt!" << endl;
				saveToFile(timings[2], numbers, ARRAYSIZE, 3, "insertionSortSorted.txt");
				cout << "File saved as insertionSortSorted.txt!" << endl;
				saveToFile(timings[3], numbers, ARRAYSIZE, 4, "shellSortSorted.txt");
				cout << "File saved as shellSortSorted.txt!" << endl;
				saveToFile(timings[4], numbers, ARRAYSIZE, 5, "mergeSortSorted.txt");
				cout << "File saved as mergeSortSorted.txt!" << endl;
				saveToFile(timings[5], numbers, ARRAYSIZE, 6, "quickSortSorted.txt");
				cout << "File saved as quickSortSorted.txt!" << endl;
			}

		}
		else if (input == "exit")
		{
			cout << endl << "The program will now close!" << endl;
			system("PAUSE");
			break;
		}

		cout << "Would you like to try another method? (y/n): ";
		getline(cin, input);
		if (input == "n")
		{
			break;
		}

	} while (input == "y");
	
	//system("PAUSE");
	system("exit");
	return 0;
}