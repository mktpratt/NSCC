/*  Assignment 3 - Sorting (EXTERNAL)  **
**             LinkedList.cpp          **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

// Reference - http://cppknowcoding.greatknow.com/view/21020-circular-linked-list.html

#include "LinkedList.h"

using namespace std;

// Default constructor
LinkedList::LinkedList() 
{
	_head = NULL;
}

// Copy constructor
LinkedList::LinkedList(const LinkedList& orig) 
{
}

// Destructor
LinkedList::~LinkedList() 
{
}

// Append
void LinkedList::append(string in)
{
	ListNode* newNode = new ListNode();
	newNode->setLine(in);
	if (_head == NULL)
	{
		_head = newNode;
	}
	else 
	{
		ListNode* counter = _head;
		ListNode* behind = NULL;
		while (counter != NULL)
		{
			// Move to the next node
			behind = counter;
			counter = counter->getNext();
		}

		// Attatch to the end
		behind->setNext(newNode);
	}
}

// Remove
void LinkedList::remove(int index)
{
	ListNode* counter = _head;
	ListNode* behind = NULL;
	if (index < 0)
	{
		cerr << "Line must be > 0." << endl;
		return;
	}
	// If at the start of the list
	else if (index == 0)
		_head = counter->getNext();
	else
	{
		// Go to the nth spot
		for (int i = 0; i < index; i++)
		{
			behind = counter;
			counter = counter->getNext();
			if (counter == NULL)
			{
				cerr << "Line does not exist." << endl;
				return;
			}
		}

		// Delete the skipped one
		behind->setNext(behind->getNext());
	}

	// Delete the node
	delete counter;
}

// Insert
void LinkedList::insert(string in, int index)
{
	index++;
	ListNode* newNode = new ListNode();
	newNode->setLine(in);

	ListNode* counter = _head;
	ListNode* behind = NULL;
	int count = 0;

	while (counter != NULL)
	{
		if (++count == index)
			break;
		behind = counter;
		counter = counter->getNext();
	}

	if (counter != NULL)
	{
		if (behind == NULL)
		{
			// Insert at start
			newNode->setNext(_head);
			_head = newNode;
		}
		else
		{
			// Insert into middle
			newNode->setNext(behind->getNext());
			behind->setNext(newNode);
		}
	}
	else
	{
		// Doesn't exist
		cerr << "Insertion out of bounds." << endl;
		return;
	}
}

// Count
int LinkedList::count()
{
	int lines = 0;
	ListNode* node = _head;
	while (node != NULL)
	{
		node = node->getNext();
		lines++;
	}
	return lines;
}

// showAllLines
void LinkedList::showAllLines(string lprefix, int lindex)
{
	int lnum = lindex;
	ListNode* node = _head;
	while (node != NULL)
	{
		// Show the line
		cout << lnum << lprefix << node->getLine() << endl;
		node = node->getNext();
		lnum++;
	}
	return;
}

// showLines
void LinkedList::showLines(string lprefix, int lindex, int lbegin, int lend)
{
	int lnum = lindex;
	ListNode* counter = _head;

	if (lbegin < 0 || lend < 0)
	{
		cerr << "Line numbers must be non-negative integers." << endl;
		return;
	}
	else if (lbegin > lend)
	{
		cerr << "Finishing index must equal or exceed starting index."
			<< endl;
		return;
	}
	else
	{
		// Go to the nth spot
		for (int i = 0; i < lbegin; i++)
		{
			counter = counter->getNext();
			lnum++;
			if (counter == NULL)
			{
				cerr << "Line does not exist." << endl;
				return;
			}
		}

		// Display the first line
		cout << lnum << lprefix << counter->getLine() << endl;

		// Go to the nth spot
		for (int i = 0; i < (lend - lbegin); i++)
		{
			counter = counter->getNext();
			lnum++;
			if (counter == NULL)
			{
				cerr << "Line does not exist." << endl;
				return;
			}
			else
			{
				// Display the line
				cout << lnum << lprefix << counter->getLine() << endl;
			}
		}
	}


}

// << Operator
ostream& operator<<(ostream& output, LinkedList& list){
	ListNode* node = list._head;
	while (node != NULL)
	{
		output << node->getLine();
		node = node->getNext();
		if (node != NULL)
			output << endl;
	}
	return output;
}
