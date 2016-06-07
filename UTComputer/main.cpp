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

#include "Stack.h"
#include "Controller.h"

int main() {	
	Stack s;
	std::string rpn = "2 2 * 3 + UNDO REDO UNDO";
	
	Controller::instance().command(rpn);
	
	system("pause");
	return 0;
}