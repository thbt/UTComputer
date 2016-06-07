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

Controller& Controller::instance() {
    static Controller instance;
    return instance;
}

Controller::Controller() : NumberDisplay(4) {
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
    dispatcher.emplace("!=", DifferentOp());
    dispatcher.emplace("=<", InfEqOp());
    dispatcher.emplace("<", InfOp());
    dispatcher.emplace(">", SupOp());
    dispatcher.emplace(">=", SupEqOp());
    dispatcher.emplace("AND", AndOp());
    dispatcher.emplace("OR", OrOp());
    dispatcher.emplace("NOT", NotOp());
    dispatcher.emplace("UNDO", UndoOp());
    dispatcher.emplace("REDO", RedoOp());
}

// TODO throw exception si l'opération n'existe pas
void Controller::execute(std::string op) {
    // On effectue une opération sur la stack -> on sauvegarde l'état
    undoStack.push(stack.createMemento());
    dispatcher[op](&stack);
}

// TODO throw exception si rien a pop
void Controller::undo() {
    undoStack.pop(); // pop la dernière opération
    redoStack.push(stack.createMemento());
    stack.setMemento(undoStack.top());
    undoStack.pop(); // pop le undo de la stack
}

// TODO throw exception si rien a pop
void Controller::redo() {
    undoStack.pop(); // pop le undo de la stack
    stack.setMemento(redoStack.top());
    undoStack.push(stack.createMemento());
    redoStack.pop();
}

void Controller::command(const std::string& str) {
    // 1. Tokenizer
    // TODO Générer les bons tokens pour les programmes et les expressions
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
    for(std::string const& t : tokens) {
        if(t[0] == '[' || t[0] == '`' || t[0] == '.' || (t[0] >= '0' && t[0] <= '9')) // Check if the token is a value (number/complex/expression/program)
            stack.push(LiteralFactory::getInstance().makeLiteral(t));
        else if(t[0] == '-' && t.length() > 1) // special case : negative number
            stack.push(LiteralFactory::getInstance().makeLiteral(t));
        else {// otherwise the token is an operator
            try {
                execute(t);
            } catch(OperatorException oe) {
                showError(oe.getInfo());
                //std::cerr << oe.getInfo() << std::endl; // prob not enough values in stack
            }
        }

        // TODO a supprimer (uniquement pour debugger
        //std::cout << "affichage stack :" << std::endl;
        //for(auto it = stack.begin(); it != stack.end(); it++) {
        //	std::cout << (*it)->toString() << std::endl;
        //}
    }
    changeState();
}

unsigned int Controller::getNbDisplay() const{
    return NumberDisplay;
}
void Controller::setNbDisplay(unsigned int nb){
    NumberDisplay = nb;
}

