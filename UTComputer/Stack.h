#pragma once
#include <stack>
#include <vector>
#include "Literal.h"
#include "StackMemento.h"

// TODO voir comment utiliser la seconde partie du template de stack
// utilisation du pattern adapteur d'objet

class Stack {
	std::vector<ILiteral*> stack;
public:
	bool empty() const { return stack.empty(); }
	size_t size() const { return stack.size(); }
	ILiteral* top() { return stack.back(); }
	const ILiteral* top() const { return stack.back(); }
	void push(ILiteral* val) { return stack.push_back(val); }
	void pop() { stack.pop_back(); }

	// deep copy constructor
	Stack() : stack() {}
	Stack(const Stack& s);
	~Stack();

	std::vector<ILiteral*>::const_reverse_iterator begin() const { return stack.crbegin(); }
	std::vector<ILiteral*>::const_reverse_iterator end() const { return stack.crend(); }

	StackMemento* createMemento() { StackMemento* sm = new StackMemento(); sm->setState(stack); return sm; }
	void setMemento(StackMemento* m); // deep copy
};

