#include "Operator.h"
#include "LiteralFactory.h"

void PlusOp::interpret(Stack* s) {
	//enum Type { INTEGER, RATIONAL, REAL, COMPLEX, EXPRESSION, PROGRAM };
	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	switch (lt) {
		case INTEGER:
			int lval = dynamic_cast<IntegerLiteral*>(left)->getValue();
			switch (rt) {
				case INTEGER:
					s->push(LiteralFactory::getInstance().makeLiteral(lval + dynamic_cast<IntegerLiteral*>(right)->getValue()));
					break;
				case REAL:
					s->push(LiteralFactory::getInstance().makeLiteral(lval + dynamic_cast<IntegerLiteral*>(right)->getValue()));
					break;
				case RATIONAL:
					pair<int, int> pairRational;
					pairRational.first = dynamic_cast<RationalLiteral*>(right)->getValue().first + lval;
					pairRational.second = dynamic_cast<RationalLiteral*>(right)->getValue().second;
					s->push(LiteralFactory::getInstance().makeLiteral(pairRational));
					break;
				/*case COMPLEX:


					break;*/
			}
			break;
	}
}
