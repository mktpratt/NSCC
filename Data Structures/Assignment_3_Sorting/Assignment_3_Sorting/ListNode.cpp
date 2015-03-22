/*       Assignment 3 - Sorting        **
**             ListNode.cpp            **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

#include "ListNode.h"

// Default constructor
ListNode::ListNode() {
	next = NULL;
	value = -1;
}

// Copy constructor
ListNode::ListNode(const ListNode& orig) {
}

// Destructor
ListNode::~ListNode() {
}

// getLine
int ListNode::getLine(){
	return value;
}

// setLine
void ListNode::setLine(int in){
	value = in;
}

// getNext
ListNode* ListNode::getNext(){
	return next;
}

// setNext
void ListNode::setNext(ListNode* in){
	next = in;
}
