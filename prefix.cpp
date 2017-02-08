/*-------------------------------------------------------------------------------------------------------------------------------

	Author:			Destiny Boyer
	Professor:		Rob Nash
	Class:			CSS342
	Assignment:		Recursion
	Date:			11/14/2016

	Class takes in prefix expressions (represented as strings), and calculates an answer to the expression using recursion.
	Stacks from the STL are used in the recursive calculation function to pop and push digits and answer, the last digit
	left on the stack is the answer to the prefix expression. This class also uses recursion to take a prefix expression,
	and translate it in to a postfix expression. Default constructors and destructors are used since all data is primitive.


	Class Invariants:
		- all prefix expressions are valid
		- expressions can only be +, /, -, or *
		- numbers can only be one digit in size

-------------------------------------------------------------------------------------------------------------------------------*/

#include "prefix.h"

using namespace std;

/*-------------------------------------------------------------------------------------------------

	Overloaded output operator for an outstream. First parameter is the output stream, second is
	the object to be printed. Prints the prefixExpression associated with second parameter
	and returns the output stream.

	PRECONDITIONS:
		- toPrint is an initialized object

	POSTCONDITIONS:
		- prints the prefixExpression of toPrint to the output stream

-------------------------------------------------------------------------------------------------*/

ostream& operator<<(ostream& output, const Prefix& toPrint) {
	output << toPrint.prefixExpression;	//prints the prefixExpression of toPrint
	return output;						//returns the output stream
};

/*-------------------------------------------------------------------------------------------------

	Default no-args constructor. Creates a Prefix object and sets numElements = 0. Initializes
	prefixExpression and postfixExpression to empty strings.

-------------------------------------------------------------------------------------------------*/

Prefix::Prefix() {
	numElements = 0;
	prefixExpression = "";
	postfixExpression = "";
};

/*-------------------------------------------------------------------------------------------------

	Default destructor -- appropriate because all data is primitive and no memory is
	dynamically allocated.

-------------------------------------------------------------------------------------------------*/

Prefix::~Prefix() {

};

/*-------------------------------------------------------------------------------------------------

	Function takes in an istream and uses it to set the prefixExpression. Sets numElements
	equal to the length of the prefixExpression.

	PRECONDITIONS:
		- inFile is a valid istream

	POSTCONDITIONS:
		- sets the prefixExpression to a string read from inFile
		- sets numElements equal to the length of prefixExpression

-------------------------------------------------------------------------------------------------*/

void Prefix::setPrefix(istream& inFile) {
	inFile >> prefixExpression;					//sets the prefixExpression equal to a string
												//read from inFile

	numElements = prefixExpression.length();	//sets numElements equal to the length of
												//prefixExpression
};

/*-------------------------------------------------------------------------------------------------

	Facade function that calls recCalculate to recursively calculate the answer to the calling
	object's prefixExpression.

	PRECONDITIONS:
		- prefixExpression must have previously been initialized with setPrefix()
		- prefixExpression is a valid
		- operators are +, -, /, or *
		- each number in prefixExpression is only a single digit

	POSTCONDITIONS:
		- returns the answer to the prefixExpression

-------------------------------------------------------------------------------------------------*/

int Prefix::evaluatePrefix(void) {
	return recCalculate(0);	//calls recCalculate with a beginning index of 0
};

/*-------------------------------------------------------------------------------------------------

	Private recursive function called by evaluatePrefix() to calculate the answer to the
	expression of prefixExpression. Uses stacks to push and pop numbers for evaluation.
	Recursively calls itself by incrementing the index parameter until the index parameter is
	equal to numElements. Returns digits.top() which is equal to the answer of the expression
	when the index is equal to numElements (we have reached the end of the expression)

	PRECONDITIONS:
		- must be called by evaluatePrefix()
		- prefixExpression must have previously been initialized with setPrefix()
		- prefixExpression is a valid expression
		- operators are +, -, /, or *
		- each number in prefixExpression is only a single digit

	POSTCONDITIONS:
		- recursively calls itself while index < numElements
		- returns the digits.top(), which is the answer to the prefixExpression, when index
		  is equal to numElements (the end of the expression has been reached)

-------------------------------------------------------------------------------------------------*/

