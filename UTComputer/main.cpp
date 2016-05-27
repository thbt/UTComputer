#include <iostream>
#include "Literal.h"
#include "Stack.h"
#include "Operator.h"

int main() {
	
	IntegerLiteral n1(4);
	RealLiteral n2(1.7);
	RationalLiteral n3(-5, 2);
	ComplexLiteral n4(new RationalLiteral(-5,2), new RationalLiteral(-3, 4));
	IntegerLiteral n5(2);
	IntegerLiteral n6(3);
	ComplexLiteral n7(new IntegerLiteral(4), new RealLiteral(1.75));
	
	/*
	NumberLiteral n1(1);
	NumberLiteral n2(2.5, real);
	NumberLiteral n3(3, rational, 4);
	NumberLiteral n4(5, complex, 1.0, 2.5); // TODO Comment gérer les complexes
	*/
	Stack s;
	s.push(&n4);
	//s.push(&n1);
	//s.push(&n5);
	//s.push(&n6);
	//s.push(&n2);
	s.push(&n7);
	
	std::cout << "affichage stack :" << std::endl;
	for(auto it = s.begin(); it != s.end(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
	
	PlusOp po;
	po.interpret(&s);

	std::cout << "affichage stack :" << std::endl;
	for(auto it = s.begin(); it != s.end(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
	
	/*
	po.interpret(&s);

	std::cout << "affichage stack :" << std::endl;
	for (auto it = s.begin(); it != s.end(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
	
	po.interpret(&s);

	std::cout << "affichage stack :" << std::endl;
	for (auto it = s.begin(); it != s.end(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
	*/
	system("pause");
	return 0;
}