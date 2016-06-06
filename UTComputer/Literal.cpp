#include "Literal.h"
#include <string>
#include <sstream>

//TODO throw exception au lieu de return...
void RationalLiteral::simplification(){
	// si le numerateur est 0, le denominateur prend la valeur 1
	if (numerator == 0) {
		denominator = 1;
		return;
	}

	/* un denominateur ne devrait pas être 0;
	si c’est le cas, on sort de la méthode */
	if (denominator == 0)
		return;

	/* utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun
	Denominateur (PGCD) entre le numerateur et le denominateur */
	int a = numerator, b = denominator;

	// on ne travaille qu’avec des valeurs positives...
	if (a < 0)
		a = -a;
	if (b<0)
		b = -b;

	while (a != b){
		if (a>b)
			a = a - b;
		else
			b = b - a;
	}

	// on divise le numerateur et le denominateur par le PGCD=a
	numerator /= a; denominator /= a;
	// si le denominateur est négatif, on fait passer le signe - au denominateur
	if (denominator < 0) {
		denominator = -denominator;
		numerator = -numerator;
	}
}