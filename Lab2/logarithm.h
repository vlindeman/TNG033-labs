/*************************
* Class Logarithm        *
* TNG033: Lab 2          *
**************************/


#ifndef LOGARITHM_H
#define LOGARITHM_H

#include <iostream>

#include "expression.h"

using namespace std;

class Logarithm : public Expression
{
public:
	// Default constructor
	Logarithm();
	
	// Constructor that creates the logarithmic expression 𝑐1+𝑐2×𝑙𝑜𝑔𝑏(𝐸). 
	Logarithm(const Expression &E, const double c1, const double c2, const int b);

	// copy constructor
	Logarithm(const Logarithm &L);

	// Destructor
	~Logarithm();

	// returns y = f(x) when given x
	double operator()(const double x) const override;

	// An assignment operator
	Logarithm& operator=(const Logarithm &L);
	
	// Clone: instances can create copies of themselves
	Logarithm* clone() const override;

protected:

	int base; // base of the log
	double a1, a2; // coefficients 
	Expression *exp; 

	void display(ostream &os) const override;

};

#endif
