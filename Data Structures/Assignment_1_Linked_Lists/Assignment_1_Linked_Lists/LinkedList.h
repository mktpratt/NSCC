/*      Assignment 1 - Linked Lists          **
**              LinkedList.h                 **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

class LinkedList
{

public:
	LinkedList();
	~LinkedList();
	void add(string line);
	void deleteNode(int nodenum);
	string getValue(int nodenum);
	void insertAtIndex(int index, string nLine);
	friend ostream& operator<<(ostream& output, LinkedList& list);
	int getNumLines();

private:
	Node *first;
	int totalines;

};