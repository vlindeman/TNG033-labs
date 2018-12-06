/*********************************************************
* Class Logarithm member functions implementation        *
* TNG033: Lab 2                                          *
**********************************************************/

#include "logarithm.h"
#include "polynomial.h"

//  default constructor that creates the logarithm 𝑙𝑜𝑔2(𝑥)
Logarithm::Logarithm()
	: a1{ 0 }, a2{ 1 }, base{ 2 }
{
	double coeff[2] = { 0, 1 }; // 0 + 1*x, for polynomial 
	exp = new Polynomial(1, coeff);
}

// Constructor that creates the logarithmic expression 𝑐1+𝑐2×𝑙𝑜𝑔𝑏(𝐸). 
Logarithm::Logarithm(const Expression &E, const double c1, const double c2, const int b)
	: a1{ c1 }, a2{ c2 }, base{ b }
{
	exp = E.clone();
}

// Copy constructor 
Logarithm::Logarithm(const Logarithm &L)
	: a1{ L.a1 }, a2{ L.a2 }, base{ L.base }
{
	exp = L.exp->clone();
}

// Destructor
Logarithm::~Logarithm() {
	delete exp;
}

// returns y = f(x) when given x
double Logarithm::operator()(const double x) const {
	double result = 0.0, poly_result = 0.0;
	poly_result = exp->operator()(x);
	result = a1 + a2 * (log10(poly_result) / log10(base));
	return result;
}

//Assignment operator
Logarithm& Logarithm::operator=(const Logarithm &L) {
	base = L.base;
	a1 = L.a1;
	a2 = L.a2;
	delete exp;
	exp = L.exp->clone();
	
	return (*this);
}

Logarithm* Logarithm::clone() const {
	Logarithm *l = new Logarithm(*this);
	return l;
}

void Logarithm::display(ostream &os) const {

	// print if first coef is not 0
	if (a1 != 0) os << a1 << " + ";

	//print if second coef is not 0
	if (a2 != 0) {
		os << a2 << " * Logarithm_" << base << "( " << *exp << " )";
	}

}