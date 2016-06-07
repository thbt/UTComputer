#include <stack>
#include <queue>
#include <cctype>

#include "Operator.h"
#include "LiteralFactory.h"
#include "OperatorException.h"
#include "Controller.h"

void PlusOp::operator()(Stack* s) {
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : + prend deux arguments");

	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	if ((lt != INTEGER && lt != REAL && lt != RATIONAL && lt != COMPLEX) || (rt != INTEGER && rt != REAL && rt != RATIONAL && rt != COMPLEX)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : / ne prend que des nombres (Entier, RŽel, Rationnel ou Complexe)");
	}


	std::pair<int, int> pairRa;
	INumberLiteral* pRe;
	INumberLiteral* pIm;
	int intVal;
	double doubleVal;
	double r;
	Type t;

	switch (lt) {
	case INTEGER:
		intVal = dynamic_cast<IntegerLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal + dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal + dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first = dynamic_cast<RationalLiteral*>(right)->getValue().first + (intVal*dynamic_cast<RationalLiteral*>(right)->getValue().second);
			pairRa.second = dynamic_cast<RationalLiteral*>(right)->getValue().second;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			switch (t){
			case INTEGER:
				s->push(LiteralFactory::getInstance().makeLiteral(new IntegerLiteral(intVal + dynamic_cast<IntegerLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case REAL:
				s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(intVal + dynamic_cast<RealLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case RATIONAL:
				s->push(LiteralFactory::getInstance().makeLiteral(new RationalLiteral(dynamic_cast<RationalLiteral*>(pRe)->getValue().first + (intVal*dynamic_cast<RationalLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->getValue().second),
					dynamic_cast<RationalLiteral*>(pRe)->getValue().second),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			}
			break;

		}
		break;

	case RATIONAL:
		pairRa.first = dynamic_cast<RationalLiteral*>(left)->getValue().first;
		pairRa.second = dynamic_cast<RationalLiteral*>(left)->getValue().second;
		switch (rt) {
		case INTEGER:
			pairRa.first += dynamic_cast<IntegerLiteral*>(right)->getValue()*pairRa.second;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case REAL:
			r = (float)pairRa.first / (float)pairRa.second;
			s->push(LiteralFactory::getInstance().makeLiteral(r + dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first *= dynamic_cast<RationalLiteral*>(right)->getValue().second;
			pairRa.first += dynamic_cast<RationalLiteral*>(right)->getValue().first * pairRa.second;
			pairRa.second *= dynamic_cast<RationalLiteral*>(right)->getValue().second;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			switch (t){
			case INTEGER:
				s->push(LiteralFactory::getInstance().makeLiteral(
					new RationalLiteral(dynamic_cast<IntegerLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->getValue()*pairRa.second + pairRa.first, pairRa.second),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case REAL:
				r = (float)pairRa.first / (float)pairRa.second;
				s->push(LiteralFactory::getInstance().makeLiteral(
					new RealLiteral(r + dynamic_cast<RealLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->getValue()),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case RATIONAL:
				pairRa.second *= dynamic_cast<RationalLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->getValue().second;
				s->push(LiteralFactory::getInstance().makeLiteral(
					new RationalLiteral(pairRa.first*dynamic_cast<RationalLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->getValue().second + dynamic_cast<RationalLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->getValue().first * pairRa.second, dynamic_cast<RationalLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->getValue().second*pairRa.second),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			}
			break;
		}
		break;

	case REAL:
		doubleVal = dynamic_cast<RealLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal + dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal + dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first = dynamic_cast<RationalLiteral*>(right)->getValue().first;
			pairRa.second = dynamic_cast<RationalLiteral*>(right)->getValue().second;
			r = (float)pairRa.first / (float)pairRa.second;
			s->push(LiteralFactory::getInstance().makeLiteral(r + doubleVal));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			switch (t){
			case INTEGER:
				s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(doubleVal + dynamic_cast<IntegerLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case REAL:
				s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(doubleVal + dynamic_cast<RealLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case RATIONAL:
				r = (float)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (float)dynamic_cast<RationalLiteral*>(pRe)->getValue().second;
				s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(r + doubleVal),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			}
			break;

		}
		break;

	case COMPLEX:
		pRe = &dynamic_cast<ComplexLiteral*>(left)->Re();
		pIm = &dynamic_cast<ComplexLiteral*>(left)->Im();

		if (rt != COMPLEX){
			s->push(right);
			s->push(left);
			this->operator()(s);
		} else {
			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			this->operator()(s);
			ILiteral* partiReel = s->top(); s->pop();
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			this->operator()(s);
			ILiteral* partiIm = s->top(); s->pop();
			t = partiReel->getType();
			if (t == INTEGER){
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
			else if (t == REAL){
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
			else{
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
		}

		break;
	}
}

void MinusOp::operator()(Stack* s) {
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : - prend deux arguments");

	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	if ((lt != INTEGER && lt != REAL && lt != RATIONAL && lt != COMPLEX) || (rt != INTEGER && rt != REAL && rt != RATIONAL && rt != COMPLEX)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : / ne prend que des nombres (Entier, Réel, Rationnel ou Complexe)");
	}

	std::pair<int, int> pairRa;
	INumberLiteral* pRe;
	INumberLiteral* pIm;
	int intVal;
	double doubleVal;
	double r;
	Type t;

	//cout << "Type 1 : " << rt << ", type 2 : " << lt << endl;

	switch (lt) {
	case INTEGER:
		intVal = dynamic_cast<IntegerLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal - dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal - dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first = (intVal*dynamic_cast<RationalLiteral*>(right)->getValue().second) - dynamic_cast<RationalLiteral*>(right)->getValue().first;
			pairRa.second = dynamic_cast<RationalLiteral*>(right)->getValue().second;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			switch (t){
			case INTEGER:
				s->push(LiteralFactory::getInstance().makeLiteral(new IntegerLiteral(intVal - dynamic_cast<IntegerLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case REAL:
				s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(intVal - dynamic_cast<RealLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case RATIONAL:
				s->push(LiteralFactory::getInstance().makeLiteral(new RationalLiteral((intVal*dynamic_cast<RationalLiteral*>(pRe)->getValue().second) - dynamic_cast<RationalLiteral*>(pRe)->getValue().first,
					dynamic_cast<RationalLiteral*>(pRe)->getValue().second),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			}
			break;

		}
		break;

	case RATIONAL:
		pairRa.first = dynamic_cast<RationalLiteral*>(left)->getValue().first;
		pairRa.second = dynamic_cast<RationalLiteral*>(left)->getValue().second;
		switch (rt) {
		case INTEGER:
			pairRa.first -= dynamic_cast<IntegerLiteral*>(right)->getValue()*pairRa.second;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case REAL:
			r = (float)pairRa.first / (float)pairRa.second;
			s->push(LiteralFactory::getInstance().makeLiteral(r - dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first *= dynamic_cast<RationalLiteral*>(right)->getValue().second;
			pairRa.first -= dynamic_cast<RationalLiteral*>(right)->getValue().first * pairRa.second;
			pairRa.second *= dynamic_cast<RationalLiteral*>(right)->getValue().second;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			switch (t){
			case INTEGER:
				s->push(LiteralFactory::getInstance().makeLiteral(
					new RationalLiteral(pairRa.first - dynamic_cast<IntegerLiteral*>(pRe)->getValue()*pairRa.second, pairRa.second),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case REAL:
				r = (float)pairRa.first / (float)pairRa.second;
				s->push(LiteralFactory::getInstance().makeLiteral(
					new RealLiteral(r - dynamic_cast<RealLiteral*>(pRe)->getValue()),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case RATIONAL:
				s->push(LiteralFactory::getInstance().makeLiteral(
					new RationalLiteral(pairRa.first*dynamic_cast<RationalLiteral*>(pRe)->getValue().second - dynamic_cast<RationalLiteral*>(pRe)->getValue().first * pairRa.second,
					pairRa.second * dynamic_cast<RationalLiteral*>(pRe)->getValue().second),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			}
			break;
		}
		break;

	case REAL:
		doubleVal = dynamic_cast<RealLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal - dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal - dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first = dynamic_cast<RationalLiteral*>(right)->getValue().first;
			pairRa.second = dynamic_cast<RationalLiteral*>(right)->getValue().second;
			r = (float)pairRa.first / (float)pairRa.second;
			s->push(LiteralFactory::getInstance().makeLiteral(r - doubleVal));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			switch (t){
			case INTEGER:
				s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(doubleVal - dynamic_cast<IntegerLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case REAL:
				s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(doubleVal - dynamic_cast<RealLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			case RATIONAL:
				r = (float)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (float)dynamic_cast<RationalLiteral*>(pRe)->getValue().second;
				s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(r - doubleVal),
					&dynamic_cast<ComplexLiteral*>(right)->Im()));
				break;
			}
			break;

		}
		break;

	case COMPLEX:
		pRe = &dynamic_cast<ComplexLiteral*>(left)->Re();
		pIm = &dynamic_cast<ComplexLiteral*>(left)->Im();

		if (rt != COMPLEX){
			s->push(right);
			s->push(left);
			this->operator()(s);
			ComplexLiteral* cmpI = dynamic_cast<ComplexLiteral*>(s->top()); s->pop();
			t = cmpI->Re().getType();
			switch (t) {
			case(INTEGER) :
				s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(LiteralFactory::getInstance().makeLiteral(-dynamic_cast<IntegerLiteral*>(&cmpI->Re())->getValue())), &cmpI->Im()));
				break;
			case(REAL) :
				s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(LiteralFactory::getInstance().makeLiteral(-dynamic_cast<RealLiteral*>(&cmpI->Re())->getValue())), &cmpI->Im()));
				break;
			case(RATIONAL) :
				pairRa = dynamic_cast<RationalLiteral*>(&cmpI->Re())->getValue();
				pairRa.first *= -1;
				s->push(LiteralFactory::getInstance().makeLiteral(new RationalLiteral(pairRa.first, pairRa.second), &cmpI->Im()));
				break;
			}
		}
		else{
			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			this->operator()(s);
			ILiteral* partiReel = s->top(); s->pop();
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			this->operator()(s);
			ILiteral* partiIm = s->top(); s->pop();
			t = partiReel->getType();
			if (t == INTEGER){
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
			else if (t == REAL){
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
			else{
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
		}

		break;
	}
}

void MultiOp::operator()(Stack* s) {
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : * prend deux arguments");

	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	if ((lt != INTEGER && lt != REAL && lt != RATIONAL && lt != COMPLEX) ||
		(rt != INTEGER && rt != REAL && rt != RATIONAL && rt != COMPLEX)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : * ne prend que des nombres (Entier, RŽel, Rationnel ou Complexe)");
	}

	std::pair<int, int> pairRa;
	INumberLiteral* pRe;
	INumberLiteral* pIm;
	int intVal;
	double doubleVal;
	double r;
	Type t, t2;


	INumberLiteral* INL1 = new IntegerLiteral(0);
	INumberLiteral* INL2 = new IntegerLiteral(0);

	switch (lt) {
	case INTEGER:
		intVal = dynamic_cast<IntegerLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal * dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal * dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first = intVal* dynamic_cast<RationalLiteral*>(right)->getValue().first;
			pairRa.second = dynamic_cast<RationalLiteral*>(right)->getValue().second;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			t2 = dynamic_cast<ComplexLiteral*>(right)->Im().getType();
			pIm = &dynamic_cast<ComplexLiteral*>(right)->Im();
			switch (t){
			case INTEGER:
				INL1 = new IntegerLiteral(intVal * dynamic_cast<IntegerLiteral*>(pRe)->getValue());
				break;
			case REAL:
				INL1 = new RealLiteral(intVal * dynamic_cast<RealLiteral*>(pRe)->getValue());
				break;
			case RATIONAL:
				INL1 = new RationalLiteral(intVal * dynamic_cast<RationalLiteral*>(pRe)->getValue().first, dynamic_cast<RationalLiteral*>(pRe)->getValue().second);
				break;
			}

			switch (t2){
			case INTEGER:
				INL2 = new IntegerLiteral(intVal * dynamic_cast<IntegerLiteral*>(pIm)->getValue());
				break;
			case REAL:
				INL2 = new RealLiteral(intVal * dynamic_cast<RealLiteral*>(pIm)->getValue());
				break;
			case RATIONAL:
				INL2 = new RationalLiteral(intVal * dynamic_cast<RationalLiteral*>(pIm)->getValue().first, dynamic_cast<RationalLiteral*>(pIm)->getValue().second);
				break;
			}
			s->push(LiteralFactory::getInstance().makeLiteral(INL1, INL2));

			break;

		}
		break;

	case RATIONAL:
		pairRa.first = dynamic_cast<RationalLiteral*>(left)->getValue().first;
		pairRa.second = dynamic_cast<RationalLiteral*>(left)->getValue().second;
		switch (rt) {
		case INTEGER:
			pairRa.first *= dynamic_cast<IntegerLiteral*>(right)->getValue();
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case REAL:
			r = (float)pairRa.first / (float)pairRa.second;
			s->push(LiteralFactory::getInstance().makeLiteral(r * dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first *= dynamic_cast<RationalLiteral*>(right)->getValue().first;
			pairRa.second *= dynamic_cast<RationalLiteral*>(right)->getValue().second;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			t2 = dynamic_cast<ComplexLiteral*>(right)->Im().getType();
			pIm = &dynamic_cast<ComplexLiteral*>(right)->Im();
			switch (t){
			case INTEGER:
				INL1 = new RationalLiteral(pairRa.first * dynamic_cast<IntegerLiteral*>(pRe)->getValue(), pairRa.second);
				break;
			case REAL:
				INL1 = new RealLiteral((double)pairRa.first / (double)pairRa.second * dynamic_cast<RealLiteral*>(pRe)->getValue());
				break;
			case RATIONAL:
				INL1 = new RationalLiteral(pairRa.first * dynamic_cast<RationalLiteral*>(pRe)->getValue().first, pairRa.second * dynamic_cast<RationalLiteral*>(pRe)->getValue().second);
				break;
			}

			switch (t2){
			case INTEGER:
				INL2 = new RationalLiteral(pairRa.first * dynamic_cast<IntegerLiteral*>(pIm)->getValue(), pairRa.second);
				break;
			case REAL:
				INL2 = new RealLiteral((double)pairRa.first / (double)pairRa.second * dynamic_cast<RealLiteral*>(pIm)->getValue());
				break;
			case RATIONAL:
				INL2 = new RationalLiteral(pairRa.first * dynamic_cast<RationalLiteral*>(pIm)->getValue().first, pairRa.second * dynamic_cast<RationalLiteral*>(pRe)->getValue().second);
				break;
			}
			s->push(LiteralFactory::getInstance().makeLiteral(INL1, INL2));
			break;
		}
		break;

	case REAL:
		doubleVal = dynamic_cast<RealLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal * dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal * dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first = dynamic_cast<RationalLiteral*>(right)->getValue().first;
			pairRa.second = dynamic_cast<RationalLiteral*>(right)->getValue().second;
			r = (double)pairRa.first / (double)pairRa.second;
			s->push(LiteralFactory::getInstance().makeLiteral(r * doubleVal));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			t2 = dynamic_cast<ComplexLiteral*>(right)->Im().getType();
			pIm = &dynamic_cast<ComplexLiteral*>(right)->Im();
			switch (t){
			case INTEGER:
				INL1 = new RealLiteral(doubleVal * dynamic_cast<IntegerLiteral*>(pRe)->getValue());
				break;
			case REAL:
				INL1 = new RealLiteral(doubleVal * dynamic_cast<RealLiteral*>(pRe)->getValue());
				break;
			case RATIONAL:
				INL1 = new RealLiteral(doubleVal * ((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second));
				break;
			}

			switch (t2){
			case INTEGER:
				INL2 = new RealLiteral(doubleVal * dynamic_cast<IntegerLiteral*>(pIm)->getValue());
				break;
			case REAL:
				INL2 = new RealLiteral(doubleVal * dynamic_cast<RealLiteral*>(pIm)->getValue());
				break;
			case RATIONAL:
				INL2 = new RealLiteral(doubleVal * ((double)dynamic_cast<RationalLiteral*>(pIm)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pIm)->getValue().second));
				break;
			}
			s->push(LiteralFactory::getInstance().makeLiteral(INL1, INL2));
			break;
		}
		break;

	case COMPLEX:
		pRe = &dynamic_cast<ComplexLiteral*>(left)->Re();
		pIm = &dynamic_cast<ComplexLiteral*>(left)->Im();

		if (rt != COMPLEX){
			s->push(right);
			s->push(left);
			this->operator()(s);
		}
		else{ //(aa' – bb') + i (ab' + ba')
			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			this->operator()(s);
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			this->operator()(s);
			MinusOp mop;
			mop(s);
			ILiteral* partiReel = s->top(); s->pop();

			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			this->operator()(s);
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			this->operator()(s);
			PlusOp pop;
			pop(s);
			ILiteral* partiIm = s->top(); s->pop();

			t = partiReel->getType();
			if (t == INTEGER){
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
			else if (t == REAL){
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
			else{
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
		}

		break;
	}
}

void DivOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : / a besoin de deux arguments");

	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	if ((lt != INTEGER && lt != REAL && lt != RATIONAL && lt != COMPLEX) || (rt != INTEGER && rt != REAL && rt != RATIONAL && rt != COMPLEX)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : / ne prend que des nombres (Entier, Réel, Rationnel ou Complexe)");
	}

	if (rt == COMPLEX){
		if (dynamic_cast<ComplexLiteral*>(right)->Re().isNul() && dynamic_cast<ComplexLiteral*>(right)->Im().isNul()){
			s->push(left);
			s->push(right);
			throw OperatorException("Erreur : Division par zéro impossible");
		}
	}
	else{
		if (dynamic_cast<INumberLiteral*>(right)->isNul()){
			s->push(left);
			s->push(right);
			throw OperatorException("Erreur : Division par zéro impossible");
		}
	}




	std::pair<int, int> pairRa;
	INumberLiteral* pRe;
	INumberLiteral* pIm;
	int intVal;
	double doubleVal;
	double r;
	Type t, t2;

	MinusOp mop;
	PlusOp pop;
	MultiOp muop;

	std::pair<int, int> pairReel;
	std::pair<int, int> pairIm;

	INumberLiteral* INL1 = new IntegerLiteral(0);
	INumberLiteral* INL2 = new IntegerLiteral(0);

	switch (lt) {
	case INTEGER:
		intVal = dynamic_cast<IntegerLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral((double)intVal / dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal / dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first = dynamic_cast<RationalLiteral*>(right)->getValue().second * intVal;
			pairRa.second = dynamic_cast<RationalLiteral*>(right)->getValue().first;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX: // x*(a-ib)/(a²+b²)
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			t2 = dynamic_cast<ComplexLiteral*>(right)->Im().getType();
			pIm = &dynamic_cast<ComplexLiteral*>(right)->Im();
			switch (t){
			case INTEGER:
				switch (t2){
				case INTEGER:
					pairReel.first = dynamic_cast<IntegerLiteral*>(pRe)->getValue() * intVal;
					pairReel.second = (dynamic_cast<IntegerLiteral*>(pRe)->getValue()*dynamic_cast<IntegerLiteral*>(pRe)->getValue()) + (dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue());
					INL1 = new RationalLiteral(pairReel.first, pairReel.second);
					pairIm.first = dynamic_cast<IntegerLiteral*>(pIm)->getValue() * intVal;
					pairIm.second = -((dynamic_cast<IntegerLiteral*>(pRe)->getValue()*dynamic_cast<IntegerLiteral*>(pRe)->getValue()) + (dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					INL2 = new RationalLiteral(pairIm.first, pairIm.second);
					break;
				case REAL:
					INL1 = new RealLiteral((intVal * dynamic_cast<IntegerLiteral*>(pRe)->getValue()) / (dynamic_cast<IntegerLiteral*>(pRe)->getValue()*dynamic_cast<IntegerLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((-intVal * dynamic_cast<RealLiteral*>(pIm)->getValue()) / (dynamic_cast<IntegerLiteral*>(pRe)->getValue()*dynamic_cast<IntegerLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					break;
				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new IntegerLiteral(intVal));
					muop(s);
					if ((INL1 = dynamic_cast<RationalLiteral*>(s->top())) == nullptr)
						INL1 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new IntegerLiteral(-intVal));
					muop(s);
					for (auto it = s->begin(); it != s->end(); it++) {
						std::cout << (*it)->toString() << std::endl;
					}
					if ((INL2 = dynamic_cast<RationalLiteral*>(s->top())) == nullptr)
						INL2 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();
					break;
				}
				break;

			case REAL:
				switch (t2){
				case INTEGER:
					INL1 = new RealLiteral((intVal * dynamic_cast<RealLiteral*>(pRe)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((-intVal * dynamic_cast<IntegerLiteral*>(pIm)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					break;
				case REAL:
					INL1 = new RealLiteral((intVal * dynamic_cast<RealLiteral*>(pRe)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((-intVal * dynamic_cast<RealLiteral*>(pIm)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					break;
				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new IntegerLiteral(intVal));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new IntegerLiteral(-intVal));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top()); s->pop();
					break;
				}
				break;
			case RATIONAL:
				switch (t2){
				case INTEGER:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new IntegerLiteral(intVal));
					muop(s);
					if ((INL1 = dynamic_cast<RationalLiteral*>(s->top())) == nullptr)
						INL1 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new IntegerLiteral(-intVal));
					muop(s);
					if ((INL2 = dynamic_cast<RationalLiteral*>(s->top())) == nullptr)
						INL2 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();

					break;
				case REAL:
					INL1 = new RealLiteral((intVal * ((double)(dynamic_cast<RationalLiteral*>(pRe)->getValue().first) / (double)(dynamic_cast<RationalLiteral*>(pRe)->getValue().second))) / ((((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)*((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)) + (dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue())));
					INL2 = new RealLiteral((-intVal * dynamic_cast<RealLiteral*>(pIm)->getValue()) / ((((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)*((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)) + (dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue())));
					break;
				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new IntegerLiteral(intVal));
					muop(s);
					INL1 = dynamic_cast<RationalLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new IntegerLiteral(-intVal));
					muop(s);
					INL2 = dynamic_cast<RationalLiteral*>(s->top()); s->pop();
					break;
				}
			}
			s->push(LiteralFactory::getInstance().makeLiteral(INL1, INL2));
			break;
		}
		break;

	case REAL:
		doubleVal = dynamic_cast<RealLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal / dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal / dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			s->push(LiteralFactory::getInstance().makeLiteral(doubleVal / ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second)));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			t2 = dynamic_cast<ComplexLiteral*>(right)->Im().getType();
			pIm = &dynamic_cast<ComplexLiteral*>(right)->Im();
			switch (t){
			case INTEGER:
				switch (t2){
				case INTEGER:
					INL1 = new RealLiteral((doubleVal * dynamic_cast<IntegerLiteral*>(pRe)->getValue()) / (dynamic_cast<IntegerLiteral*>(pRe)->getValue()*dynamic_cast<IntegerLiteral*>(pRe)->getValue() + dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((-doubleVal * dynamic_cast<IntegerLiteral*>(pIm)->getValue()) / (dynamic_cast<IntegerLiteral*>(pRe)->getValue()*dynamic_cast<IntegerLiteral*>(pRe)->getValue() + dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					break;
				case REAL:
					INL1 = new RealLiteral((doubleVal * dynamic_cast<IntegerLiteral*>(pRe)->getValue()) / (dynamic_cast<IntegerLiteral*>(pRe)->getValue()*dynamic_cast<IntegerLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((-doubleVal * dynamic_cast<RealLiteral*>(pIm)->getValue()) / (dynamic_cast<IntegerLiteral*>(pRe)->getValue()*dynamic_cast<IntegerLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					break;
				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RealLiteral(doubleVal));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RealLiteral(-doubleVal));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top()); s->pop();
					break;
				}
				break;

			case REAL:
				switch (t2){
				case INTEGER:
					INL1 = new RealLiteral((doubleVal * dynamic_cast<RealLiteral*>(pRe)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((-doubleVal * dynamic_cast<IntegerLiteral*>(pIm)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					break;
				case REAL:
					INL1 = new RealLiteral((doubleVal * dynamic_cast<RealLiteral*>(pRe)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((-doubleVal * dynamic_cast<RealLiteral*>(pIm)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					break;
				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RealLiteral(doubleVal));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RealLiteral(-doubleVal));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top()); s->pop();
					break;
				}
				break;

			case RATIONAL:
				switch (t2){
				case INTEGER:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RealLiteral(doubleVal));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RealLiteral(-doubleVal));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();
					break;
				case REAL:
					INL1 = new RealLiteral((doubleVal * ((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)) / ((((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)*((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)) + (dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue())));
					INL2 = new RealLiteral((-doubleVal * dynamic_cast<RealLiteral*>(pIm)->getValue()) / ((((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)*((double)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (double)dynamic_cast<RationalLiteral*>(pRe)->getValue().second)) + (dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue())));
					break;
				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RealLiteral(doubleVal));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RealLiteral(-doubleVal));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top()); s->pop();
					break;
				}
			}
			s->push(LiteralFactory::getInstance().makeLiteral(INL1, INL2));
			break;
		}
		break;

	case RATIONAL:
		pairRa.first = dynamic_cast<RationalLiteral*>(left)->getValue().first;
		pairRa.second = dynamic_cast<RationalLiteral*>(left)->getValue().second;
		switch (rt) {
		case INTEGER:
			pairReel.first = pairRa.first;
			pairReel.second = pairRa.second*dynamic_cast<IntegerLiteral*>(right)->getValue();
			s->push(LiteralFactory::getInstance().makeLiteral(pairReel));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(((double)pairRa.first / (double)pairRa.second) / dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first *= dynamic_cast<RationalLiteral*>(right)->getValue().second;
			pairRa.second *= dynamic_cast<RationalLiteral*>(right)->getValue().first;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX:
			t = dynamic_cast<ComplexLiteral*>(right)->Re().getType();
			pRe = &dynamic_cast<ComplexLiteral*>(right)->Re();
			t2 = dynamic_cast<ComplexLiteral*>(right)->Im().getType();
			pIm = &dynamic_cast<ComplexLiteral*>(right)->Im();
			switch (t){
			case INTEGER:
				switch (t2){
				case INTEGER:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(pairRa.first, pairRa.second));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(-pairRa.first, pairRa.second));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top()); s->pop();
					break;

				case REAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(pairRa.first, pairRa.second));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(-pairRa.first, pairRa.second));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top()); s->pop();
					break;

				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(pairRa.first, pairRa.second));
					muop(s);
					if ((INL1 = dynamic_cast<RationalLiteral*>(s->top())) == nullptr)
						INL1 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(-pairRa.first, pairRa.second));
					muop(s);
					if ((INL2 = dynamic_cast<RationalLiteral*>(s->top())) == nullptr)
						INL2 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();
					break;
				}
				break;

			case REAL:
				switch (t2){
				case INTEGER:
					INL1 = new RealLiteral((((double)pairRa.first / (double)pairRa.second) * dynamic_cast<RealLiteral*>(pRe)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((((double)-pairRa.first / (double)pairRa.second) * dynamic_cast<IntegerLiteral*>(pIm)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<IntegerLiteral*>(pIm)->getValue()*dynamic_cast<IntegerLiteral*>(pIm)->getValue()));
					break;
				case REAL:
					INL1 = new RealLiteral((((double)pairRa.first / (double)pairRa.second) * dynamic_cast<RealLiteral*>(pRe)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					INL2 = new RealLiteral((((double)-pairRa.first / (double)pairRa.second) * dynamic_cast<RealLiteral*>(pIm)->getValue()) / (dynamic_cast<RealLiteral*>(pRe)->getValue()*dynamic_cast<RealLiteral*>(pRe)->getValue() + dynamic_cast<RealLiteral*>(pIm)->getValue()*dynamic_cast<RealLiteral*>(pIm)->getValue()));
					break;
				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(pairRa.first, pairRa.second));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(-pairRa.first, pairRa.second));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top()); s->pop();
					break;
				}
				break;

			case RATIONAL: /* MARQUE */
				switch (t2){
				case INTEGER:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(pairRa.first, pairRa.second));
					muop(s);
					if ((INL1 = dynamic_cast<RationalLiteral*>(s->top())) == nullptr)
						INL1 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(-pairRa.first, pairRa.second));
					muop(s);
					if ((INL2 = dynamic_cast<RationalLiteral*>(s->top())) == nullptr)
						INL2 = dynamic_cast<RealLiteral*>(s->top());
					s->pop();
					break;
				case REAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(pairRa.first, pairRa.second));
					muop(s);
					INL1 = dynamic_cast<RealLiteral*>(s->top()), s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(-pairRa.first, pairRa.second));
					muop(s);
					INL2 = dynamic_cast<RealLiteral*>(s->top()); s->pop();
					break;
				case RATIONAL:
					s->push(pRe);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(pairRa.first, pairRa.second));
					muop(s);
					INL1 = dynamic_cast<RationalLiteral*>(s->top()); s->pop();

					s->push(pIm);
					s->push(pRe);
					s->push(pRe);
					muop(s);
					s->push(pIm);
					s->push(pIm);
					muop(s);
					pop(s);
					this->operator()(s);
					s->push(new RationalLiteral(-pairRa.first, pairRa.second));
					muop(s);
					INL2 = dynamic_cast<RationalLiteral*>(s->top()); s->pop();
					break;
				}
			}
			s->push(LiteralFactory::getInstance().makeLiteral(INL1, INL2));
			break;
		}
		break;

	case COMPLEX: // MARQUE A TESTER
		pRe = &dynamic_cast<ComplexLiteral*>(left)->Re();
		pIm = &dynamic_cast<ComplexLiteral*>(left)->Im();

		if (rt != COMPLEX){
			s->push(new IntegerLiteral(1));
			s->push(right);
			muop(s);
			s->push(left);
			this->operator()(s);
		}
		else{ //(aa' + bb')/a'²+b'² + i (ba' - ab')/a'²+b'²
			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			muop(s);
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			muop(s);
			pop(s);
			s->push(pIm);
			s->push(pIm);
			muop(s);
			s->push(pRe);
			s->push(pRe);
			muop(s);
			pop(s);
			this->operator()(s);
			ILiteral* partiReel = s->top(); s->pop();

			//i(ba' - ab') / a'²+b'²
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			muop(s);
			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			muop(s);
			mop(s);
			s->push(pIm);
			s->push(pIm);
			muop(s);
			s->push(pRe);
			s->push(pRe);
			muop(s);
			pop(s);
			this->operator()(s);
			ILiteral* partiIm = s->top(); s->pop();

			t = partiReel->getType();
			if (t == INTEGER){
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
			else if (t == REAL){
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
			else{
				t = partiIm->getType();
				switch (t){
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
					break;
				case RATIONAL:
					s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(partiReel), dynamic_cast<RationalLiteral*>(partiIm)));
					break;
				}
			}
		}

		break;
	}
}

void DivEntOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : DIV prend deux arguments");

	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	if (lt != INTEGER || rt != INTEGER) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : DIV ne prend que des entiers");
	}

	if (dynamic_cast<IntegerLiteral*>(right)->getValue() == 0){
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : division par 0 interdite");
	}

	int divEntier = dynamic_cast<IntegerLiteral*>(left)->getValue() / dynamic_cast<IntegerLiteral*>(right)->getValue();
	s->push(LiteralFactory::getInstance().makeLiteral(divEntier));
}

void ModulOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : MOD a besoin de deux arguments");

	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	if (lt != INTEGER || rt != INTEGER) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : MOD ne prend que des entiers");
	}

	if (dynamic_cast<IntegerLiteral*>(right)->getValue() == 0){
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : division par 0 interdite");
	}

	int divEntier = dynamic_cast<IntegerLiteral*>(left)->getValue() % dynamic_cast<IntegerLiteral*>(right)->getValue();
	s->push(LiteralFactory::getInstance().makeLiteral(divEntier));
}

void NegOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : NEG a besoin d'un argument");

	ILiteral* number = s->top(); s->pop();
	Type t = number->getType();
	std::pair<int, int> rationalNeg;

	if (t != INTEGER && t != REAL && t != RATIONAL && t != COMPLEX) {
		s->push(number);
		throw OperatorException("Erreur : NEG n'accepte que les nombres (Entier,Réel,Rationnel ou Complexe)");
	}

	switch (t){
	case INTEGER:
		s->push(LiteralFactory::getInstance().makeLiteral(-dynamic_cast<IntegerLiteral*>(number)->getValue()));
		break;
	case REAL:
		s->push(LiteralFactory::getInstance().makeLiteral(-dynamic_cast<RealLiteral*>(number)->getValue()));
		break;
	case RATIONAL:
		rationalNeg.first = -dynamic_cast<RationalLiteral*>(number)->getValue().first;
		rationalNeg.second = dynamic_cast<RationalLiteral*>(number)->getValue().second;
		s->push(LiteralFactory::getInstance().makeLiteral(rationalNeg));
		break;
	case COMPLEX:
		INumberLiteral* pRe = &dynamic_cast<ComplexLiteral*>(number)->Re();
		INumberLiteral* pIm = &dynamic_cast<ComplexLiteral*>(number)->Im();
		Type tRe = pRe->getType();
		Type tIm = pIm->getType();

		switch (tRe){
		case INTEGER:
			pRe = new IntegerLiteral(-dynamic_cast<IntegerLiteral*>(pRe)->getValue());
			break;

		case REAL:
			pRe = new RealLiteral(-dynamic_cast<RealLiteral*>(pRe)->getValue());
			break;

		case RATIONAL:
			pRe = new RationalLiteral(-dynamic_cast<RationalLiteral*>(pRe)->getValue().first, dynamic_cast<RationalLiteral*>(pRe)->getValue().second);
			break;
		}

		switch (tIm){
		case INTEGER:
			pIm = new IntegerLiteral(-dynamic_cast<IntegerLiteral*>(pIm)->getValue());
			break;

		case REAL:
			pIm = new RealLiteral(-dynamic_cast<RealLiteral*>(pIm)->getValue());
			break;

		case RATIONAL:
			pIm = new RationalLiteral(-dynamic_cast<RationalLiteral*>(pIm)->getValue().first, dynamic_cast<RationalLiteral*>(pIm)->getValue().second);
			break;
		}
		s->push(LiteralFactory::getInstance().makeLiteral(pRe, pIm));
		break;
	}
}

void NumOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : NUM a besoin d'un argument");

	ILiteral* number = s->top(); s->pop();

	Type t = number->getType();

	if (t != INTEGER && t != RATIONAL) {
		s->push(number);
		throw OperatorException("Erreur :NUM n'accepte que les entiers ou les rationnels");
	}

	if (t == INTEGER)
		s->push(number);
	else
		s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(number)->getValue().first));
}

void DenOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : DEN a besoin d'un argument");

	ILiteral* number = s->top(); s->pop();

	Type t = number->getType();

	if (t != INTEGER && t != RATIONAL) {
		s->push(number);
		throw OperatorException("Erreur : DEN n'accepte que les entiers ou les rationnels");
	}

	if (t == INTEGER)
		s->push(number);
	else
		s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(number)->getValue().second));
}

void $Op::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : $ a besoin de deux arguments");

	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	if ((lt != INTEGER && lt != REAL && lt != RATIONAL) || (rt != INTEGER && rt != REAL && rt != RATIONAL)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : $ ne prend que des entier, réel ou rationel");
	}

	s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<INumberLiteral*>(left), dynamic_cast<INumberLiteral*>(right)));
}

void ReOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : RE a besoin d'un argument");

	ILiteral* number = s->top(); s->pop();
	Type t = number->getType();

	if (t != INTEGER && t != RATIONAL && t != REAL && t != COMPLEX) {
		s->push(number);
		throw OperatorException("Erreur : RE n'accepte que les nombres (entier, réel, rationnel ou complexe)");
	}


	if (t == INTEGER || t == RATIONAL || t == REAL)
		s->push(number);
	else{
		Type t = dynamic_cast<ComplexLiteral*>(number)->Re().getType();
		switch (t){
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(&dynamic_cast<ComplexLiteral*>(number)->Re())->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(&dynamic_cast<ComplexLiteral*>(number)->Re())->getValue()));
			break;
		case RATIONAL:
			s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(&dynamic_cast<ComplexLiteral*>(number)->Re())->getValue()));
			break;
		}
	}
}

void ImOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : RE a besoin d'un argument");

	ILiteral* number = s->top(); s->pop();
	Type t = number->getType();

	if (t != INTEGER && t != RATIONAL && t != REAL && t != COMPLEX) {
		s->push(number);
		throw OperatorException("Erreur : RE n'accepte que les nombres (entier, réel, rationnel ou complexe)");
	}


	if (t == INTEGER || t == RATIONAL || t == REAL)
		s->push(number);
	else{
		Type t = dynamic_cast<ComplexLiteral*>(number)->Re().getType();
		switch (t){
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(&dynamic_cast<ComplexLiteral*>(number)->Im())->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(&dynamic_cast<ComplexLiteral*>(number)->Im())->getValue()));
			break;
		case RATIONAL:
			s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RationalLiteral*>(&dynamic_cast<ComplexLiteral*>(number)->Im())->getValue()));
			break;
		}
	}
}

void DupOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : DUP a besoin d'un argument");

	ILiteral* number = s->top(); s->push(number);
}

void DropOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : DropOp a besoin d'un argument");

	s->pop();
}

void SwapOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : SwapOp a besoin d'un argument");

	ILiteral* lit = s->top(); s->pop();
	ILiteral* lit2 = s->top(); s->pop();
	s->push(lit);
	s->push(lit2);
}

void ClearOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : ClearOp a besoin d'un argument");

	int size = s->size();
	for (int i = 0; i < size; i++)
		s->pop();
}

void EqualOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : = a besoin d'au moins deux arguments");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	ILiteral* left = s->top(); s->pop();
	Type lt = left->getType();

	if ((rt != INTEGER && rt != RATIONAL && rt != REAL && rt != COMPLEX) || (lt != INTEGER && lt != RATIONAL && lt != REAL && lt != COMPLEX)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : = ne prend que des nombres (complexe, entier, real ou rationel)");
	}

	if (rt != lt)
		s->push(new IntegerLiteral(0));
	else{
		switch (rt) {
		case INTEGER:
			s->push(new IntegerLiteral(dynamic_cast<IntegerLiteral*>(left)->getValue() == dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;

		case REAL:
			s->push(new IntegerLiteral(dynamic_cast<RealLiteral*>(left)->getValue() == dynamic_cast<RealLiteral*>(right)->getValue()));
			break;

		case RATIONAL:
			s->push(new IntegerLiteral(dynamic_cast<RationalLiteral*>(left)->getValue() == dynamic_cast<RationalLiteral*>(right)->getValue()));
			break;

		case COMPLEX:
			Type tRe = dynamic_cast<ComplexLiteral*>(left)->getTypeReal();
			Type tIm = dynamic_cast<ComplexLiteral*>(left)->getTypeIm();
			Type tRe2 = dynamic_cast<ComplexLiteral*>(right)->getTypeReal();
			Type tIm2 = dynamic_cast<ComplexLiteral*>(right)->getTypeIm();
			ComplexLiteral rComplex = *dynamic_cast<ComplexLiteral*>(right);
			ComplexLiteral lComplex = *dynamic_cast<ComplexLiteral*>(left);

			if (tRe != tRe2 || tIm != tIm2)
				s->push(new IntegerLiteral(0));
			else{
				switch (tRe){
				case INTEGER:
					switch (tIm) {
					case INTEGER:
						s->push(new IntegerLiteral(
							(dynamic_cast<IntegerLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<IntegerLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<IntegerLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<IntegerLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case REAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<IntegerLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<IntegerLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RealLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<RealLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case RATIONAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<IntegerLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<IntegerLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RationalLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<RationalLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					}
					break;

				case REAL:
					switch (tIm) {
					case INTEGER:
						s->push(new IntegerLiteral(
							(dynamic_cast<RealLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<RealLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<IntegerLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<IntegerLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case REAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<RealLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<RealLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RealLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<RealLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case RATIONAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<RealLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<RealLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RationalLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<RationalLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					}
					break;

				case RATIONAL:
					switch (tIm) {
					case INTEGER:
						s->push(new IntegerLiteral(
							(dynamic_cast<RationalLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<RationalLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<IntegerLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<IntegerLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case REAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<RationalLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<RationalLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RealLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<RealLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case RATIONAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<RationalLiteral*>(&rComplex.Re())->getValue() == dynamic_cast<RationalLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RationalLiteral*>(&rComplex.Im())->getValue() == dynamic_cast<RationalLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					}
					break;
				}
			}
			break;
		}
	}
}

void DifferentOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : != a besoin d'au moins deux arguments");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	ILiteral* left = s->top(); s->pop();
	Type lt = left->getType();

	if ((rt != INTEGER && rt != RATIONAL && rt != REAL && rt != COMPLEX) || (lt != INTEGER && lt != RATIONAL && lt != REAL && lt != COMPLEX)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : != ne prend que des nombres (complexe, entier, real ou rationel)");
	}

	if (rt != lt)
		s->push(new IntegerLiteral(1));
	else{
		switch (rt) {
		case INTEGER:
			s->push(new IntegerLiteral(dynamic_cast<IntegerLiteral*>(left)->getValue() != dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;

		case REAL:
			s->push(new IntegerLiteral(dynamic_cast<RealLiteral*>(left)->getValue() != dynamic_cast<RealLiteral*>(right)->getValue()));
			break;

		case RATIONAL:
			s->push(new IntegerLiteral(dynamic_cast<RationalLiteral*>(left)->getValue() != dynamic_cast<RationalLiteral*>(right)->getValue()));
			break;

		case COMPLEX:
			Type tRe = dynamic_cast<ComplexLiteral*>(left)->getTypeReal();
			Type tIm = dynamic_cast<ComplexLiteral*>(left)->getTypeIm();
			Type tRe2 = dynamic_cast<ComplexLiteral*>(right)->getTypeReal();
			Type tIm2 = dynamic_cast<ComplexLiteral*>(right)->getTypeIm();
			ComplexLiteral rComplex = *dynamic_cast<ComplexLiteral*>(right);
			ComplexLiteral lComplex = *dynamic_cast<ComplexLiteral*>(left);

			if (tRe != tRe2 || tIm != tIm2)
				s->push(new IntegerLiteral(1));
			else{
				switch (tRe){
				case INTEGER:
					switch (tIm) {
					case INTEGER:
						s->push(new IntegerLiteral(
							(dynamic_cast<IntegerLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<IntegerLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<IntegerLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<IntegerLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case REAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<IntegerLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<IntegerLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RealLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<RealLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case RATIONAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<IntegerLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<IntegerLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RationalLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<RationalLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					}
					break;

				case REAL:
					switch (tIm) {
					case INTEGER:
						s->push(new IntegerLiteral(
							(dynamic_cast<RealLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<RealLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<IntegerLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<IntegerLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case REAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<RealLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<RealLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RealLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<RealLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case RATIONAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<RealLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<RealLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RationalLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<RationalLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					}
					break;

				case RATIONAL:
					switch (tIm) {
					case INTEGER:
						s->push(new IntegerLiteral(
							(dynamic_cast<RationalLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<RationalLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<IntegerLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<IntegerLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case REAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<RationalLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<RationalLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RealLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<RealLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					case RATIONAL:
						s->push(new IntegerLiteral(
							(dynamic_cast<RationalLiteral*>(&rComplex.Re())->getValue() != dynamic_cast<RationalLiteral*>(&lComplex.Re())->getValue())
							&& (dynamic_cast<RationalLiteral*>(&rComplex.Im())->getValue() != dynamic_cast<RationalLiteral*>(&lComplex.Im())->getValue())
							));
						break;
					}
					break;
				}
			}
			break;
		}
	}
}

void InfEqOp::operator()(Stack* s) {
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : =< a besoin d'au moins deux arguments");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	ILiteral* left = s->top(); s->pop();
	Type lt = left->getType();

	if ((rt != INTEGER && rt != RATIONAL && rt != REAL) || (lt != INTEGER && lt != RATIONAL && lt != REAL)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : =< ne prend que des nombres (entier, réel ou rationelle)");
	}


	switch (lt) {
	case INTEGER:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() <= dynamic_cast<IntegerLiteral*>(right)->getValue())));
			break;
		case REAL:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() <= dynamic_cast<RealLiteral*>(right)->getValue())));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() <= ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second))));
			break;
		}
		break;

	case REAL:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() <= dynamic_cast<IntegerLiteral*>(right)->getValue())));
			break;
		case REAL:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() <= dynamic_cast<RealLiteral*>(right)->getValue())));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() <= ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second))));
			break;
		}
		break;

	case RATIONAL:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) <= dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) <= dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) <= ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second)));
			break;
		}
		break;
	}
}

