/*  Assignment 3 - Sorting (EXTERNAL)  **
**              ListNode.h             **
**         Written by Mike Pratt       **
**            and Aaron Ali            **
**            NSCC PROG 2400           */

#ifndef LISTNODE_H
#define	LISTNODE_H

#include <stdio.h>
#include <string>

using namespace std;

class ListNode 
{
	public:
		ListNode();
		ListNode(const ListNode& orig);
		virtual ~ListNode();
		string getLine();
		void setLine(std::string line);
		int getNumber();
		void setLineandNumber(string line, int number);
		ListNode* getNext();
		void setNext(ListNode* in);

	private:
		string _line;
		int _number;
		ListNode* _next;
};

#endif

