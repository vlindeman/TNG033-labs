/*************************
* Class Polynomial       *
* TNG033: Lab 2          *
**************************/

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>

#include "expression.h"


class Polynomial : public Expression
{
public:
	// Constructor that creates a polynomial from an array of doubles
	Polynomial(int n, double arr[]);

	// Conversion constructor, double to Polynomial 
	Polynomial(const double d);

	// Copy constructor
	Polynomial(const Polynomial& pol); 

	//Destructor 
	~Polynomial();

	// Polynomial clone, instances can create copies of themselves
	Polynomial* clone() const override;
	
	//Assignment operator
	Polynomial& operator=(const Polynomial &pol);

	// Addition operators 
	Polynomial operator+(const Polynomial &pol)const;
	Polynomial operator+(const double &d)const;
	friend Polynomial operator+(const double d, const Polynomial& pol);

	//friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);

	// Operator() returns the value of the polynomial as a double with given value d for var x
	double operator()(const double d)const override;

	// Used to access the value of a polynomial’s coefficient
	double operator[](const int a) const;
	double& operator[](int a);

protected:
	int degree; // Degree of the polynomial 
	double *coef; // coefficients for the polynomial array 
	void display(std::ostream& os) const override;

};


#endif
