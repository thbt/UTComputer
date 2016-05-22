#include "Literal.h"
#include <string>
#include <sstream>

string NumberLiteral::toString() const {
	std::stringstream ss;

	switch(type) {
	case integer:
		ss << (int) reNum;
		break;
	case rational:
		ss << (int) reNum << "/" << (int) reDen;
		break;
	case real:
		ss << reNum;
		break;
	case complex:
		if(floor(reNum) == reNum) {
			ss << (int) reNum;
			if(reDen != 1) ss << "/" << (int) reDen;
		} else ss << reNum;

		ss << "$";

		if(floor(imNum) == imNum) {
			ss << (int) imNum;
			if(imDen != 1) ss << "/" << (int) imDen;
		} else ss << imNum;
	}

	return ss.str();
};