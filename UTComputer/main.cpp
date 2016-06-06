#include <string>
#include <iostream>
#include <istream>
#include <vector>
#include <ostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <map>
#include <functional> // for std::function

#include "Literal.h"
#include "Stack.h"
#include "Operator.h"
#include "OperatorException.h"
#include "LiteralFactory.h"


std::vector<std::string> split(const std::string& str) {
	std::stringstream ss(str); // string to stream
	
	std::string item;
	std::vector<std::string> tokens;
	
	while(getline(ss, item, ' '))
		tokens.push_back(item);
	
	return tokens;
}

void parser(std::string rpnexpr, Stack* s) {
	// a ranger ailleurs (pas la peine de la completer pour l'instant ça suffira pour tester)
	std::map<std::string, std::function<void(Stack*)>> dispatcher;
	dispatcher.emplace("+", PlusOp());
	dispatcher.emplace("-", MinusOp());
	dispatcher.emplace("*", MultiOp());
	
	// 1. Tokenizer
	// TODO Générer les bons tokens pour les programmes et les expressions
	std::vector<std::string> tokens = split(rpnexpr);
	// 2. Syntactic analysis
	// TODO try catch pour l'instanciation des littéraux
	for(std::string const& t: tokens) {
		if(t[0] == '[' || t[0] == '`' || t[0] == '.' || (t[0] >= '0' && t[0] <= '9')) // Check if the token is a value (number/complex/expression/program)
			s->push(LiteralFactory::getInstance().makeLiteral(t));
		else if(t[0] == '-' && t.length() > 1) // special case : negative number
			s->push(LiteralFactory::getInstance().makeLiteral(t));
		else {// otherwise the token is an operator
			try {
				dispatcher[t](s);
			} catch (OperatorException oe) {
				std::cerr << oe.getInfo() << std::endl; // prob not enough values in stack
			}
		}
		
		// pour debugger
		std::cout << "affichage stack :" << std::endl;
		for(auto it = s->begin(); it != s->end(); it++) {
			std::cout << (*it)->toString() << std::endl;
		}
	}
}

int main() {
	IntegerLiteral n1(0);
	RealLiteral n2(4.5);
	RationalLiteral n3(0,1);
	ComplexLiteral n4(new RealLiteral(0), new IntegerLiteral(0));
	IntegerLiteral n5(10);
	IntegerLiteral n6(5);
	ComplexLiteral n7(new RationalLiteral(0,1), new RationalLiteral(0,3));
	RationalLiteral n8(4, 2);
	
	// TODO singleton pour la stack ??
	Stack s;
	std::string rpn = "2 2 + 3 * 5 -";
	parser(rpn,&s);
	//s.push(&n3);
	//s.push(&n8);
	
	//s.push(&n1);
	//s.push(&n3);
	
	//s.push(&n1);
	//s.push(&n5);
	//s.push(&n6);
	//s.push(&n2);
	
	try {
	} catch (OperatorException oe){
		std::cerr << oe.getInfo() << std::endl;
	}

	std::cout << "affichage stack :" << std::endl;
	for(auto it = s.begin(); it != s.end(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
	
	system("pause");
	return 0;
}