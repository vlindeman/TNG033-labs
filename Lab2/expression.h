/*************************
* Class Expression       *
* TNG033: Lab 2          *
**************************/

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>

const double EPSILON = 1.0e-5;


class Expression
{
public:
	

	// Virtual Destructor 
	virtual ~Expression() = default;

	// Function to test whether a given value x is a root of the function f.
	bool isRoot(double x) const;

	// Pure virtual clone fuction 
	virtual Expression * clone() const = 0;

	// Evaluates an Expression for a value, returns a double (Pure virtual)
	virtual double operator()(const double d) const = 0;

	// Display an Expression
	friend std::ostream& operator<<(std::ostream &os, const Expression &E);
	
protected:

	virtual void display(std::ostream& os) const = 0;

};


#endif
