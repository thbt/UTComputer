#include "Stack.h"

Stack* Stack::Instance() {
	if(instance == nullptr)
		instance = new Stack;

	return instance;
}