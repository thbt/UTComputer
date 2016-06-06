#pragma once

#include <string>
#include <functional>
#include <map>

#include "Stack.h"
#include "Operator.h"

class Controller {
	Stack& stack;
	std::map<std::string, std::function<void(Stack* s)>> dispatcher;
public: 
	Controller(Stack& s);
	void command(const std::string& str);
};