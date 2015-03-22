/*  Assignment 3 - Sorting (EXTERNAL)  **
**              LinkedList.h           **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#include <iostream>
#include "ListNode.h"

using namespace std;

class LinkedList 
{
	public:	
		LinkedList();
		LinkedList(const LinkedList& orig);
		virtual ~LinkedList();	
		void append(string in);
		void remove(int index);
		void insert(string in, int index);
		int count();
		void showAllLines(string lprefix, int lindex);
		void showLines(string lprefix, int lindex, int lbegin, int lend);
		friend ostream& operator << (ostream& output, LinkedList& list);

	private:
		ListNode* _head;
};

#endif