void SupOp::operator()(Stack* s) {
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : > a besoin d'au moins deux arguments");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	ILiteral* left = s->top(); s->pop();
	Type lt = left->getType();

	if ((rt != INTEGER && rt != RATIONAL && rt != REAL) || (lt != INTEGER && lt != RATIONAL && lt != REAL)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : > ne prend que des nombres (entier, réel ou rationelle)");
	}


	switch (lt) {
	case INTEGER:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() > dynamic_cast<IntegerLiteral*>(right)->getValue())));
			break;
		case REAL:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() > dynamic_cast<RealLiteral*>(right)->getValue())));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() > ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second))));
			break;
		}
		break;

	case REAL:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() > dynamic_cast<IntegerLiteral*>(right)->getValue())));
			break;
		case REAL:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() > dynamic_cast<RealLiteral*>(right)->getValue())));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() > ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second))));
			break;
		}
		break;

	case RATIONAL:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) > dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) > dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) > ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second)));
			break;
		}
		break;
	}
}

void InfOp::operator()(Stack* s) {
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : < a besoin d'au moins deux arguments");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	ILiteral* left = s->top(); s->pop();
	Type lt = left->getType();

	if ((rt != INTEGER && rt != RATIONAL && rt != REAL) || (lt != INTEGER && lt != RATIONAL && lt != REAL)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : < ne prend que des nombres (entier, réel ou rationelle)");
	}


	switch (lt) {
	case INTEGER:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() < dynamic_cast<IntegerLiteral*>(right)->getValue())));
			break;
		case REAL:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() < dynamic_cast<RealLiteral*>(right)->getValue())));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() < ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second))));
			break;
		}
		break;

	case REAL:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() < dynamic_cast<IntegerLiteral*>(right)->getValue())));
			break;
		case REAL:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() < dynamic_cast<RealLiteral*>(right)->getValue())));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() < ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second))));
			break;
		}
		break;

	case RATIONAL:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) < dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) < dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) < ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second)));
			break;
		}
		break;
	}
}

