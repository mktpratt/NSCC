/*    Assignment 3 - Courses   **
**         studentIO.h         **
**    Written by Mike Pratt    **
**       NSCC PROG 2100        */

#ifndef STUDENTIO_H //if not defined
#define STUDENTIO_H

#include <boost/regex.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

class StudentIO {

private:
	// Number of courses user enters
	int numberOfCoursesEntered;

public:
	// Default constructor
	StudentIO();
	// Get student name
	string getName();
	// Get the student's courses
	string* getCourses();
	// Int for amount of courses
	int getNumberOfCourses();

	// RegEx for student's name
	bool isValidStudentName(const string &studentName);
	// RegEx for valid course name
	bool isValidCourse(const string &courseName);


};

#endif