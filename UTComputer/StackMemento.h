#pragma once

#include <vector>

#include "Literal.h"

/**
* Pattern Memento
* Originator = Stack : c'est l'objet dont on souhaite conserver les états au fur et a mesure de l'utilisation
* Memento = StackMemento : classe amie de l'originator, car c'est à l'originator de
*/
class StackMemento {
	friend class Stack;

	std::vector<ILiteral*> state;
	StackMemento() {};

	void setState(const std::vector<ILiteral*>& s); // deep copy
	std::vector<ILiteral*> getState() const { return state; }
public:
	~StackMemento();
};
