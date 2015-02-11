/* Assignment 2 - Rational Number Calculator **
**             Rational.cpp                  **
**         Written by Mike Pratt             **
**            NSCC PROG 2100                 */

#include "Rational.h"

using std::string;
using std::stoi;
using std::vector;
using std::size_t;

// After discussing with several classmates, the boost library seems to
// be the most effective library to accomplish our task with RegEx.
using boost::regex;
using boost::regex_match;


// Default constructor
Rational::Rational()
{
	this->numerator = 0;
	this->denominator = 1;
}

// Single digit/string constructor
Rational::Rational(string rNumber)
{
	// Single digit (+/-)
	regex f("-?\\d+");
	if (regex_match(rNumber, f)) {
		wholeNumberConstructor(rNumber);
	}
	else {
		mixedConstructor(rNumber);
	}
}

// Create rational fraction from two integer entry (Num and denom)
Rational::Rational(int numer, int denom) : numerator(numer), denominator(denom)
{
	if (this->numerator == 0 || denom == 0) {
		this->numerator = 0;
		this->denominator = 1;
	}
	// Reduce fractions and normalize +/- fractions
	normalize(this->numerator, this->denominator);
};

// Create a rational number from single digit (Only numerator, denom set to 1)
void Rational::wholeNumberConstructor(string &rNumber)
{
	this->numerator = stoi(rNumber); // convert to int
	this->denominator = 1;
}

// Create fraction from mixed string (Ex. 2 1/2)
void Rational::mixedConstructor(string &rNumber)
{
	// Create character array to hold string
	char s[50];
	// Copy the string to the array
	strncpy(s, rNumber.c_str(), sizeof(s));
	// Create array to hold expressions
	vector<string> expression;
	// Create pointer to get current tokenized value
	const char* p;
	// Each call will grab a p
	p = strtok(s, " /");

	while (p != NULL)
	{
		expression.push_back(p);
		p = strtok(NULL, " /");
	}

	// Check for a space (Mixed number)
	size_t spacePos = rNumber.find(" ");
	if (spacePos == std::string::npos) {
		// Standard fraction
		this->numerator = stoi(expression[0]);
		this->denominator = stoi(expression[1]);
	}
	else {
		// Mixed fraction
		int eWhole = stoi(expression[0]);
		int eNumer = stoi(expression[1]);
		int eDenom = stoi(expression[2]);

		if (eWhole < 0) {
			eNumer *= -1;
		}
		this->numerator = eWhole * eDenom + eNumer;
		this->denominator = eDenom;
	}
}

// Get Greatest Common Denominator
int Rational::getGCD(int num1, int num2)
{

	/* Using Euclid's Algorithm
	Source: http://en.wikipedia.org/wiki/Greatest_common_divisor
	To compute gcd(48,18), divide 48 by 18 to get a quotient of 2
	and a remainder of 12. Then divide 18 by 12 to get a quotient of 1
	and a remainder of 6. Then divide 12 by 6 to get a remainder of 0,
	which means that 6 is the gcd. */

	// Check for division by 0
	if (num1 == 0 && num2 == 0){
		return 1;
	}
	else if (num2 == 0){
		return num1;
	}

	// Remove any negative signs
	num1 = abs(num1);
	num2 = abs(num2);

	// Int to hold temporary int value
	int tempNum;

	// Check if num2 < num 1
	if (num2 < num1) {
		// Swap them if num2 < num1 
		tempNum = num1;
		num1 = num2;
		num2 = tempNum;
	}

	// Create int for any remainder
	int remainder = 0;
	// Find remainder
	remainder = num1 % num2;

	// Try and find more remainders by reducing
	while (remainder != 0) {
		remainder = num1 % num2;
		num1 = num2;
		num2 = remainder;
	}

	return num1;
}

