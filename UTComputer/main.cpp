#include <iostream>
#include "Stack.h"
#include "Literal.h"

int main() {
	/*IntegerLiteral e(8);
	RealLiteral re(1, 7);
	RationalLiteral ra(19, 95);
	ComplexLiteral c(new IntegerLiteral(-5), new RationalLiteral(-3, 4));
	*/
	NumberLiteral n1(1);
	NumberLiteral n2(2.5, real);
	NumberLiteral n3(3, rational, 4);
	NumberLiteral n4(5, complex, 1.0, 2.5); // TODO Comment gérer les complexes

	Stack s;
	s.push(&n1);
	s.push(&n2);
	s.push(&n3);
	s.push(&n4);
	
	for(auto it = s.begin(); it != s.end(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
	



	system("pause");
	return 0;
}