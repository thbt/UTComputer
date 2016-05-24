#pragma once
#include <stack>
#include <vector>
#include "Literal.h"

// TODO voir comment utiliser la seconde partie du template de stack
// utilisation du pattern adapteur d'objet
// utilisation du pattern singleton
class Stack {
	std::vector<ILiteral*> stack;
public:
	bool empty() const { return stack.empty(); }
	size_t size() const { return stack.size(); }
	ILiteral* top() { return stack.back(); }
	const ILiteral* top() const { return stack.back(); }
	void push(ILiteral* val) { return stack.push_back(val); }
	void pop() { stack.pop_back(); }

	std::vector<ILiteral*>::const_reverse_iterator begin() const { return stack.crbegin(); }
	std::vector<ILiteral*>::const_reverse_iterator end() const { return stack.crend(); }
};