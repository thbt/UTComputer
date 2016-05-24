#include "LiteralFactory.h"

const LiteralFactory& LiteralFactory::getInstance() {
	static LiteralFactory instance;
	return instance;
}

ILiteral* LiteralFactory::makeLiteral(int n) const {
	return new IntegerLiteral(n);
}