void SupEqOp::operator()(Stack* s) {
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : >= a besoin d'au moins deux arguments");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	ILiteral* left = s->top(); s->pop();
	Type lt = left->getType();

	if ((rt != INTEGER && rt != RATIONAL && rt != REAL) || (lt != INTEGER && lt != RATIONAL && lt != REAL)) {
		s->push(left);
		s->push(right);
		throw OperatorException("Erreur : >= ne prend que des nombres (entier, réel ou rationelle)");
	}


	switch (lt) {
	case INTEGER:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() >= dynamic_cast<IntegerLiteral*>(right)->getValue())));
			break;
		case REAL:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() >= dynamic_cast<RealLiteral*>(right)->getValue())));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral((dynamic_cast<IntegerLiteral*>(left)->getValue() >= ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second))));
			break;
		}
		break;

	case REAL:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() >= dynamic_cast<IntegerLiteral*>(right)->getValue())));
			break;
		case REAL:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() >= dynamic_cast<RealLiteral*>(right)->getValue())));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral((dynamic_cast<RealLiteral*>(left)->getValue() >= ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second))));
			break;
		}
		break;

	case RATIONAL:
		switch (rt){
		case INTEGER:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) >= dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) >= dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			s->push(new IntegerLiteral(((double)dynamic_cast<RationalLiteral*>(left)->getValue().first / (double)dynamic_cast<RationalLiteral*>(left)->getValue().second) >= ((double)dynamic_cast<RationalLiteral*>(right)->getValue().first / (double)dynamic_cast<RationalLiteral*>(right)->getValue().second)));
			break;
		}
		break;
	}
}

void AndOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : AND a besoin d'au moins deux arguments");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	ILiteral* left = s->top(); s->pop();
	Type lt = left->getType();

	switch (rt){
	case INTEGER:
		if (dynamic_cast<IntegerLiteral*>(right)->isNul()){
			s->push(new IntegerLiteral(0));
			return;
		}
		break;

	case REAL:
		if (dynamic_cast<RealLiteral*>(right)->isNul()){
			s->push(new IntegerLiteral(0));
			return;
		}
		break;

	case RATIONAL:
		if (dynamic_cast<RationalLiteral*>(right)->isNul()){
			s->push(new IntegerLiteral(0));
			return;
		}
		break;

	case COMPLEX:
		if (dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->isNul()
			&& dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Im())->isNul()){
			s->push(new IntegerLiteral(0));
			return;
		}
		break;
	}

	switch (lt){
	case INTEGER:
		if (dynamic_cast<IntegerLiteral*>(left)->isNul()){
			s->push(new IntegerLiteral(0));
			return;
		}
		break;

	case REAL:
		if (dynamic_cast<RealLiteral*>(left)->isNul()){
			s->push(new IntegerLiteral(0));
			return;
		}
		break;

	case RATIONAL:
		if (dynamic_cast<RationalLiteral*>(left)->isNul()){
			s->push(new IntegerLiteral(0));
			return;
		}
		break;

	case COMPLEX:
		if (dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(left)->Re())->isNul()
			&& dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(left)->Im())->isNul()){
			s->push(new IntegerLiteral(0));
			return;
		}
		break;
	}

	s->push(new IntegerLiteral(1));
}

void OrOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : OR a besoin d'au moins deux arguments");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	ILiteral* left = s->top(); s->pop();
	Type lt = left->getType();

	int orBool = 0;

	switch (rt){
	case INTEGER:
		if (!dynamic_cast<IntegerLiteral*>(right)->isNul())
			orBool++;
		break;

	case REAL:
		if (!dynamic_cast<RealLiteral*>(right)->isNul())
			orBool++;
		break;

	case RATIONAL:
		if (!dynamic_cast<RationalLiteral*>(right)->isNul())
			orBool++;
		break;

	case COMPLEX:
		if (!dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->isNul()
			|| !dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Im())->isNul())
			orBool++;
		break;
	}

	switch (lt){
	case INTEGER:
		if (!dynamic_cast<IntegerLiteral*>(left)->isNul())
			orBool++;
		break;

	case REAL:
		if (!dynamic_cast<RealLiteral*>(left)->isNul())
			orBool++;
		break;

	case RATIONAL:
		if (!dynamic_cast<RationalLiteral*>(left)->isNul())
			orBool++;
		break;

	case COMPLEX:
		if (!dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(left)->Re())->isNul()
			|| !dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(left)->Im())->isNul())
			orBool++;
		break;
	}

	if (orBool == 0)
		s->push(new IntegerLiteral(0));
	else
		s->push(new IntegerLiteral(1));
}

