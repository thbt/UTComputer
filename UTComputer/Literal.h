#pragma once
#include <iostream>
#include <string>

using namespace std;

// TODO: destructor where its needed

class IOperand {
public:
	virtual string toString() const = 0;
};

class ILiteral : public IOperand {};

enum NumberType { integer, rational, real, complex };

class NumberLiteral : public ILiteral {
	double reNum;
	double reDen;
	double imNum;
	double imDen;

	NumberType type;
public:
	NumberLiteral(double rn, NumberType t = integer, double rd = 1, double in = 0, double id = 1)
		: reNum(rn), reDen(rd), imNum(in), imDen(id), type(t) {}


	string toString() const;
};


/*
class INumberLiteral : public ILiteral {};

class IntegerLiteral : public INumberLiteral {
	int value;
public:
	IntegerLiteral(int v) : value(v) {}

	int getValue() const { return value; }

	string toString() const { return to_string(value); }
};

// TODO simplificateur
class RationalLiteral : public INumberLiteral {
	IntegerLiteral numerator;
	IntegerLiteral denominator;
public:
	RationalLiteral(int n, int d) : numerator(IntegerLiteral(n)), denominator(IntegerLiteral(d)) {}
	RationalLiteral(IntegerLiteral n = IntegerLiteral(0), IntegerLiteral d = IntegerLiteral(1)) : numerator(n), denominator(d) {}

	ILiteral* eval() { return this; }

	string toString() const { return numerator.toString() + "/" + denominator.toString(); }
};

// TODO : utiliser un double et pas se faire chier ?
// TODO : Exception pour 0.0
class RealLiteral : public INumberLiteral {
	IntegerLiteral integer;
	IntegerLiteral mantissa;
public:
	RealLiteral(int i, int m = 0) : integer(IntegerLiteral(i)), mantissa(IntegerLiteral(m)) {}
	RealLiteral(IntegerLiteral i = IntegerLiteral(0), IntegerLiteral m = IntegerLiteral(0)) : integer(i), mantissa(m) {}

	ILiteral* eval() { return this; }

	string toString() const { return integer.toString() + "." + mantissa.toString(); }
};

class ComplexLiteral : public ILiteral {
	INumberLiteral* real;
	INumberLiteral* imaginary;
public:
	ComplexLiteral(INumberLiteral* r = new IntegerLiteral(0), INumberLiteral* i = new IntegerLiteral(0)) : real(r), imaginary(i) {}

	ILiteral* eval() { return this; }

	string toString() const { return real->toString() + "$" + imaginary->toString(); }
};
*/

/*
class AtomLiteral : public IOperand {
	string name;
	IOperand* identity;
public:
	AtomLiteral(string n, ILiteral* i) : name(n), identity(i) {}

	IOperand* eval() { return identity; }

	string toString() const { return name; }
};
*/


class ExpressionLiteral : public ILiteral {
	string expression;
public:
	ExpressionLiteral(string e) : expression(e) {}
};

class ProgramLiteral : public ILiteral {
	string program;
public:
	ProgramLiteral(string p) : program(p) {}
};

