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
	Stack s;
	std::string rpn = "2$3/4 4$4/3 *";
	
	Controller c(s);
	c.command(rpn);
	
	system("pause");
	return 0;
}