/*  Assignment 3 - Sorting (EXTERNAL)  **
**              ListNode.cpp           **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

#include "ListNode.h"

using namespace std;

// Default constructor
ListNode::ListNode()
{
	_next = NULL;
	_line = "";
	_number = -1;
}

// Copy constructor
ListNode::ListNode(const ListNode& orig) 
{
}

// Destructor
ListNode::~ListNode() 
{
}

// getLine
string ListNode::getLine()
{
	return _line;
}

// setLine
void ListNode::setLine(string in)
{
	_line = in;
}

// getNext
ListNode* ListNode::getNext()
{
	return _next;
}

// setNext
void ListNode::setNext(ListNode* in)
{
	_next = in;
}
