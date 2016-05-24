#pragma once

#include "Literal.h"
#include "Stack.h"

// pattern visiteur
class IOperator : public IOperand {
	std::string symbol;
	const unsigned int arity;
public:
	IOperator(std::string s, unsigned int a) : symbol(s), arity(a) {}
	std::string toString() const { return symbol; }
	virtual void interpret(Stack* s) = 0;

	/*
	// liste des types litteraux concrets !
	virtual void visitIntegerLiteral(IntegerLiteral* l) = 0;
	virtual void visitRealLiteral(RealLiteral* l) = 0;
	virtual void visitRationalLiteral(RationalLiteral* l) = 0;
	virtual void visitComplexLiteral(ComplexLiteral* l) = 0;
	*/
};

class PlusOp : public IOperator {
public:
	PlusOp() : IOperator("+", 2) {}
	void interpret(Stack* s);

	//void visitIntegerLiteral(IntegerLiteral* l);
};