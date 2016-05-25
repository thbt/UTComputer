#include "Operator.h"
#include "LiteralFactory.h"

void PlusOp::interpret(Stack* s) {
	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();

	switch(lt) {
	case INTEGER:
		int lval = dynamic_cast<IntegerLiteral*>(left)->getValue();
		switch(rt) {
		case INTEGER:
			int rval = dynamic_cast<IntegerLiteral*>(right)->getValue();
			int n = lval + rval;
			s->push(LiteralFactory::getInstance().makeLiteral(n));
		case REAL:
			double rval = dynamic_cast<RealLiteral*>(right)->getValue();
		}
		break;

	}
}
