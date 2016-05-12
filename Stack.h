#pragma once

#include <iostream>
#include <iostream>
#include <stack>

#include "Literal.h"

using namespace std;

class Stack : public QObject {
	Q_OBJECT

	static Stack* instance;

	stack<ILiteral*> stack;

	string message;
	unsigned int nbToPrint;
protected:
	Stack() : message("Bienvenue !"), nbToPrint(4) {}
public:
	static Stack* Instance();
	static void freeInstance();

	void push(ILiteral* e);
	void pop();
	ILiteral* top() const;
	bool isEmpty() const { return stack.empty(); }
	unsigned int size() const { return stack.size(); }

	unsigned int getNbToPrint() const { return nbToPrint; }
signals:
	void update();
};