void NotOp::operator()(Stack* s){
	if (s->size() < this->getArity())
		throw OperatorException("Erreur : AND a besoin d'au moins un argument");

	ILiteral* right = s->top(); s->pop();
	Type rt = right->getType();

	switch (rt){
	case INTEGER:
		if (dynamic_cast<IntegerLiteral*>(right)->isNul()){
			s->push(new IntegerLiteral(1));
		}
		break;

	case REAL:
		if (dynamic_cast<RealLiteral*>(right)->isNul()){
			s->push(new IntegerLiteral(1));
		}
		break;

	case RATIONAL:
		if (dynamic_cast<RationalLiteral*>(right)->isNul()){
			s->push(new IntegerLiteral(1));
		}
		break;

	case COMPLEX:
		if (dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Re())->isNul()
			&& dynamic_cast<INumberLiteral*>(&dynamic_cast<ComplexLiteral*>(right)->Im())->isNul()){
			s->push(new IntegerLiteral(1));
			return;
		}
		break;
	}
	s->push(new IntegerLiteral(1));
}

void UndoOp::operator()(Stack* s) {
	Controller::instance().undo();
}

void RedoOp::operator()(Stack* s) {
	Controller::instance().redo();
}

void EvalOp::operator()(Stack* s) {
	if(s->size() < this->getArity())
		throw OperatorException("Erreur : EVAL a besoin d'au moins un argument");

	ILiteral* arg = s->top(); s->pop();
	Type at = arg->getType();

	if(at != EXPRESSION)
		throw OperatorException("Erreur : l'argument d'EVAL doit être une expression");

	// shunting yard
	Stack rpnStack;

	std::queue<std::string> outputQueue;
	std::stack<std::string> operatorStack;

	std::string expr = dynamic_cast<ExpressionLiteral*>(arg)->getValue;

	while(!expr.empty()) { // tant qu'il reste des tokens
		std::string token;
		// check if token is a number
		char c = expr[0];
		expr.erase(0, 1);
		token += c;

		// If the token is a number, then add it to the output queue.
		if(std::isdigit(c)) {
			while(!expr.empty() && (c = expr.at(0)) && (std::isdigit(c) || c == decimal_sep)) {
				res += c;
				expr.erase(0, 1);
			}
		}
	}
		

}