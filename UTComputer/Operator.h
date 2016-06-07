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
	virtual void operator()(Stack* s) = 0; // Foncteur = classe-fonction
    unsigned int getArity() const { return arity; }

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
	void operator()(Stack* s);
};

class MinusOp : public IOperator {
public:
	MinusOp() : IOperator("-", 2) {}
	void operator()(Stack* s);
};

class MultiOp : public IOperator {
public:
	MultiOp() : IOperator("*", 2) {}
	void operator()(Stack* s);
};

class DivOp : public IOperator {
public:
	DivOp() : IOperator("/", 2) {}
	void operator()(Stack* s);
};

class DivEntOp : public IOperator {
public:
	DivEntOp() : IOperator("DIV", 2) {}
	void operator()(Stack* s);
};

class ModulOp : public IOperator {
public:
	ModulOp() : IOperator("MOD", 2) {}
	void operator()(Stack* s);
};

class NegOp : public IOperator {
public:
	NegOp() : IOperator("NEG", 1) {}
	void operator()(Stack* s);
};

class NumOp : public IOperator {
public:
	NumOp() : IOperator("NUM", 1) {}
	void operator()(Stack* s);

};

class DenOp : public IOperator {
public:
	DenOp() : IOperator("DEN", 1) {}
	void operator()(Stack* s);

};

class $Op : public IOperator {
public:
	$Op() : IOperator("$", 2) {}
	void operator()(Stack* s);
};

class ReOp : public IOperator{
public :
	ReOp() : IOperator("RE", 1) {}
	void operator()(Stack* s);
};

class ImOp : public IOperator{
public:
	ImOp() : IOperator("IM", 1) {}
	void operator()(Stack* s);
};

class DupOp : public IOperator{
public:
	DupOp() : IOperator("DUP", 1) {}
	void operator()(Stack* s);
};

class DropOp : public IOperator{
public:
	DropOp() : IOperator("DROP", 1) {}
	void operator()(Stack* s);
};

class SwapOp : public IOperator {
public:
	SwapOp() : IOperator("SWAP", 1) {}
	void operator()(Stack* s);
};

class ClearOp : public IOperator {
public:
	ClearOp() : IOperator("CLEAR", 0) {}
	void operator()(Stack* s);
};

class EqualOp : public IOperator {
public:
	EqualOp() : IOperator("=", 2) {}
	void operator()(Stack* s);
};

class DifferentOp : public IOperator {
public:
	DifferentOp() : IOperator("!=", 2) {}
	void operator()(Stack* s);
};

class InfEqOp : public IOperator {
public:
	InfEqOp() : IOperator("<=", 2) {}
	void operator()(Stack* s);
};

class InfOp : public IOperator {
public:
	InfOp() : IOperator("<", 2){}
	void operator()(Stack* s);
};

class SupOp : public IOperator {
public:
	SupOp() : IOperator(">", 2){}
	void operator()(Stack* s);
};

class SupEqOp : public IOperator {
public:
	SupEqOp() : IOperator("=>", 2){}
	void operator()(Stack* s);
};

class AndOp : public IOperator {
public:
	AndOp() : IOperator("AND", 2){}
	void operator()(Stack* s);
};

class OrOp : public IOperator {
public:
	OrOp() : IOperator("OR", 2){}
	void operator()(Stack* s);
};

class NotOp : public IOperator {
public:
	NotOp() : IOperator("NOT", 1){}
	void operator()(Stack* s);
};

class UndoOp : public IOperator {
public:
	UndoOp() : IOperator("UNDO", 0) {}
	void operator()(Stack* s);
};

class RedoOp : public IOperator {
public:
	RedoOp() : IOperator("REDO", 0) {}
	void operator()(Stack* s);
};


class EvalOp : public IOperator {
public:
	EvalOp() : IOperator("EVAL", 1) {}
	void operator()(Stack* s);
};
