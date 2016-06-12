/**
* \file LiteralFactory.h
* \brief Cree les bons litteraux selon les parametres
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/

#pragma once

#include <string>
#include "Literal.h"


/*! \class LiteralFactory
* \brief Gere la creation des litteraux
*
* Possede differentes methodes pour creer les bons litteraux selon les parametres.
*/
class LiteralFactory {
	LiteralFactory() {};

	/**
	*	\brief Permet de creer un numberLiteral
	*
	*	Creer le litteral correspondant a l'affichage.
	*	Une string avec un . creera un real, avec un / rationnel, sinon un entier
	*
	*	\param str : String correspondant a un nombre
	*	\return INumberLiteral* : INumberLiteral qui vient d'etre creer
	*/
	INumberLiteral* makeNumberLiteral(std::string str) const;
public:
	/**
	*  \brief Renvoie l'instance de la literal factory
	*/
	static const LiteralFactory& getInstance();

	LiteralFactory(const LiteralFactory&) = delete; /*!< \brief Suppression du constructeur de recopie. */
	void operator=(const LiteralFactory&) = delete; /*!< \brief Suppression de l'opérateur d'affectation */


	/**
	*	\brief Permet de creer un IntegerLiteral
	*
	*	\param n : valeur de l'IntegerLiteral
	*	\return ILiteral* : l'integerliteral qui vient d'etre creer
	*/
	ILiteral* makeLiteral(int n) const;

	/**
	*	\brief Permet de creer un RealLiteral
	*
	*	Creer un integer si n vaut 0, sinon un reel
	*
	*	\param n : valeur du RealLiteral
	*	\return ILiteral* : RealLiteral ou IntegerLiteral qui vient d'etre creer
	*/
	ILiteral* makeLiteral(double n) const;

	/**
	*	\brief Permet de creer un RationalLiteral
	*
	*	Creer un integer si n->first vaut 0, sinon un rationnel
	*
	*	\param n : paire d'entier pour creer le RationalLitteral
	*	\return ILiteral* : RationalLitteral ou IntegerLiteral qui vient d'etre creer
	*/
	ILiteral* makeLiteral(std::pair<int,int> n) const;

	/**
	*	\brief Permet de creer un ComplexeLiteral
	*
	*	\param re : partie reel du complexe
	*	\param im : partie imaginaire du complexe
	*
	*	\return ILiteral* : ComplexeLiteral qui vient d'etre creer
	*/
	ILiteral* makeLiteral(INumberLiteral* re, INumberLiteral* im) const;
	
	/**
	*	\brief Permet de creer un litteral
	*
	*	Creer le litteral correspondant a l'affichage.
	*	Une string commencant par un [ creera une expression, un ` creera une variable.
	*	Si elle contient un $ ce sera un complexe, sinon INumberLiteral
	*
	*	\param str : String qui choisira le litteral a creer
	*	\return ILiteral* : ILiteral qui vient d'etre creer
	*/
	ILiteral* makeLiteral(std::string str) const; // abstract factory
};