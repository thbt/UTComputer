#include "LiteralFactory.h"

const LiteralFactory& LiteralFactory::getInstance() {
	static LiteralFactory instance;
	return instance;
}

ILiteral* LiteralFactory::makeLiteral(int n) const {
	return new IntegerLiteral(n);
}

ILiteral* LiteralFactory::makeLiteral(double n) const {
	return new RealLiteral(n);
}

ILiteral* LiteralFactory::makeLiteral(pair<int, int> n) const{
	return new RationalLiteral(n.first, n.second);
}

ILiteral* LiteralFactory::makeLiteral(INumberLiteral* re, INumberLiteral* im) const{
	return new ComplexLiteral(re, im);
}