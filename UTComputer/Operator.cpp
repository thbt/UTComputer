#include "Operator.h"
#include "LiteralFactory.h"

void PlusOp::interpret(Stack* s) {
	//enum Type { INTEGER, RATIONAL, REAL, COMPLEX, EXPRESSION, PROGRAM };
	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	pair<int, int> pairRa;
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
					s->push(LiteralFactory::getInstance().makeLiteral(new IntegerLiteral(doubleVal + dynamic_cast<IntegerLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(doubleVal + dynamic_cast<RealLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
					break;
				case RATIONAL:
					r = (float)dynamic_cast<RationalLiteral*>(pRe)->getValue().first / (float)dynamic_cast<RationalLiteral*>(pRe)->getValue().second;
					s->push(LiteralFactory::getInstance().makeLiteral(new RealLiteral(r+doubleVal),
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
				interpret(s);
			}
			else{
				s->push(pRe);
				s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
				interpret(s);
				ILiteral* partiReel = s->top(); s->pop();
				s->push(pIm);
				s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
				interpret(s);
				ILiteral* partiIm = s->top(); s->pop();
				t = partiReel->getType();
				if (t == INTEGER){
					t = partiIm->getType();
					switch (t){
					case INTEGER :
						s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<IntegerLiteral*>(partiIm)));
						break;
					case REAL :
						s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(partiReel), dynamic_cast<RealLiteral*>(partiIm)));
						break;
					case RATIONAL :
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

void MinusOp::interpret(Stack* s) {
	//enum Type { INTEGER, RATIONAL, REAL, COMPLEX, EXPRESSION, PROGRAM };
	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	pair<int, int> pairRa;
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
				s->push(LiteralFactory::getInstance().makeLiteral(new IntegerLiteral(doubleVal - dynamic_cast<IntegerLiteral*>(pRe)->getValue()), &dynamic_cast<ComplexLiteral*>(right)->Im()));
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
			interpret(s);
			ComplexLiteral* cmpI = dynamic_cast<ComplexLiteral*>(s->top()); s->pop();
			t = cmpI->Re().getType();
			switch (t) {
			case(INTEGER):
				s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<IntegerLiteral*>(LiteralFactory::getInstance().makeLiteral(-dynamic_cast<IntegerLiteral*>(&cmpI->Re())->getValue())), &cmpI->Im()));
				break;
			case(REAL) :
				s->push(LiteralFactory::getInstance().makeLiteral(dynamic_cast<RealLiteral*>(LiteralFactory::getInstance().makeLiteral(-dynamic_cast<RealLiteral*>(&cmpI->Re())->getValue())), &cmpI->Im()));
				break;
			case(RATIONAL) :
				pairRa = dynamic_cast<RationalLiteral*>(&cmpI->Re())->getValue();
				pairRa.first *= -1;
				s->push(LiteralFactory::getInstance().makeLiteral(new RationalLiteral(pairRa.first,pairRa.second), &cmpI->Im()));
				break;
			}
		}
		else{
			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			interpret(s);
			ILiteral* partiReel = s->top(); s->pop();
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			interpret(s);
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

void MultiOp::interpret(Stack* s) {
	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	pair<int, int> pairRa;
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
			interpret(s);
		}
		else{ //(aa' � bb') + i (ab' + ba')
			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			interpret(s);
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			interpret(s);
			MinusOp mop;
			mop.interpret(s);
			ILiteral* partiReel = s->top(); s->pop();

			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			interpret(s);
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			interpret(s);
			PlusOp pop;
			pop.interpret(s);
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

void DivOp::interpret(Stack* s){
	/*ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	pair<int, int> pairRa;
	INumberLiteral* pRe;
	INumberLiteral* pIm;
	int intVal;
	double doubleVal;
	double r;
	Type t, t2;

	INumberLiteral* INL1 = new IntegerLiteral(0);
	INumberLiteral* INL2 = new IntegerLiteral(0);

	switch (lt) { // � faire
	case INTEGER:
		intVal = dynamic_cast<IntegerLiteral*>(left)->getValue();
		switch (rt) {
		case INTEGER:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal / dynamic_cast<IntegerLiteral*>(right)->getValue()));
			break;
		case REAL:
			s->push(LiteralFactory::getInstance().makeLiteral(intVal / dynamic_cast<RealLiteral*>(right)->getValue()));
			break;
		case RATIONAL:
			pairRa.first = dynamic_cast<RationalLiteral*>(right)->getValue().second;
			pairRa.second = dynamic_cast<RationalLiteral*>(right)->getValue().first;
			s->push(LiteralFactory::getInstance().makeLiteral(pairRa));
			break;
		case COMPLEX: // x*(a-ib)/(a�+b�)
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
			interpret(s);
		}
		else{ //(aa' � bb') + i (ab' + ba')
			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			interpret(s);
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			interpret(s);
			MinusOp mop;
			mop.interpret(s);
			ILiteral* partiReel = s->top(); s->pop();

			s->push(pRe);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Im());
			interpret(s);
			s->push(pIm);
			s->push(&dynamic_cast<ComplexLiteral*>(right)->Re());
			interpret(s);
			PlusOp pop;
			pop.interpret(s);
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
	*/

}