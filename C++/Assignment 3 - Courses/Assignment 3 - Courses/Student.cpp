/*    Assignment 3 - Courses   **
**         Student.cpp         **
**    Written by Mike Pratt    **
**       NSCC PROG 2100        */

#include "Student.h"
#include <iostream>

using namespace std;

// Default constructor
Student::Student() {

	// Display that the default constructor is being fired
	cout << endl << "*** Default Constructor ***" << endl;

	this->studentName = "Blank Name";
	this->numCourses = 0;
	this->courses = NULL;

}

// Copy constructor
Student::Student(Student &otherStudent){

	// Display that the copy constructor is being fired
	cout << endl << "*** Copy Constructor ***" << endl;

	// Set the other student's name
	this->studentName = otherStudent.studentName;
	// Set the other student's number of courses
	this->numCourses = otherStudent.numCourses;
	// Create a new string array of courses
	this->courses = new std::string[otherStudent.numCourses];

	// Loop through to copy each class to other student
	for (int i = 0; i < otherStudent.numCourses; i++){
		this->courses[i] = otherStudent.courses[i];
	} // End for loop

}

// Destructor
Student::~Student(){

	// Display that the destructor is being fired
	cout << endl << "*** Destructor ***" << endl;

	// Check for NULL value
	if (this->courses != NULL){
		// Delete the array
		delete[] this->courses;
		// Set courses to NULL
		this->courses = NULL;
	} // End if
}

// Begin setValues method
void Student::setValues(const std::string & name, const std::string * courses, int numCourses){

	// Set name
	this->studentName = name;
	// Set courses
	this->numCourses = numCourses;
	// Copy the list of courses
	this->courses = new std::string[numCourses];

	for (int i = 0; i < numCourses; i++){
		this->courses[i] = courses[i];
	} // End for loop

} // End setValues method

// Begin toString method
std::string Student::toString(){

	std::string studentString = "";
	studentString += "\n\t\t\t NAME \n";
	studentString += "\t\t\t ---- \n";
	studentString += "\t\t\t " + this->studentName + "\n\n";

	// Add courses header if the student has classes
	if (this->numCourses > 0){
		studentString += "\t\t\t COURSES \n";
		studentString += "\t\t\t ------- \n";
	} // End if

	// Add the courses
	for (int i = 0; i < this->numCourses; i++){
		studentString += "\t\t\t " + this->courses[i] + "\n\n";
	} // End for loop

	// Return string
	return studentString;

} // End toString method

// Overload << operator
std::ostream& operator<< (std::ostream& output, Student& student)
{
	// Load ostream
	output << student.toString();
	// Return the ostream
	return output;
} // End overload << operator method

// Overload = operator
Student& Student::operator= (Student otherStudent){

	/// Set the name of other student
	this->studentName = otherStudent.studentName;
	// Set the array size
	this->numCourses = otherStudent.numCourses;
	// Delete the current student's courses
	delete[] this->courses;
	// Create new array (dynamic)
	this->courses = new std::string[otherStudent.numCourses];

	// Add the courses
	for (int i = 0; i < otherStudent.numCourses; i++) {
		this->courses[i] = otherStudent.courses[i];
	} // End for loop

	return *this;
} // End overload = operator method

// Clear all of the values
void Student::clearValues(){

	// Check if course array is NOT empty and delete it
	if (this->courses != NULL){
		delete[] this->courses;
		this->courses = NULL;
	} // End if

	// Reset the student data
	this->courses = 0;
	this->studentName = "Blank Name";
	this->numCourses = 0;

} // End clearValues method