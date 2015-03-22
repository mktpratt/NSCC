/*       Assignment 3 - Sorting        **
**               ListNode.h            **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

#ifndef LISTNODE_H
#define	LISTNODE_H

#include <stdio.h>

class ListNode 
{
	public:
		ListNode();
		ListNode(const ListNode& orig);
		virtual ~ListNode();	
		int getLine();
		void setLine(int value);
		ListNode* getNext();
		void setNext(ListNode* in);

	private:	
		int value;
		ListNode* next;
};

#endif

