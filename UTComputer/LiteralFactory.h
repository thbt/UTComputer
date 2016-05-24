#pragma once
#include "Literal.h"

class LiteralFactory {
	LiteralFactory() {};
public:
	static const LiteralFactory& getInstance();
	LiteralFactory(const LiteralFactory&) = delete; // Suppression du constructeur de recopie.
	void operator=(const LiteralFactory&) = delete; // Suppression de l'op�rateur d'affectation.

	ILiteral* makeLiteral(int n) const;
};