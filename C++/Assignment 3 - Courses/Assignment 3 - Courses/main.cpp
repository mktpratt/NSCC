/*    Assignment 3 - Courses   **
**          main.cpp           **
**    Written by Mike Pratt    **
**       NSCC PROG 2100        */

#include "student.h"
#include "studentio.h"
#include <stdio.h>
#include <iostream>
#include <boost/regex.hpp>

using namespace std;

bool repeat();

// Begin method main
int main(){

	bool goAgain = true;
	// IO Class
	StudentIO sIO;

	// Begin while loop
	while (goAgain)
	{
		// Get name
		string name = sIO.getName();
		// Get courses
		string * courses = sIO.getCourses();
		// Determine number of courses entered
		int numCourses = sIO.getNumberOfCourses();
		// Create student (object)
		Student s;
		// Set values of name, courses, and number of courses
		s.setValues(name, courses, numCourses);
		// Print out the student and courses
		cout << s;
		// Get a second name
		string s2Name = (sIO.getName());

		// Create another student object
		Student s2;
		// Copy the first student to the second student
		s2 = s;

		// Clear the values of first student
		s.clearValues();

		// Print out the student and courses
		cout << s;
		// Set the second student's name
		s2.setName(s2Name);
		// Print the second student
		cout << s2;

		// Determine if user would like to run again
		goAgain = repeat();

	}// End while loop

	cout << endl << "The program will now close. ";
	system("PAUSE");

	return 0;
} // End method main

// Begin method repeat
bool repeat()
{
	// Create RegEx for user's response
	boost::regex yesNoRegex("([Yy|Nn])");
	// User's response
	string response = "";

	// Repeat until the user's response matches the RegEx
	while (!(boost::regex_match(response, yesNoRegex)))
	{
		cout << "Would you like to enter another set? (Y/N) : ";
		// Read in the line
		getline(cin, response);
		// Clear the input
		cin.clear();
	} // End while loop

	// Return response
	return response == "y" || response == "Y";
}// End method repeat