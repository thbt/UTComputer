#include "LiteralFactory.h"

const LiteralFactory& LiteralFactory::getInstance() {
	static LiteralFactory instance;
	return instance;
}

ILiteral* LiteralFactory::makeLiteral(int n) const {
	return new IntegerLiteral(n);
}

ILiteral* LiteralFactory::makeLiteral(double n) const {
	if (floor(n) == n)
		return new IntegerLiteral((int)n);
	else
		return new RealLiteral(n);
}

ILiteral* LiteralFactory::makeLiteral(pair<int, int> n) const{
	RationalLiteral* R = new RationalLiteral(n.first, n.second);
	if (R->getValue().second == 1)
		return new IntegerLiteral(R->getValue().first);
	else
		return R;
}

ILiteral* LiteralFactory::makeLiteral(INumberLiteral* re, INumberLiteral* im) const{
	return new ComplexLiteral(re, im);
}