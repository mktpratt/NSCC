/*       Assignment 3 - Sorting        **
**              LinkedList.h           **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#include <iostream>
#include "ListNode.h"

class LinkedList 
{
	public:
		LinkedList();
		LinkedList(const LinkedList& orig);
		virtual ~LinkedList();
		void Append(int in);
		LinkedList* Concat(LinkedList* firstList, int pivotValue, LinkedList* secondList);
		int ValueAt(int index);
		void Delete(int index);
		void Insert(int in, int index);
		int Count();

	private:
		ListNode* head;
};

#endif

