#include "LiteralFactory.h"
#include <math.h>
#include <algorithm>

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

ILiteral* LiteralFactory::makeLiteral(std::pair<int, int> n) const{
	if (n.second == 1)
		return new IntegerLiteral(n.first);
	else
		return new RationalLiteral(n.first, n.second);
}

ILiteral* LiteralFactory::makeLiteral(INumberLiteral* re, INumberLiteral* im) const{
	return new ComplexLiteral(re, im);
}

INumberLiteral* LiteralFactory::makeNumberLiteral(std::string str) const {
	if(str.find('/') != std::string::npos) {
		size_t pos = str.find('/');
		int num = std::stoi(str.substr(0, pos));
		int den = std::stoi(str.substr(pos + 1, str.length()));
		
		return new RationalLiteral(num,den);
	} else if(str.find('.') != std::string::npos) {
		return new RealLiteral(std::stod(str));
	} else {
		return new IntegerLiteral(std::stoi(str));
	}
}

ILiteral* LiteralFactory::makeLiteral(std::string str) const {
	if(str[0] == '[')
		return new ProgramLiteral(str);
	else if(str[0] == '`')
		return new ExpressionLiteral(str);
	else if(str.find('$') != std::string::npos) {
		size_t pos = str.find('$');
		INumberLiteral* re = makeNumberLiteral(str.substr(0, pos));
		INumberLiteral* im = makeNumberLiteral(str.substr(pos + 1, str.length()));
		return new ComplexLiteral(re, im);
	} else
		return makeNumberLiteral(str);
}