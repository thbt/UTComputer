#pragma once

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <stack>

#include "Stack.h"
#include "Operator.h"

class Controller {
	Controller();

	Stack stack;
	std::map<std::string, std::function<void(Stack* s)>> dispatcher;
	std::stack<StackMemento*> undoStack;
	std::stack<StackMemento*> redoStack;

public: 
	static Controller& instance();

	void command(const std::string& str);
	void execute(std::string op);

	void undo();
	void redo();
};