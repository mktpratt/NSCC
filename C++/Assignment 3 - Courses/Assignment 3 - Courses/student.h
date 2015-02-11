/*    Assignment 3 - Courses   **
**          student.h          **
**    Written by Mike Pratt    **
**       NSCC PROG 2100        */

#ifndef STUDENT_H //if not defined
#define STUDENT_H

#include <boost/regex.hpp>
#include <string>

using namespace std;

class Student {

private:
	// Students name
	string studentName;
	// Courses
	string * courses;
	// Number of courses
	int numCourses;

public:
	// Default constructor
	Student();
	// Destructor
	~Student();
	// Copy Constructor
	Student(Student &rStudent);

	// Set values
	void setValues(const string &name, const string* courses, int numCourses);
	// Reset all values
	void clearValues();
	// Set student name
	void setName(const string &name) {
		this->studentName = name;
	}

	// toString method
	string toString();
	// Overload the << operator
	friend ostream& operator<< (ostream& output, Student& student);

	// Getters
	// Get the number of courses
	int getNumCourses() {
		return this->numCourses;
	};
	// Get the student's name
	string getStudentName() {
		return this->studentName;
	};
	// Retrieve the courses array
	string* getCourses() {
		return this->courses;
	};
	// Equals Operator
	Student& operator= (Student rStudent);

};

#endif