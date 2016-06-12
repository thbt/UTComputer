//
//  Controller.cpp
//  UTComputer
//
//  Created by Thibaut Roy on 06/06/16.
//  Copyright © 2016 tyrius. All rights reserved.
//

#include <sstream>
#include <algorithm>
#include <fstream>

#include "Controller.h"
#include "LiteralFactory.h"
#include "OperatorException.h"
#include "ParserException.h"
#include <iostream>

const std::string pathVar = "SaveFiles/variable.txt";
const std::string pathFct = "SaveFiles/fonction.txt";

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
	dispatcher.emplace("IFT", IftOp());
	dispatcher.emplace("EVAL", EvalOp());
	dispatcher.emplace("STO", StoOp());
	dispatcher.emplace("FORGET", ForgetOp());
	dispatcher.emplace("EDIT", EditOp());

	initAtome();
}

void Controller::execute(std::string op) {
	// Controle l'existence de la commande
	if(dispatcher.find(op) == dispatcher.end())
		throw OperatorException("L'operateur n'existe pas.");
	else {
		// On effectue une operation sur la stack -> on sauvegarde l'etat
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
		undoStack.pop(); // pop la derniere operation
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
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> tokens;
    std::string newToken = "";

	unsigned int nestedProgCounter = 0;
	bool inExpression = false;

    while(getline(ss, item, ' ')) {
		if(inExpression) {
			newToken += item;
			if(item.back() == '`') {
				inExpression = false;
				tokens.push_back(newToken);
				newToken = "";
			}
		} else if(nestedProgCounter > 0) {
			newToken += item;

			if(item[0] == '[') nestedProgCounter++;

			if(item.back() == ']') {
				nestedProgCounter--;
				if(nestedProgCounter == 0) {
					tokens.push_back(newToken);
					newToken = "";
				}
			} else {
				newToken += ' ';
			}
		} else {
			if(item[0] == '`') {
				newToken += item;
				if(item.back() == '`') {
					tokens.push_back(newToken);
					newToken = "";
				} else 
					inExpression = true;
			} else if(item[0] == '[' || newToken[0] == '[') {
				newToken += item;
				if(item.back() == ']') {
					tokens.push_back(newToken);
					newToken = "";
				} else {
					newToken += ' ';
					nestedProgCounter++;
				}
			} else
				tokens.push_back(item);
		}
    }

    std::cout << "affichage tokens :" << std::endl;
    for(auto it = tokens.begin(); it != tokens.end(); it++) {
        std::cout << *it << std::endl;
    }

    // 2. Syntactic analysis
    
    for(std::string& t : tokens) {
		transform(t.begin(), t.end(), t.begin(), ::toupper);
		if (t[0] == '[' || t[0] == '`' || t[0] == '.' || (t[0] >= '0' && t[0] <= '9')) { // Check if the token is a value (number/complex/expression/program)
			stack.push(LiteralFactory::getInstance().makeLiteral(t)); // TODO try catch pour l'instanciation des litteraux
			changeState();
		}
		else if (t[0] == '-' && t.length() > 1) { // special case : negative number
			stack.push(LiteralFactory::getInstance().makeLiteral(t));
			changeState();
		}
        else {
			std::vector<std::string> opList = getOperators();

			std::vector<std::string> varList;
			for(auto it = variables.begin(); it != variables.end(); ++it)
				varList.push_back(it->first);
			
			std::vector<std::string> progList;
			for(auto it = programs.begin(); it != programs.end(); ++it)
				progList.push_back(it->first);
			
			if(std::find(opList.begin(), opList.end(), t) != opList.end()) { // token is an operator
				try {
					execute(t);
					changeState();
				} catch(OperatorException oe) {
					showError(oe.getInfo());
					std::cerr << oe.getInfo() << std::endl;
				} catch(ParserException pe) {
					showError(pe.getInfo());
					std::cerr << pe.getInfo() << std::endl;
				}
			} else if(std::find(varList.begin(), varList.end(), t) != varList.end()) { // token is a variable
				stack.push(LiteralFactory::getInstance().makeLiteral(variables[t])); // TODO try catch pour l'instanciation des litteraux
				changeState();
			} else if(std::find(progList.begin(), progList.end(), t) != progList.end()) { // token is a program
				command(programs[t].substr(1, programs[t].size() - 2));
			} else {
				stack.push(LiteralFactory::getInstance().makeLiteral("`" + t + "`"));
				changeState();
			}
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

void Controller::createAtome(std::string name, std::string value) {
	if(dispatcher.find(name) != dispatcher.end())
		throw OperatorException("Erreur : nom interdit, un opérateur possède déjà le nom : " + name);

	if(variables.find(name) != variables.end())
		throw OperatorException("Erreur : nom interdit, une variable possède déjà le nom : " + name);

	if(programs.find(name) != programs.end())
		throw OperatorException("Erreur : nom interdit, un programme possède déjà le nom : " + name);

	if (value[0] == '[')
		programs[name] = value;
	else
		variables[name] = value;
	changeVarFct();
}

void Controller::initAtome() {
	std::ifstream monFluxVar(pathVar, std::ios_base::app);
	std::ifstream monFluxProg(pathFct, std::ios_base::app);

	std::string line;
	std::string delimiter = "|";

	while (std::getline(monFluxVar, line))
	{
		variables[line.substr(0, line.find(delimiter))] = line.substr(line.find(delimiter) + 1, line.length());
	}

	while (std::getline(monFluxProg, line))
	{
		programs[line.substr(0, line.find(delimiter))] = line.substr(line.find(delimiter) + 1, line.length());
	}
}

void Controller::saveAtome() {
	std::ofstream monFluxVar(pathVar);
	std::ofstream monFluxFct(pathFct);

	for (std::map<std::string, std::string>::iterator iter = variables.begin(); iter != variables.end(); ++iter) {
		monFluxVar << iter->first << "|" << iter->second << std::endl;
	}

	for (std::map<std::string, std::string>::iterator iter = programs.begin(); iter != programs.end(); ++iter) {
		monFluxFct << iter->first << "|" << iter->second << std::endl;
	}
}

std::map<std::string, std::string> Controller::getVariables() {
	return variables;
}

std::map<std::string, std::string> Controller::getPrograms() {
	return programs;
}

void Controller::deleteAtome(std::string name) {
	std::map<std::string, std::string>::iterator it;

	it = programs.find(name);
	if (it != programs.end()){
		programs.erase(it);
	} else {
		it = variables.find(name);
		if(it != variables.end())
			variables.erase(it);
		else {
			std::stringstream ss;
			ss << "La variable " << name << " n'existe pas";
			throw OperatorException(ss.str());
		}
	}
	changeVarFct();
}

void Controller::editAtom(std::string name) {
	std::map<std::string, std::string>::iterator it;

	it = programs.find(name);
	if(it != programs.end()) {
		editProg(name);
	} else {
		it = variables.find(name);
		if(it != variables.end())
			editVar(name);
		else {
			std::stringstream ss;
			ss << "La variable " << name << " n'existe pas";
			throw OperatorException(ss.str());
		}	
	}
	changeVarFct();
}

std::string Controller::getPathVar() { return pathVar; };
std::string Controller::getPathProg() { return pathFct; };