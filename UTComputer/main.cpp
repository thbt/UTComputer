#include <iostream>
#include "Literal.h"
#include "Stack.h"
#include "Operator.h"
#include "OperatorException.h"

int main() {
	IntegerLiteral n1(0);
	RealLiteral n2(4.5);
	RationalLiteral n3(10, 3);
	ComplexLiteral n4(new RealLiteral(10.5), new IntegerLiteral(10));
	IntegerLiteral n5(10);
	IntegerLiteral n6(5);
	ComplexLiteral n7(new RationalLiteral(0,1), new RationalLiteral(0,3));
	RationalLiteral n8(4, 2);

	Stack s;
	s.push(&n3);
	s.push(&n4);

	//s.push(&n1);
	//s.push(&n3);

	//s.push(&n1);
	//s.push(&n5);
	//s.push(&n6);
	//s.push(&n2);
	
	std::cout << "affichage stack :" << std::endl;
	for(auto it = s.begin(); it != s.end(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
	try{
		//PlusOp po;
		//po.interpret(&s);

		//MinusOp mo;
		//mo.interpret(&s);

		//MultiOp muo;
		//muo.interpret(&s);

		//DivOp divo;
		//divo.interpret(&s);

		//DivEntOp deo;
		//deo.interpret(&s);

		//ModulOp modulo;
		//modulo.interpret(&s);

		//NegOp nop;
		//nop.interpret(&s);

		//NumOp numop;
		//numop.interpret(&s);

		//$Op $op;
		//$op.interpret(&s);

		//ReOp reOp;
		//reOp.interpret(&s);

		//DupOp duop;
		//duop.interpret(&s);

		//DropOp drop;
		//drop.interpret(&s);

		//SwapOp swap;
		//swap.interpret(&s);

		ClearOp clear;
		clear.interpret(&s);
	}
	catch (OperatorException oe){
		cerr << oe.getInfo() << endl;
	}

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