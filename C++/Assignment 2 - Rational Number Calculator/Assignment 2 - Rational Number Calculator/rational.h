/* Assignment 2 - Rational Number Calculator **
**               Rational.h                  **
**         Written by Mike Pratt             **
**            NSCC PROG 2100                 */

#ifndef MYOWNMATH_H //if not defined
#define MYOWNMATH_H
#define _CRT_SECURE_NO_WARNINGS

#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;

// Rational Numbers
class Rational
{
public:

	// Default constructor
	Rational();
	// Two int constructor
	Rational(int numer, int denom);
	// Mixed number constructor
	Rational(string rationalNumber);

	// + operator overload
	Rational operator+ (const Rational &num2);
	// - operator overload
	Rational operator- (const Rational &num2);
	// * operator overload
	Rational operator* (const Rational &num2);
	// / operator overload
	Rational operator/ (const Rational &num2);
	// < operator overload
	bool operator< (Rational &num1);
	// > operator overload
	bool operator> (Rational &num1);
	// == operator overload
	bool operator== (Rational &num1);
	// Stream overloads
	friend void operator>> (istream &input, Rational &num);
	friend ostream& operator<< (ostream& output, Rational& num);

	void wholeNumberConstructor(string &rationalNumber);
	void mixedConstructor(string &rationalNumber);


private:

	// GCD
	int getGCD(int numer, int denom);
	// Normalize fraction (Reduce to lowest terms) 
	void normalize(int &numer, int &denom);
	// Output to string
	string toString();
	// Test against RegEx
	bool isRational(const string &str);
	// Check if string is a valid mixed number
	bool validString();

	int numerator;
	int denominator;
};


#endif