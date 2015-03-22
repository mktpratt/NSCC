/*      Assignment 1 - Linked Lists          **
**             LinkedList.cpp                **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */


#include "LinkedList.h"

#ifndef NULL
#define NULL 0
#endif 

// Default constructor
LinkedList::LinkedList() : first(NULL), totalines(-1)
{

}

LinkedList::~LinkedList()
{
	Node *node = first;

	while (node != NULL)
	{
		Node *temp = node;

		node = node->next;
		delete temp;
	}
}

// Destructor
void LinkedList::add(string line)
{
	Node *node = new Node();
	node->line = line;
	this->totalines++;

	if (first == NULL)
	{
		first = node;
	}
	else
	{
		Node *currNode = first;
		Node *prevNode = NULL;

		while (currNode != NULL)
		{
			prevNode = currNode;
			currNode = currNode->next;
		}

		if (prevNode != NULL)
		{
			prevNode->next = node;
		}
	}
}

void LinkedList::deleteNode(int nodenum)
{
	int index = -1;

	Node *node = first;
	Node *prev = NULL;

	while (node != NULL)
	{
		index++;

		if (index == nodenum)
		{
			break;
		}

		prev = node;
		node = node->next;
	}

	if (index >= 0)
	{
		if (node == first)
		{
			first = node->next;
		}
		else
		{
			prev->next = node->next;
		}

		delete node;
		totalines--;
	}
} // End method deleteNode

string LinkedList::getValue(int nodenum) 
{
	int index = -1;
	string val = "";

	Node *node = first;

	while (node != NULL)
	{
		index++;

		if (index == nodenum)
		{
			val = node->line;
			break;
		}

		node = node->next;
	}
	return val;
} // End method getValud

void LinkedList::insertAtIndex(int index, string nLine)
{
	Node *node = new Node();
	node->line = nLine;
	totalines++;

	if (index == 0)
	{

		node->next = first;
		first = node;

	}
	else 
	{
		index--;
		int i = 0;
		Node *prev = first;

		while (prev != NULL)
		{
			if (i == index)
			{
				break;
			}

			prev = prev->next;
			i++;
		} // End while

		if (first == NULL)
		{
			first = node;
		}
		else
		{
			if (prev != NULL)
			{
				node->next = prev->next;
				prev->next = node;
			}
			else
			{
				add(nLine);
			}
		}
	} // End else
} // End method insertAtIndex

ostream& operator<<(ostream& output, LinkedList& list)
{
	Node *currNode = list.first;
	int i = 0;

	// Loop while not empty
	while (currNode != NULL)
	{
		output << i << ":   " << currNode->line << endl;
		currNode = currNode->next;
		i++;
	}
	return output;
}

int LinkedList::getNumLines()
{
	return this->totalines;
}