/*********************************************************
* Class Polynomial member functions implementation       *
* TNG033: Lab 2                                          *
**********************************************************/

#include "polynomial.h"
#include "math.h"
#include <iomanip>
#include <iostream>

// Constructor that creates a polynomial from an array of doubles
Polynomial::Polynomial(int n, double arr[])
	: degree{n}
{
	coef = new double[n + 1];

	for (int i = 0; i <= n; i++) {
		coef[i] = arr[i];
	}
}

// Conversion constructor, double to Polynomial 
Polynomial::Polynomial(const double d)
	: degree{0}
{
	coef = new double[1];
	coef[0] = d;
}

// Copy constructor
Polynomial::Polynomial(const Polynomial& pol) 
	: degree{pol.degree} 
{
	coef = new double[degree + 1];

	for (int i = 0; i <= pol.degree; i++) {
		coef[i] = pol.coef[i];
	}
}

//Destructor 
Polynomial::~Polynomial() {
	delete[] coef;
	degree = 0;
}

//Polynomial clonable = instances can create copies of themselves
Polynomial * Polynomial::clone() const {
	Polynomial * pclone = new Polynomial(*this);
	return pclone;
}

//Assignment operator
Polynomial& Polynomial::operator=(const Polynomial &pol) {
	if (!(&pol == this)) { // if not self-assignment 
		delete[] coef;
		coef = new double[pol.degree + 1];
		degree = pol.degree;

		for (int i = 0; i <= degree; i++) {
			coef[i] = pol.coef[i];
		}
	}
	return (*this);
}

// Operator() returns the value of the polynomial as a double with given value d for var x
double Polynomial::operator()(const double d) const {
	double result = 0.0;

	for (int i = 0; i <= degree; i++) {
		if (i == 0)
			result += coef[i];
		else {
			result += (coef[i] * pow(d, i));
		}
	}

	return result;
}

// Addition of two polynomials 
Polynomial Polynomial::operator+(const Polynomial &pol) const {

	Polynomial result(*this);
	// max av pol deg
	for (int i = 0; i <= pol.degree; i++) {
		result.coef[i] += pol.coef[i];
	}

	return result;
}

// Addition of a polynomial with a real (double) value 𝑑
Polynomial Polynomial::operator+(const double &d) const {
	coef[0] += d;
	return *this;
}

// Addition of a polynomial with a real (double) value d
Polynomial operator+(const double d, const Polynomial& pol) {
	Polynomial p = pol;
	p.coef[0] += d;
	return p;
}

//  access the value of a polynomial’s coefficient (const)
double Polynomial::operator[](const int a) const {
	return coef[a];
}

//  access the value of a polynomial’s coefficient (non-const)
double& Polynomial::operator[](int a) {
	return coef[a];
}

//function to display a polynomial
void Polynomial::display(std::ostream& os) const {

	if (degree > 0)
		os << std::setprecision(2) << std::fixed << coef[0] << " + ";
	else
		os << std::setprecision(2) << std::fixed << coef[0];

	for (int i = 1; i <= degree; i++) {

		//display if coef isn't zero 
		if (coef[i] != 0) {
			os << std::setprecision(2) << coef[i] << " * X^" << i;
		}

		//if there are still something to display
		if (i < degree && coef[i + 1] != 0) {
			os << " + ";
		}

	}
}
