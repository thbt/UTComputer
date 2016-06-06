#include <string>
#include <iostream>
#include <istream>
#include <vector>
#include <ostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <map>
#include <functional> // for std::function

#include "Literal.h"
#include "Stack.h"
#include "Operator.h"
#include "OperatorException.h"
#include "LiteralFactory.h"

#include "Controller.h"

int main() {
	/*
	IntegerLiteral n1(0);
	RealLiteral n2(4.5);
	RationalLiteral n3(0,1);
	ComplexLiteral n4(new RealLiteral(0), new IntegerLiteral(0));
	IntegerLiteral n5(10);
	IntegerLiteral n6(5);
	ComplexLiteral n7(new RationalLiteral(0,1), new RationalLiteral(0,3));
	RationalLiteral n8(4, 2);
	*/
	
	Stack s;
	std::string rpn = "2 2 + 3 * 5 -";
	
	Controller c(s);
	c.command(rpn);
	
	system("pause");
	return 0;
}