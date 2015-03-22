/*  Assignment 3 - Sorting (EXTERNAL)  **
**               Source.cpp            **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

/* 
RESOURCES:
http://www.dreamincode.net/forums/topic/57880-merge-sorting-a-look-with-recursion/
http://www.codeproject.com/Articles/92761/Work-C-Algorithm-of-External-Natural-Merge-Sort-wi
*/


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <limits>
#include <conio.h>
#include <time.h>

using namespace std;

// Declare constant variables
const int ARRAYSIZE = 10000;
const int BLOCKSIZEFORMERGE = 1000;
const int NUMWAYS = ARRAYSIZE / BLOCKSIZEFORMERGE;

// File names
string fileNames[]
= { "unsortedNumbers.txt", "file1", "file2", "extenalMergeSorted.txt" };

// Split - http://stackoverflow.com/a/236803
vector<string> &split(const string &s, char delim, vector<string> &elems) 
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


// Split - http://stackoverflow.com/a/236803
vector<string> split(const string &s, char delim) 
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

// Find minimum value
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

void mergeSortRec(int numbers[], string lines[], int left, int right,
	int* tempIntArray, string* tempStringArray)
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

		//sort subarrays
		mergeSortRec(numbers, lines, left, left + middlePoint,
			tempIntArray, tempStringArray);
		mergeSortRec(numbers, lines, left + middlePoint, right,
			tempIntArray, tempStringArray);

		// Merge the arrays together into tempIntArray
		for (int i = 0; i < length; i++)
		{
			// If there are still more elements in left, check for right elements.
			// If there are, compare them and see if left is smaller.
			// If it isn't, use the element in right array.
			if ((posLeft < left + middlePoint) &&
				((posRight == right)
				|| (min(numbers[posLeft], numbers[posRight]) == numbers[posLeft])))
			{
				tempIntArray[i] = numbers[posLeft];
				tempStringArray[i] = lines[posLeft];
				posLeft++;
			}
			else
			{
				tempIntArray[i] = numbers[posRight];
				tempStringArray[i] = lines[posRight];
				posRight++;
			}
		}

		// Copy the temp array back into numbers array
		for (int i = left; i<right; i++)
		{
			numbers[i] = tempIntArray[i - left];
			lines[i] = tempStringArray[i - left];
		}
	}
}

// mergeSortWrapper - http://www.cprogramming.com/tutorial/computersciencetheory/merge.html
bool mergeSortWrapper(int numbers[], string lines[], int BLOCKSIZEFORMERGE){
	
	// Allocate "scratch space"
	int* scratchInt = (int*)malloc(BLOCKSIZEFORMERGE * sizeof(int));
	string* scratchString = new string[BLOCKSIZEFORMERGE];

	if ((scratchInt != NULL) && (scratchString != NULL))
	{
		// Do the recursive merge sort
		mergeSortRec(numbers, lines, 0, BLOCKSIZEFORMERGE, scratchInt, scratchString);

		// Free the memory used
		free(scratchInt);
		return true;
	}
	else
	{
		cerr << "No memory available or invalid size." << endl;
		return false;
	}
}

// chunksSort (Manages the 1000 piece chunks)
bool chunksSort(string fileNames[], int numbers[], string lines[],
	int BLOCKSIZEFORMERGE, int ARRAYSIZE){
	
	// Set up input file
	ifstream inStream(fileNames[0].c_str());
	if (inStream.fail())
	{
		cerr << "Couldn't open file containing numbers." << endl << endl;
		return false;
	}

	// Set up output files
	ofstream outStreamA(fileNames[1].c_str());
	ofstream outStreamB(fileNames[2].c_str());
	if (outStreamA.fail() || outStreamB.fail())
	{
		cerr << "Couldn't open output stream." << endl << endl;
		return false;
	}

	// Load the numbers
	for (int i = 0; i < ARRAYSIZE; i += BLOCKSIZEFORMERGE)
	{
		for (int j = 0; j < BLOCKSIZEFORMERGE; j++)
		{
			// Load lines
			string fileLine;
			getline(inStream, fileLine);

			// Split the lines
			vector<string> lineParts = split(fileLine, ':');

			// Get the line number
			string lineNumber = lineParts.at(0);
			lines[j] = lineNumber;

			// Get the number
			stringstream ss(lineParts.at(1));
			int number;
			ss >> number;
			numbers[j] = number;
		}

		// Do the merge sort
		if (!mergeSortWrapper(numbers, lines, BLOCKSIZEFORMERGE))
		{
			cerr << "Sorting failed." << endl;
			return false;
		}

		// Put first half of the sorted arrays into scratch file
		if (i<(ARRAYSIZE / 2))
		{
			for (int j = 0; j<BLOCKSIZEFORMERGE; j++)
			{
				outStreamA << lines[j] << ":" << numbers[j];
				if ((i + j) < (ARRAYSIZE / 2))
				{
					outStreamA << endl;
				}
			}
		}
		// Put second half of the sorted arrays into different scratch file
		else
		{
			for (int j = 0; j<BLOCKSIZEFORMERGE; j++)
			{
				outStreamB << lines[j] << ":" << numbers[j];
				if ((i + j) < (ARRAYSIZE))
				{
					outStreamB << endl;
				}
			}
		}
	}

	// Close streams
	inStream.close();
	outStreamA.close();
	outStreamB.close();
	return true;

}

