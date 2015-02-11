/* Assignment 2 - Rational Number Calculator **
**               Source.cpp                  **
**         Written by Mike Pratt             **
**            NSCC PROG 2100                 */

#include "Rational.h"
#include <string>
using std::cout;
using std::endl;

void printNumbers(Rational &num1, Rational &num2){

	// Print out addition, subtraction, multiplication and division
	Rational num3;
	num3 = num1 + num2;
	cout << num1 << " + " << num2 << " = ";
	cout << num3 << endl;

	num3 = num1 - num2;
	cout << num1 << " - " << num2 << " = ";
	cout << num3 << endl;

	num3 = num1 * num2;
	cout << num1 << " * " << num2 << " = ";
	cout << num3 << endl;

	num3 = num1 / num2;
	cout << num1 << " / " << num2 << " = ";
	cout << num3 << endl;

	// Comparison tests
	if (num1 > num2){
		cout << num1 << " == " << num2 << " = FALSE\n";
		cout << num1 << " > " << num2 << " = TRUE\n";
		cout << num1 << " < " << num2 << " = FALSE\n";
	}
	else if (num1 > num2) {
		cout << num1 << " == " << num2 << " = FALSE\n";
		cout << num1 << " > " << num2 << " = FALSE\n";
		cout << num1 << " < " << num2 << " = TRUE\n";
	}
	else if (num1 == num2) {
		cout << num1 << " == " << num2 << " = TRUE\n";
		cout << num1 << " > " << num2 << " = FALSE\n";
		cout << num1 << " < " << num2 << " = FALSE\n";
	}
}

// Check if user wants to enter more numbers
bool isValidResponse(string response){

	if (response.length() > 1){
		return false;
	}

	// Check if either y/Y/n/N
	if (!(int(response[0]) == 121 || int(response[0]) == 89
		|| int(response[0]) == 78 || int(response[0]) == 110)){
		return false;
	}

	return true;
};

// Ask user if they'd like to go again
bool anotherSet(){

	string response = "";

	// Prompt for Y/N
	do{
		cout << "Would you like to run another test? (Y/N): ";
		getline(cin, response);
		// Check for ctrl + z
		if (cin.eof() == 1) {
			cin.clear();
		}
	} while (!isValidResponse(response));

	return(response == "Y" || response == "y");
};



int main(){

	cout << "Welcome to Mike's Rational Number Calculator!" << endl;
	cout << "Simply enter a rational number (Ex. 5 1/2 or 2/-3) and press Enter." << endl;
	cout << "You will then be prompted to enter a second rational number. Once completed, \nthe calculator will handle the rest!" << endl << endl;
	system("PAUSE");
	cout << endl;

	bool goAgain = true;

	while (goAgain){
		Rational num1;
		Rational num2;

		cout << "Enter the first rational number: ";
		cin >> num1;
		cout << "Enter a second rational number: ";
		cin >> num2;
		cout << endl << endl;

		printNumbers(num1, num2);

		cout << endl << endl;

		goAgain = anotherSet();
	}
	cout << endl << "Thanks for using my calculator! The program will now close." << endl;
	system("PAUSE");

	return 0;
}