#pragma once
#include "Literal.h"

class LiteralFactory {
	LiteralFactory() {};
public:
	static const LiteralFactory& getInstance();
	LiteralFactory(const LiteralFactory&) = delete; // Suppression du constructeur de recopie.
	void operator=(const LiteralFactory&) = delete; // Suppression de l'opérateur d'affectation.

	ILiteral* makeLiteral(int n) const;
};