#pragma once 

#include <string>

class OperatorException {
	std::string info;
public:
	OperatorException(const std::string& str) :info(str){}
	std::string getInfo() const { return info; }
};