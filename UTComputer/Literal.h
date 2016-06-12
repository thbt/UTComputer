#pragma once
#include <iostream>
#include <string>

// TODO: destructor where its needed

class IOperand {
public:
	virtual std::string toString() const = 0;
};

enum Type { INTEGER, RATIONAL, REAL, COMPLEX, EXPRESSION, PROGRAM };

class ILiteral : public IOperand {
	Type type;
public:
	ILiteral(Type t) : type(t) {}

	Type getType() const { return type; }

	virtual ILiteral* clone() const = 0;
	virtual std::string toString() const = 0;
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
	
	virtual ILiteral* clone() const = 0;
	virtual std::string toString() const = 0;
	virtual bool isNul() const = 0;
	//virtual void accept(IOperator&) = 0;

};

class IntegerLiteral : public INumberLiteral {
	int value;
public:
	IntegerLiteral(int v) : INumberLiteral(INTEGER), value(v) {}
	ILiteral* clone() const { return new IntegerLiteral(*this); }

	int getValue() const { return value; }
	bool isNul() const {
		if (value == 0)
			return true;
		return false;
	}

	std::string toString() const { return std::to_string(value); }
	//void accept(IOperator& o) { o.visitIntegerLiteral(this); }
};

// TODO on conserve le fait que le numérateur soit une entier ou seulement un int ?
class RationalLiteral : public INumberLiteral {
	int numerator;
	int denominator;
public:
	RationalLiteral(int n, int d) : INumberLiteral(RATIONAL), numerator(n), denominator(d) { simplification(); }
	ILiteral* clone() const { return new RationalLiteral(*this); }

	std::string toString() const { return std::to_string(numerator) + "/" + std::to_string(denominator); }

	std::pair<int, int> getValue() const {
		std::pair<int, int> twoValues;
		twoValues.first = numerator;
		twoValues.second = denominator;
		return twoValues;
	}

	bool isNul() const {
		if (numerator == 0)
			return true;
		return false;
	}

	void simplification();

};

// TODO : Exception pour 0.0
class RealLiteral : public INumberLiteral {
	double value;
public:
	RealLiteral(double v) : INumberLiteral(REAL), value(v) {}
	ILiteral* clone() const { return new RealLiteral(*this); }

	std::string toString() const { return std::to_string(value); }
	double getValue() const { return value; }
	bool isNul() const {
		if (value == 0)
			return true;
		return false;
	}
};

class ComplexLiteral : public ILiteral {
	INumberLiteral* real;
	INumberLiteral* imaginary;
public:
	ComplexLiteral(INumberLiteral* r = new IntegerLiteral(0), INumberLiteral* i = new IntegerLiteral(0)) 
		: ILiteral(COMPLEX), real(r), imaginary(i) {}
	ILiteral* clone() const { return new ComplexLiteral(*this); }

	std::string toString() const { return real->toString() + "$" + imaginary->toString(); }

	INumberLiteral& Re() const { return *real; }
	INumberLiteral& Im() const { return *imaginary; }

	Type getTypeReal() const { return real->getType(); }
	Type getTypeIm() const { return imaginary->getType(); }

	/* Zzzzz
	std::pair<INumberLiteral, INumberLiteral> getValue() const {
		std::pair<INumberLiteral, INumberLiteral> twoValues;
		twoValues.first = *real;
		twoValues.second = *imaginary;
		return twoValues;
	}*/
};

class ExpressionLiteral : public ILiteral {
	std::string expression;
public:
	ExpressionLiteral(std::string e) : ILiteral(EXPRESSION), expression(e) {}
	ILiteral* clone() const { return new ExpressionLiteral(*this); }

	std::string getValue() const {
		return expression;
	}
	
	std::string toString() const { return expression; }
	bool isNul() const { return expression == ""; }
};

class ProgramLiteral : public ILiteral {
	std::string program;
public:
	ProgramLiteral(std::string p) : ILiteral(PROGRAM), program(p) {}
	ILiteral* clone() const { return new ProgramLiteral(*this); }

	std::string getValue() const {
		return program;
	}
	
	std::string toString() const { return program; }
	bool isNul() const { return program == ""; }
};