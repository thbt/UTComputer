#pragma once

#include "Literal.h"
#include "Stack.h"

class IOperator : public IOperand {
	std::string symbol;
	const unsigned int arity;
public:
	IOperator(std::string s, unsigned int a) : symbol(s), arity(a) {}
	string toString() const { return symbol; }
	virtual void interpret(Stack* s) = 0;
};

class PlusOp : public IOperator {
public:
	PlusOp(IOperand* l, IOperand* r) : IOperator("+",2) {}
	void interpret(Stack* s);
};