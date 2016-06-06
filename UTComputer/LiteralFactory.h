#pragma once

#include <string>
#include "Literal.h"


class LiteralFactory {
	LiteralFactory() {};
	INumberLiteral* makeNumberLiteral(std::string str) const;
public:
	static const LiteralFactory& getInstance();
	LiteralFactory(const LiteralFactory&) = delete; // Suppression du constructeur de recopie.
	void operator=(const LiteralFactory&) = delete; // Suppression de l'opérateur d'affectation.

	ILiteral* makeLiteral(int n) const;
	ILiteral* makeLiteral(double n) const;
	ILiteral* makeLiteral(std::pair<int,int> n) const;
	ILiteral* makeLiteral(INumberLiteral* re, INumberLiteral* im) const;
	
	ILiteral* makeLiteral(std::string str) const;
};