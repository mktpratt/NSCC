/*    Assignment 3 - Courses   **
**        StudentIO.cpp        **
**    Written by Mike Pratt    **
**       NSCC PROG 2100        */

#include "StudentIO.h"
using boost::algorithm::trim;
using boost::regex;
using boost::regex_match;

using namespace std;

// Default constructor
StudentIO::StudentIO(){
	this->numberOfCoursesEntered = 0;
} // End default constructor


// Begin method getNumberOfCourses
int StudentIO::getNumberOfCourses(){
	return this->numberOfCoursesEntered;
} // End method getNumberOfCourses

// Begin method getCourses
string* StudentIO::getCourses(){

	// Variable of char to get out of loop
	string doneVariable = "S";
	numberOfCoursesEntered = 0;
	string currentCourse = "";
	// Create the array of courses
	string* courses = new string[1];

	// Loop while the course entered isn't the quit command
	while (boost::to_upper_copy(currentCourse) != doneVariable)
	{
		// 
		currentCourse = "";

		// Loop while the entered course doesn't match RegEx desired
		while (!isValidCourse(currentCourse)) {

			// Ask user to enter a course
			cout << "Please enter a course for the student (Enter S to stop entry): " << endl;
			// Retrieve the value
			getline(cin, currentCourse);
			// Trim possible white space on course
			boost::algorithm::trim(currentCourse);

			// Display error message to user for invalid course
			if (!isValidCourse(currentCourse)) {
				cout << "You have entered an invalid course format. (Ex. Math 1100, or Math)" << endl; // print prompt
			} // End if

			// Display error message to user for no courses entered
			if (numberOfCoursesEntered == 0 && boost::to_upper_copy(currentCourse) == doneVariable){
				cout << "The student must have at least one class!" << endl;
				currentCourse = "";
			}// End if

		} // End while loop

		// Check to see if the course is valid, or if the user is escaping the sequence
		if (boost::to_upper_copy(currentCourse) != doneVariable) {
			numberOfCoursesEntered++;
			// Make a new array
			string* temp = new string[numberOfCoursesEntered];
			// Loop to replace the values
			for (int i = 0; i < numberOfCoursesEntered - 1; i++) {
				// Set the temp array equal to courses array
				temp[i] = courses[i];
			}
			// Delete courses array
			delete[] courses;
			// Assign the courses again
			courses = temp;
			// Add the course to the end of the array
			courses[numberOfCoursesEntered - 1] = currentCourse;
		} // End if

	} // End while loop

	return courses;

} // End method getCourses

// Begin method getName
string StudentIO::getName(){

	// String for student's name
	string name = "";

	while (!isValidStudentName(name)){
		// Ask user to enter a student's name
		cout << "Please enter a full student name (FirstName LastName): " << endl;
		// Read in the name
		getline(cin, name);
		// Trim possible white space off of name
		boost::algorithm::trim(name);

		// Display error message to user
		if (!isValidStudentName(name)){
			cout << "Invalid student name format! (FirstName LastName)" << endl;
		} // End if

	}// End while loop

	// Return the student's name
	return name;

}// End method getName

// Begin method isValidStudentName (RegEx test)
bool StudentIO::isValidStudentName(const string &studentName){
	// name regex
	boost::regex nameRegex("(^([A-Za-z ,.'-]+)( ([A-Za-z ,.'-]+))+$)");
	return boost::regex_match(studentName, nameRegex);
} // End method isValidStudentName

// Begin method isValidCourse (RegEx test)
bool StudentIO::isValidCourse(const string &courseName){

	// course regex
	boost::regex courseRegex("(^[A-Za-z|0-9|]+( [A-Za-z|0-9|]+)?$)");
	// return match or no match
	return boost::regex_match(courseName, courseRegex);
} // End method isValidCourse