// Normalize the number (Ex. 5/-10 = -1/2)
void Rational::normalize(int &numer, int &denom)
{
	// Create gcd integer
	int gcd = getGCD(numer, denom);

	// Check for division by 0
	if (gcd != 0){
		numer /= gcd;
		denom /= gcd;
	}

	// Set to 0/1 if numerator is 0
	if (numer == 0 || denom == 0)
	{
		numer = 0;
		denom = 1;
	}
	else
	{
		// Normalize signs (Ex. 1/-1 = -1/1)
		if (numer > 0 && denom < 0 || numer < 0 && denom < 0) {  // switch signs
			numer = -numer;
			denom = -denom;
		}
	}


}

// return the rNum as string
string Rational::toString()
{

	std::stringstream ss;
	string x, y;
	// Pass numerator to stringstream
	ss << this->numerator;
	// Get numerator from stringstream
	ss >> x;
	// Clear buffer
	ss.clear();
	// Pass denominator to stringstream
	ss << this->denominator;
	// Get denominator from stringstream
	ss >> y;
	// Clear buffer
	ss.clear();
	return(x + "/" + y);

}

// Overload + operator
Rational Rational::operator+ (const Rational &num2)
{
	int num3Numer = (this->numerator * num2.denominator) + (this->denominator * num2.numerator);
	int num3Denom = (this->denominator * num2.denominator);
	normalize(num3Numer, num3Denom);
	Rational num3(num3Numer, num3Denom);
	return num3;
}

// Overload - operator
Rational Rational::operator- (const Rational &num2)
{

	int num3Numer = (this->numerator * num2.denominator) - (this->denominator * num2.numerator);
	int num3Denom = (this->denominator * num2.denominator);
	normalize(num3Numer, num3Denom);
	Rational num3(num3Numer, num3Denom);
	return  num3;
}

// Overload * operator
Rational Rational::operator* (const Rational &num2)
{
	int num3Numer = (this->numerator * num2.numerator);
	int num3Denom = (this->denominator * num2.denominator);
	normalize(num3Numer, num3Denom);
	Rational num3(num3Numer, num3Denom);
	return num3;
}

// Overload / operator
Rational Rational::operator/ (const Rational &num2)
{
	int num3Numer = this->numerator * num2.denominator;
	int num3Denom = this->denominator * num2.numerator;
	normalize(num3Numer, num3Denom);
	Rational num3(num3Numer, num3Denom);
	return num3;
}

// Overload > operator
bool Rational::operator> (Rational &num1){

	// cross multiplication
	int leftNum = this->numerator * num1.denominator;
	int rightNum = this->denominator * num1.numerator;
	return leftNum > rightNum;
}

// Overload < operator
bool Rational::operator< (Rational &num1){

	// Cross multiplication
	int leftNum = this->numerator * num1.denominator;
	int rightNum = this->denominator * num1.numerator;
	return leftNum < rightNum;
}

// Overload == operator
bool Rational::operator== (Rational &num1){

	int leftNum = this->numerator * num1.denominator; // cross multiplication
	int rightNum = this->denominator * num1.numerator;
	return leftNum == rightNum;
};

// Overload << operator
ostream& operator<< (ostream& output, Rational& rNum)
{
	char ch; // for some reason it would not run without this
	output << rNum.toString(); //right.numer << '/' << right.denom;
	return output;
};

// Overload >> operator
void operator>> (istream &input, Rational &num){

	string str;
	// Check if it matches proper format
	while (!num.isRational(str))
	{
		getline(input, str);
		// Get rid of possible spaces
		boost::algorithm::trim(str);

		// If it fails test, print message to user
		if (!num.isRational(str)) {
			cout << endl << "The number you entered is not a valid Rational or Mixed number." << endl;
			cout << "Enter a rational number: ";
			cin.clear();
		}
	}
	num = Rational(str);
}

// Check for matching rational number formats
bool Rational::isRational(const string &str)
{
	regex a("((-?[0-9])(\\d+)?)");
	regex b("(([1-9](\\d+)?\\s+)?(\\d+)/[1-9](\\d+)?)");
	regex c("(-([1-9](\\d+)?\\s+)?(\\d+)/[1-9](\\d+)?)");
	regex d("(-?(\\d+)/-?[1-9](\\d+)?)");

	if (str.length() > 8) {
		return false;
	}
	return regex_match(str, a) || regex_match(str, b) || regex_match(str, c) || regex_match(str, d);
}