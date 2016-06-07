#include "Stack.h"

Stack::Stack(const Stack& s) {
	//std::vector<ILiteral*>* newStack = new std::vector<ILiteral*>(s.size());
	stack.clear();
	for(auto it = s.begin(); it != s.end(); it++)
		stack.push_back((*it)->clone());
}

void Stack::setMemento(StackMemento* m) {
	stack.clear();
	std::vector<ILiteral*> temp = m->getState();
	for(auto it = temp.begin(); it != temp.end(); it++)
		stack.push_back((*it)->clone());
}

Stack::~Stack() {
	stack.erase(stack.begin(), stack.begin() + stack.size());
}