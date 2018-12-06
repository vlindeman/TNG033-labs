/*********************************************************
* Class Expression member functions implementation       *
* TNG033: Lab 2                                          *
**********************************************************/

#include "expression.h"
#include "math.h" //fabs

bool Expression::isRoot(double x) const {
	// Fabs = abs
	return (fabs((*this)(x)) < EPSILON);
}

std::ostream& operator<<(std::ostream &os, const Expression &E) {
	// Dynamic binding to call function display, related to the class of object E
	E.display(os);
	return os;
}
