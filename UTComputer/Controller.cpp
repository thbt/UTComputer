//
//  Controller.cpp
//  UTComputer
//
//  Created by Thibaut Roy on 06/06/16.
//  Copyright © 2016 tyrius. All rights reserved.
//

#include <sstream>
#include <algorithm>

#include "Controller.h"
#include "LiteralFactory.h"
#include "OperatorException.h"
#include <iostream>

#include <fstream>
#include <string>

#include <direct.h>
#define GetCurrentDir _getcwd


Controller& Controller::instance() {
    static Controller instance;
    return instance;
}

Controller::Controller() : stack(), NumberDisplay(5) {
    // on stocke les functors
    dispatcher.emplace("+", PlusOp());
    dispatcher.emplace("-", MinusOp());
    dispatcher.emplace("*", MultiOp());
    dispatcher.emplace("/", DivOp());
    dispatcher.emplace("DIV", DivEntOp());
    dispatcher.emplace("MOD", ModulOp());
    dispatcher.emplace("NEG", NegOp());
    dispatcher.emplace("NUM", NumOp());
    dispatcher.emplace("DEN", DenOp());
    dispatcher.emplace("$", $Op());
    dispatcher.emplace("RE", ReOp());
    dispatcher.emplace("IM", ImOp());
    dispatcher.emplace("DUP", DupOp());
    dispatcher.emplace("DROP", DropOp());
    dispatcher.emplace("SWAP", SwapOp());
    dispatcher.emplace("CLEAR", ClearOp());
    dispatcher.emplace("EQUAL", EqualOp());
	dispatcher.emplace("=", EqualOp());
    dispatcher.emplace("!=", DifferentOp());
    dispatcher.emplace("<=", InfEqOp());
    dispatcher.emplace("<", InfOp());
    dispatcher.emplace(">", SupOp());
    dispatcher.emplace(">=", SupEqOp());
    dispatcher.emplace("AND", AndOp());
    dispatcher.emplace("OR", OrOp());
    dispatcher.emplace("NOT", NotOp());
    dispatcher.emplace("UNDO", UndoOp());
    dispatcher.emplace("REDO", RedoOp());

	// variables de test
	vars.emplace("X", new IntegerLiteral(5));
	vars.emplace("V1", new RealLiteral(2.0));
}

void Controller::execute(std::string op) {
	// Controle l'existence de la commande
	if(dispatcher.find(op) == dispatcher.end())
		throw OperatorException("L'opérateur n'existe pas.");
	else {
		// On effectue une opération sur la stack -> on sauvegarde l'état
		if(op != "UNDO" && op != "REDO")
			undoStack.push(stack.createMemento());
		dispatcher[op](&stack);
	}
}

void Controller::undo() {
	if(undoStack.empty())
		throw OperatorException("Il n'y a rien a undo");
	else {
		redoStack.push(stack.createMemento());
		stack.setMemento(undoStack.top());
		undoStack.pop(); // pop la dernière opération
	}
}

void Controller::redo() {
	if(redoStack.empty())
		throw OperatorException("Il n'y a rien a redo");
	else {
		undoStack.push(stack.createMemento());
		stack.setMemento(redoStack.top());
		redoStack.pop();
	}
}

void Controller::command(const std::string& str) {
    // 1. Tokenizer
    std::stringstream ss(str); // string to stream
    std::string item;
    std::vector<std::string> tokens;
    std::string newToken = "";
    while(getline(ss, item, ' ')) {
        if(item[0] == '`') {
            newToken += item;
            if(item.back() == '`') {
                tokens.push_back(newToken);
                newToken = "";
            }
        } else if(item[0] == '[' || newToken[0] == '[') {
            newToken = newToken + item + ' ';
            if(item.back() == ']') {
                tokens.push_back(newToken);
                newToken = "";
            }
        } else
            tokens.push_back(item);
    }

    std::cout << "affichage tokens :" << std::endl;
    for(auto it = tokens.begin(); it != tokens.end(); it++) {
        std::cout << *it << std::endl;
    }

    // 2. Syntactic analysis
    // TODO try catch pour l'instanciation des littéraux
    for(std::string& t : tokens) {
		if (t[0] == '[' || t[0] == '`' || t[0] == '.' || (t[0] >= '0' && t[0] <= '9')) { // Check if the token is a value (number/complex/expression/program)
			stack.push(LiteralFactory::getInstance().makeLiteral(t));
			changeState();
		}
		else if (t[0] == '-' && t.length() > 1) { // special case : negative number
			stack.push(LiteralFactory::getInstance().makeLiteral(t));
			changeState();
		}
        else {// otherwise the token is an operator
            try {
				transform(t.begin(), t.end(), t.begin(), ::toupper);
                execute(t);
				
				changeState();
            } catch(OperatorException oe) {
                showError(oe.getInfo());
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

unsigned int Controller::getNbDisplay() const{
    return NumberDisplay;
}
void Controller::setNbDisplay(unsigned int nb){
    NumberDisplay = nb;
}

std::vector<std::string> Controller::getOperators() {
	std::vector<std::string> v;
	for(auto it = dispatcher.begin(); it != dispatcher.end(); ++it)
		v.push_back(it->first);
	return v;
}

void Controller::createAtome(std::string nom, std::string value) {
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return;
	}
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
	std::string str(cCurrentPath);
	std::string tmp = str + "\\SaveFiles\\temp.txt";
	std::ofstream temp(tmp);

	if (value[0] == '[') 
		str += "\\SaveFiles\\fonction.txt";
	else 
		str += "\\SaveFiles\\variable.txt";

	std::ifstream monFlux(str, std::ios_base::app);
	
	std::string line;

	while (std::getline(monFlux, line))
	{
		if (line.compare(0, nom.size(), nom)!=0)
		{
			temp << line << std::endl;
		}
	}


	temp << nom << "|" << value << std::endl;

	temp.close();
	monFlux.close();
	remove(str.c_str());
	rename(tmp.c_str(), str.c_str());

}