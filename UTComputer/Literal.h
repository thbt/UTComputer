#pragma once
#include <iostream>
#include <string>

using namespace std;

// TODO: destructor where its needed

class IOperand {
public:
	virtual string toString() const = 0;
};

enum Type { INTEGER, RATIONAL, REAL, COMPLEX, EXPRESSION, PROGRAM };

class ILiteral : public IOperand {
	Type type;
public:
	ILiteral(Type t) : type(t) {}

	Type getType() const { return type; }

	virtual string toString() const = 0;
	//virtual void accept(IOperator&) = 0;
};

/*
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
*/

// TODO Pour l'instant ne sert a rien.. a supprimer ?
class INumberLiteral : public ILiteral {
public:
	INumberLiteral(Type t) : ILiteral(t) {}

	virtual string toString() const = 0;
	//virtual void accept(IOperator&) = 0;
};

class IntegerLiteral : public INumberLiteral {
	int value;
public:
	IntegerLiteral(int v) : INumberLiteral(INTEGER), value(v) {}

	int getValue() const { return value; }

	string toString() const { return to_string(value); }
	//void accept(IOperator& o) { o.visitIntegerLiteral(this); }
};

// TODO on conserve le fait que le numérateur soit une entier ou seulement un int ?
// TODO simplificateur
class RationalLiteral : public INumberLiteral {
	int numerator;
	int denominator;
public:
	RationalLiteral(int n, int d) : INumberLiteral(RATIONAL), numerator(n), denominator(d) {}
	string toString() const { return to_string(numerator) + "/" + to_string(denominator); }
};

// TODO : Exception pour 0.0
class RealLiteral : public INumberLiteral {
	double value;
public:
	RealLiteral(double v) : INumberLiteral(REAL), value(v) {}
	string toString() const { return to_string(value); }
};

class ComplexLiteral : public ILiteral {
	INumberLiteral* real;
	INumberLiteral* imaginary;
public:
	ComplexLiteral(INumberLiteral* r = new IntegerLiteral(0), INumberLiteral* i = new IntegerLiteral(0)) 
		: ILiteral(COMPLEX), real(r), imaginary(i) {}
	string toString() const { return real->toString() + "$" + imaginary->toString(); }
};

class ExpressionLiteral : public ILiteral {
	string expression;
public:
	ExpressionLiteral(string e) : ILiteral(EXPRESSION), expression(e) {}
};

class ProgramLiteral : public ILiteral {
	string program;
public:
	ProgramLiteral(string p) : ILiteral(PROGRAM), program(p) {}
};

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
