#include "Operator.h"

void PlusOp::interpret(Stack* s) {
	ILiteral* right = s->top(); s->pop();
	ILiteral* left = s->top(); s->pop();


}