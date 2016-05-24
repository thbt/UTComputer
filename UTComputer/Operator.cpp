#include "Operator.h"
#include "LiteralFactory.h"

void PlusOp::interpret(Stack* s) {
	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();

	Type lt = left->getType();
	Type rt = right->getType();
	
	if(lt == INTEGER && rt == INTEGER) {
		int n = dynamic_cast<IntegerLiteral*>(right)->getValue() + dynamic_cast<IntegerLiteral*>(left)->getValue();
		s->push(LiteralFactory::getInstance().makeLiteral(n));
	}
}
