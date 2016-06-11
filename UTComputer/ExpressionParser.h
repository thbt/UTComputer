#pragma once
#include <string>

class ExpressionException {
	std::string info;
public:
	ExpressionException(const std::string& str) :info(str) {}
	std::string getInfo() const { return info; }
};

unsigned int precedence(char op);
std::string toRPN(std::string exp);