// counterCompletion
bool counterCompletion(int counters[], int numCounters, int maxNum){
	for (int i = 0; i<numCounters; i++)
	{
		if (counters[i] <= maxNum)
		{
			return false;
		}
	}
	return true;
}

// Merge n sorted list into file
bool nWayMerge(string fileNames[], int BLOCKSIZEFORMERGE){
	int counters[NUMWAYS];
	string lines[NUMWAYS];
	int numbers[NUMWAYS];

	vector<int> lastThreeNums;
	lastThreeNums.push_back(-1);
	lastThreeNums.push_back(-2);
	lastThreeNums.push_back(-3);

	fstream inStreams[NUMWAYS];
	ofstream outStream(fileNames[3].c_str());
	if (outStream.fail())
	{
		cerr << "Couldn't open output stream." << endl << endl;
		return false;
	}

	// Read in first half
	for (int i = 0; i<(NUMWAYS / 2); i++)
	{
		inStreams[i].open(fileNames[1].c_str(), ios::in);
		if (inStreams[i].fail())
		{
			cerr << "Couldn't open input stream number " << i + 1 << "." << endl << endl;
			return false;
		}
		
	    //http://stackoverflow.com/a/5207600/1736461
		for (int j = 0; j < (i*BLOCKSIZEFORMERGE); ++j)
		{
			inStreams[i].ignore(numeric_limits<streamsize>::max(), '\n');
		}
		counters[i] = 0;
	}
	
	// Read in second half
	for (int i = (NUMWAYS / 2); i<NUMWAYS; i++)
	{
		inStreams[i].open(fileNames[2].c_str(), ios::in);
		for (int j = 0; j < ((i - (NUMWAYS / 2))*BLOCKSIZEFORMERGE); ++j)
		{
			inStreams[i].ignore(numeric_limits<streamsize>::max(), '\n');
		}
		counters[i] = 0;
	}

	// Get the first num
	for (int i = 0; i<NUMWAYS; i++)
	{
		getline(inStreams[i], lines[i]);
		//get number from file
		vector<string> lineParts = split(lines[i], ':');
		stringstream ss(lineParts.at(1));
		ss >> numbers[i];
		counters[i]++;
	}

	//http://en.wikipedia.org/wiki/Merge_algorithm
	while (!counterCompletion(counters, NUMWAYS, BLOCKSIZEFORMERGE))
	{
		// Get lowest number
		int lowKeyCursor = 0;
		for (int i = 0; i < NUMWAYS; i++)
		{
			if (numbers[i] < numbers[lowKeyCursor])
			{
				lowKeyCursor = i;
			}
		}

		outStream << lines[lowKeyCursor] << endl;
		counters[lowKeyCursor]++;

		lastThreeNums.insert(lastThreeNums.begin(), numbers[lowKeyCursor]);
		if ((lastThreeNums.at(0) == lastThreeNums.at(1))
			&& (lastThreeNums.at(0) == lastThreeNums.at(2)))
		{
			cout << "Duplicates: " << numbers[lowKeyCursor] << endl;
		}

		// Get the next line
		if (counters[lowKeyCursor] <= BLOCKSIZEFORMERGE)
		{
			getline(inStreams[lowKeyCursor], lines[lowKeyCursor]);
			vector<string> lineParts = split(lines[lowKeyCursor], ':');
			stringstream ss(lineParts.at(1));
			ss >> numbers[lowKeyCursor];
		}
		else
		{
			numbers[lowKeyCursor] = numeric_limits<int>::max();
		}
	}
	return true;
}

//entry point of program
int main(int argc, char** argv) {


	// Numbers array
	static int numbers[BLOCKSIZEFORMERGE];
	// Lines array for original number
	static string lines[BLOCKSIZEFORMERGE];
	
	// Start clock
	clock_t startTime = clock();

	// Display reading in file and name
	cout << "Reading numbers from " << fileNames[0] << "." << endl;


	// Sort in chunks of BLOCKSIZEFORMERGE (1000)
	if (!chunksSort(fileNames, numbers, lines, BLOCKSIZEFORMERGE, ARRAYSIZE))
	{
		cerr << "Sorting failed." << endl;
		system("PAUSE");
		return -1;
	}

	// Merge scratch files into one file
	if (!nWayMerge(fileNames, BLOCKSIZEFORMERGE))
	{
		cerr << "Writing failed." << endl;
		system("PAUSE");
		return -1;
	}


	clock_t endTime = clock();
	clock_t clockTicksTaken = endTime - startTime;
	long double elapsedTime = (clockTicksTaken / (double)CLOCKS_PER_SEC) * 1000;

	cout << "Sorted numbers written to " << fileNames[3] << "." << endl;
	cout << endl << "External merge sort took: " << elapsedTime << "ns" << endl;
	system("PAUSE"); 

	return 0;
}
