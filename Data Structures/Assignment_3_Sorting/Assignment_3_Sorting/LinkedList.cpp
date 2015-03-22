/*       Assignment 3 - Sorting        **
**            LinkedList.cpp           **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

#include "LinkedList.h"

using namespace std;

// Default constructor
LinkedList::LinkedList() 
{
	head = NULL;//a train without any cars
}

// Copy constructor
LinkedList::LinkedList(const LinkedList& orig) 
{

}

// Destructor
LinkedList::~LinkedList() 
{

}

// Add a line at the end LinkedList
void LinkedList::Append(int in)
{

	// Create node
	ListNode* newNode = new ListNode();
	newNode->setLine(in);
	if (head == NULL)
	{
		head = newNode;
	}
	else 
	{
		ListNode* counter = head;
		ListNode* behind = NULL;
		// While there are still more
		while (counter != NULL)
		{
			// Move to next node
			behind = counter;
			counter = counter->getNext();
		}

		// Attach to end
		behind->setNext(newNode);
	}
}

// Pivot the link
LinkedList* LinkedList::Concat(LinkedList* firstList, int pivotValue, LinkedList* secondList)
{
	LinkedList* newList = new LinkedList();
	for (int i = 0; i < firstList->Count(); i++)
	{
		newList->Append(firstList->ValueAt(i));
	}
	newList->Append(pivotValue);
	for (int i = 0; i < secondList->Count(); i++)
	{
		newList->Append(secondList->ValueAt(i));
	}
	delete firstList;
	delete secondList;

	return 0;
}

// Get the value at
int LinkedList::ValueAt(int index){

	ListNode* counter = head;

	if (index < 0)
	{
		cerr << "Line numbers must be > 0." << endl;
		return -1;
	}
	else
	{
		// Go to the nth spot
		for (int i = 0; i < index; i++)
		{
			counter = counter->getNext();
			if (counter == NULL)
			{
				cerr << "Line does not exist." << endl;
				return -1;
			}
		}

		// Display first line
		return counter->getLine();

	}
}

// Delete
void LinkedList::Delete(int index){
	ListNode* counter = head;
	ListNode* behind = NULL;
	if (index < 0)
	{
		cerr << "Line must be > 0." << endl;
		return;
	}
	// If at the start of the list
	else if (index == 0)
		head = counter->getNext();
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
void LinkedList::Insert(int in, int index)
{
	index++;
	ListNode* newNode = new ListNode();
	newNode->setLine(in);

	ListNode* counter = head;
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
			newNode->setNext(head);
			head = newNode;
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
int LinkedList::Count(){
	int lines = 0;
	ListNode* node = head;
	while (node != NULL)
	{
		node = node->getNext();
		lines++;
	}
	return lines;
}

