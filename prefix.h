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


#ifndef prefix_h
#define prefix_h

#include <stack>
#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>

using namespace std;


class Prefix {

	public:

	//overloaded friend operator telling the class how to print to console
	friend ostream& operator<<(ostream& output, const Prefix& toPrint);

	Prefix();										//default no-args constructor
	~Prefix();										//default destructor since all data is primitive
	void setPrefix(istream&);						//function sets the prefixExpression via istream
	int evaluatePrefix(void);						//functions evaluates prefixExpression, calls private function
	void outputAsPostfix(ostream& output);			//function to print the postfixExpression, calls private function

	private:

	int recCalculate(int index);					//private recursive function to calculate prefixExpression
	int outputAsPostfix(string substring);			//private recursive function to output postfixExpression
	string prefixExpression;						//string to hold prefixExpression
	string postfixExpression;						//string to hold postfixExpression
	stack<int>digits;								//stack to hold digits
	int numElements;								//variable to hold number of elements in prefixExpression

};

#endif // !CALCULATOR_H

