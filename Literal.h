#pragma once
#include <iostream>
#include <string>

using namespace std;

// TODO: destructor where its needed


class ILiteral {
public:
	virtual ILiteral* eval() = 0;

	virtual string toString() const = 0;
	virtual void print(ostream& o) const = 0;
	virtual ostream& operator<<(ostream& o) const = 0;
};

class INumberLiteral : public ILiteral {
public:
	virtual ILiteral* eval() = 0;
	virtual string toString() const = 0;
	virtual void print(ostream& o) const = 0;
	virtual ostream& operator<<(ostream& o) const = 0;
};

class IntegerLiteral : public INumberLiteral {
	signed int value;
public:
	IntegerLiteral(int v) : value(v) {}
	
	ILiteral* eval() { return this; }

	string toString() const { return to_string(value); }
	void print(ostream& o = cout) const { o << value; }
	ostream& operator<<(ostream& o) const { print(o); return o; }
};

class RationalLiteral : public INumberLiteral {
	IntegerLiteral numerator;
	IntegerLiteral denominator;
public:
	RationalLiteral(int n = 0, int d = 1) : numerator(IntegerLiteral(n)), denominator(IntegerLiteral(d)) {}
	RationalLiteral(IntegerLiteral n = IntegerLiteral(0), IntegerLiteral d = IntegerLiteral(1)) : numerator(n), denominator(d) {}

	ILiteral* eval() { return this; }

	string toString() const { return numerator.toString() + "/" + denominator.toString(); }
	void print(ostream& o = cout) const { o << numerator.toString() << "/" << denominator.toString(); }
	ostream& operator<<(ostream& o) const { print(o); return o; }
};

// TODO : utiliser un double et pas se faire chier ?
class RealLiteral : public INumberLiteral {
	IntegerLiteral integer;
	IntegerLiteral mantissa;
public:
	RealLiteral(int i = 0, int m = 0) : integer(IntegerLiteral(i)), mantissa(IntegerLiteral(m)) {}
	RealLiteral(IntegerLiteral i = IntegerLiteral(0), IntegerLiteral m = IntegerLiteral(0)) : integer(i), mantissa(m) {}

	ILiteral* eval() { return this; }

	string toString() const { return integer.toString() + "." + mantissa.toString(); }
	void print(ostream& o = cout) const { o << integer.toString() << "." << mantissa.toString(); }
	ostream& operator<<(ostream& o) const { print(o); return o; }
};

class ComplexLiteral : public ILiteral {
	INumberLiteral* real;
	INumberLiteral* imaginary;
public:
	ComplexLiteral(INumberLiteral* r = new IntegerLiteral(0), INumberLiteral* i = new IntegerLiteral(0)) : real(r), imaginary(i) {}

	ILiteral* eval() { return this; }

	string toString() const { return real->toString() + "$" + imaginary->toString(); }
	void print(ostream& o = cout) const { o << real->toString() << "$" << imaginary->toString(); }
	ostream& operator<<(ostream& o) const { print(o); return o; }
};

// controler si l'atome commence bien par une majuscule
class AtomLiteral : public ILiteral {
	string name;
	ILiteral* identity;
public: 
	AtomLiteral(string n, ILiteral* i) : name(n), identity(i) {}

	ILiteral* eval() { return identity; }

	string toString() const { return name; }
	void print(ostream& o = cout) const { o << name; }
	ostream& operator<<(ostream& o) const { print(o); return o; }
};

/*
class ExpressionLiteral : public ILiteral {
	string expression;	
public:
	ExpressionLiteral(string e) : expression(e) {}
};

class ProgramLiteral : public ILiteral {
};
*/