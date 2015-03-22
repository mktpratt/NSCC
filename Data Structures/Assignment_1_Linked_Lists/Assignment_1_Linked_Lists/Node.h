/*      Assignment 1 - Linked Lists          **
**                 Node.h                    **
**         Written by Mike Pratt             **
**            NSCC PROG 2400                 */

#pragma once
#include <string>

using namespace std;

class Node
{
public:
	string line;
	Node *next;

	Node();
	~Node();
};