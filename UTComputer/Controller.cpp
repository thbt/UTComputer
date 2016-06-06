//
//  Controller.cpp
//  UTComputer
//
//  Created by Thibaut Roy on 06/06/16.
//  Copyright © 2016 tyrius. All rights reserved.
//

#include <sstream>

#include "Controller.h"
#include "LiteralFactory.h"
#include "OperatorException.h"

Controller::Controller(Stack& s) : stack(s) {
	dispatcher.emplace("+", PlusOp());
	dispatcher.emplace("-", MinusOp());
	dispatcher.emplace("*", MultiOp());
}

void Controller::command(const std::string& str) {
	// 1. Tokenizer
	// TODO Générer les bons tokens pour les programmes et les expressions
	std::stringstream ss(str); // string to stream
	std::string item;
	std::vector<std::string> tokens;
	while(getline(ss, item, ' '))
		tokens.push_back(item);

	// 2. Syntactic analysis
	// TODO try catch pour l'instanciation des littéraux
	for(std::string const& t : tokens) {
		if(t[0] == '[' || t[0] == '`' || t[0] == '.' || (t[0] >= '0' && t[0] <= '9')) // Check if the token is a value (number/complex/expression/program)
			stack.push(LiteralFactory::getInstance().makeLiteral(t));
		else if(t[0] == '-' && t.length() > 1) // special case : negative number
			stack.push(LiteralFactory::getInstance().makeLiteral(t));
		else {// otherwise the token is an operator
			try {
				dispatcher[t](&stack);
			} catch(OperatorException oe) {
				std::cerr << oe.getInfo() << std::endl; // prob not enough values in stack
			}
		}

		// TODO a supprimer (uniquement pour debugger
		std::cout << "affichage stack :" << std::endl;
		for(auto it = stack.begin(); it != stack.end(); it++) {
			std::cout << (*it)->toString() << std::endl;
		}
	}
}
