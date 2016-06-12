#include "ExpressionParser.h"

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <algorithm>    // std::find

#include "Operator.h"
#include "OperatorException.h"
#include "Controller.h"
#include "ParserException.h"

unsigned int precedence(char op) {
    switch(op) {
    case '-': case '+':
        return 1;
    case '*': case '/':
        return 2;
    default:
        return 0;
    }
}

std::string toRPN(std::string exp) {
    std::string output;
    std::stack<std::string> operators;
    std::string symbols = "+*-/";

    std::vector<std::string> availableFunctions;
    availableFunctions.push_back("+");
    availableFunctions.push_back("-");


    while(!exp.empty()) {
        // TODO parcourir la string pour remplacer les - unaire par des n (pour marquer la négation)

        char c = exp[0];
        exp.erase(0, 1);

        std::string token;
        token += c;

        // TODO : regarder si y a [, alors throw


        // 1. Si c'est un nombre on l'ajoute dans la file
        if(std::isdigit(c)) {
            // On récupère la suite du nombre
            while(!exp.empty() && (c = exp[0]) && (std::isdigit(c) || c == '.' || c == '$')) {
                token += c;
                exp.erase(0, 1);
            }
            output.append(token + ' ');
            // 2. Si c'est un op�rateur
        } else if(symbols.find(c) != std::string::npos) {
            // while there is an operator token at the top of the operator stack
            while(!operators.empty() && (precedence(c) <= precedence(operators.top()[0]))) {
                //pop o2 off the operator stack, onto the output queue;
                output.append(operators.top() + ' ');
                operators.pop();
            }
            // at the end of iteration push o1 onto the operator stack.
            operators.push(token);
            //4. If the token is a left parenthesis '(', then push it onto the stack
        } else if(c == '(') {
            operators.push(token);
            // 5. If the token is a right parenthesis ')'
        } else if(c == ')') {
            // Until the token at the top of the stack is a left parenthesis, pop operators off the stack onto the output queue.
            while(!operators.empty() && operators.top() != "(") {
                output.append(operators.top() + ' ');
                operators.pop();
            }
            if(operators.empty() || operators.top() != "(")
                throw ParserException("Parenthèses dépareillées.");

            // Pop the left parenthesis from the stack, but not onto the output queue.
            operators.pop();
            // If the token at the top of the stack is a function token, pop it onto the output queue.
            if(!operators.empty()) {
                std::string fun = operators.top();
                if(fun != "(") {
					if(std::find(availableFunctions.begin(), availableFunctions.end(), operators.top()) != availableFunctions.end()) {
						output.append(fun + ' ');
						operators.pop();
					} else {
						std::string str = "Pas d'opérateurs disponibles avec le nom : '" + fun + "'";
						throw ParserException(str);
					}
                }
            }
            // 3. Sinon c'est une fonction (ou une variable)
        } else {
            while(!exp.empty() && (c = exp[0]) && (std::isalpha(c) || std::isdigit(c))) {
                token += c;
                exp.erase(0, 1);
            }
            operators.push(token);
        }
    }
    while(!operators.empty()) {
        if(operators.top() == "(" || operators.top() == ")")
            throw ParserException("Parenthèses dépareillées");
        else {
            output.append(operators.top() + ' ');
            operators.pop();
        }
    }

    std::cout << output << std::endl;
    return output;
}
