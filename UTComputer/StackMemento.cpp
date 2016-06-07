#include "StackMemento.h"

void StackMemento::setState(const std::vector<ILiteral*>& s) {
	for(auto it = s.begin(); it != s.end(); it++)
		state.push_back((*it)->clone());
}

StackMemento::~StackMemento() {
	state.erase(state.begin(), state.begin() + state.size());
}