int Prefix::recCalculate(int index) {

	//base case, checks to see if the parameter index is
	//equal to the number of elements in the expression
	//if so, returns the answer
	if (index == numElements) {
		return digits.top();
	}

	//object to hold the current char in the expression
	//starts at the end of the expression and works toward
	//index 0
	int currentChar = prefixExpression[numElements - 1 - index];

	//checks to see if the currentChar is a digit, if so pushes it on
	//to the digit stack
	if (isdigit(currentChar)) {
		digits.push(currentChar - '0');

	} else {						//otherwise we know that the char is an
									//operator and that we need to perform
									//an operation


		int lhs = digits.top();		//holds the left-hand-side of the expression
									//equal to the top digit on the stack
		digits.pop();				//pops the top digit off the stack


		int rhs = digits.top();		//holds the right-hand-side of the expression
									//equal to the top digit on the stack
		digits.pop();				//pops the top digit off the stack

		int toPush;					//variable to hold the answer which
									//will eventually be pushed on to the stack

		//if statements to cycle through the operation to be performed
		//evaluates whether currentChar is equal to the char for the
		//operation. Once it finds the correct operation it sets toPush
		//equal to the evaluation of lhs and rhs
		if (currentChar == '+') {
			toPush = lhs + rhs;
		} else if (currentChar == '-') {
			toPush = lhs - rhs;
		} else if (currentChar == '*') {
			toPush = lhs * rhs;
		} else {
			toPush = lhs / rhs;
		}

		digits.push(toPush);		//pushes toPush (the answer of the expression)
									//on to the stack
	}
	recCalculate(index + 1);		//recursive call incrementing the index
};

/*-------------------------------------------------------------------------------------------------

	Facade function. Takes in an ostream as a parameter. Calls the private recursive function
	outputAsPostfix(string) to build a postfix expression. Prints the postfixExpression to the
	ostream.

	PRECONDITIONS:
		- prefixExpression must have previously been initialized with setPrefix()
		- prefixExpression is a valid expression
		- operators are +, -, /, or *
		- each number in prefixExpression is only a single digit

	POSTCONDITIONS:
		- prints postfixExpression to the ostream

-------------------------------------------------------------------------------------------------*/

void Prefix::outputAsPostfix(ostream& out) {
	outputAsPostfix(prefixExpression);		//calls private recursive helper function
	out << this->postfixExpression;			//prints postfixExpression to the ostream
};

/*-------------------------------------------------------------------------------------------------

	Recursive function that takes in a prefixExpression as a string and uses recursive calls
	passing substrings of the original parameter in order to build a postfix expression.

	PRECONDITIONS:
		- prefixExpression must have previously been initialized with setPrefix()
		- prefixExpression is a valid expression
		- operators are +, -, /, or *
		- each number in prefixExpression is only a single digit

	POSTCONDITIONS:
		- builds a postfix expression in the form of a string and sets the variable
		  postfixExpression equal to this

-------------------------------------------------------------------------------------------------*/

int Prefix::outputAsPostfix(string prefix) {

	char currentChar = prefix[0];				//variable to hold current char
	bool isDigit = isdigit(currentChar);	//evaluates whether the currentChar is a digit

	//if the temp object is a digit we add it to our postfixExpression string
	//expression and return 1
	if (isDigit) {
		postfixExpression += currentChar;
		return 1;
	}

	//recursive call, inputting a substring of prefix
	//it will continue until we reach a number, returns 1
	int nextChar = outputAsPostfix(prefix.substr(1));

	//recursive call using the index of nextChar (the first number in the series)
	//plus one as the index that we use when passing in a substring
	//(once we find one number in the expression, this gives us the next number)
	int nextChar2 = outputAsPostfix(prefix.substr(nextChar + 1));

	//if the temp object is not a digit we know that it must be an operator and so
	//we add it after the digits already in postfixExpression
	postfixExpression += currentChar;

	//return the sum of nextChar and nextChar2 + 1,
	//this will always be out of bounds of the length
	//of the string and is our ending base case
	return nextChar + nextChar2 + 1;

};


