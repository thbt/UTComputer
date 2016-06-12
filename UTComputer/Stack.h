/**
* \file Stack.h
* \brief Contient la pile de la calculette
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/


#pragma once
#include <stack>
#include <vector>
#include "Literal.h"
#include "StackMemento.h"

/*! \class Stack
* \brief Pile de la calculette.
*
* Stock les littéraux de la calculette.
*/
class Stack {
	std::vector<ILiteral*> stack; /*!< \brief vector de littéraux */
public:
	/**
	*  \brief Verifie si la pile est vide.
	*
	*  Renvoie vrai si la liste est vide, faux sinon.
	*
	*  \return bool : renvoie vrai si la liste est vide, faux sinon.
	*/
	bool empty() const { return stack.empty(); }

	/**
	*  \brief Renvoie la taille de la pile.
	*
	*  \return size_t : Renvoie la taille de la stack.
	*/
	size_t size() const { return stack.size(); }

	/**
	*  \brief Renvoie le premier element de la pile.
	*
	*  Renvoie le premier element, donc le plus haut, de la pile.
	*
	*  \return ILiteral* : Element le plus haut dans la pile.
	*/
	ILiteral* top() { return stack.back(); }

	/**
	*  \brief Renvoie le premier element de la pile.
	*
	*  Renvoie le premier element, donc le plus haut, de la pile en const.
	*
	*  \return const ILiteral* : Element le plus haut dans la pile en formant const.
	*/
	const ILiteral* top() const { return stack.back(); }

	/**
	*  \brief Ajoute un element dans la pile
	* 
	*  Ajoute un element au sommet de la pile
	*
	*  \param ILiteral* : Element a ajoute en haut de la pile.
	*/
	void push(ILiteral* val) { return stack.push_back(val); }

	/**
	*  \brief Enleve le premier element de la pile.
	*
	*  Supprime le premier element de la pile
	*/
	void pop() { stack.pop_back(); }

	// deep copy constructor
	Stack() : stack() {}
	Stack(const Stack& s);
	~Stack();

	/**
	*  \brief Renvoie un iterator sur le premier element de la pile.
	*
	*  \return std::vector<ILiteral*>::const_reverse_iterator : Iterator sur le premier element de la pile.
	*/
	std::vector<ILiteral*>::const_reverse_iterator begin() const { return stack.crbegin(); }

	/**
	*  \brief Renvoie un iterator sur le dernier element de la pile.
	*
	*  \return std::vector<ILiteral*>::const_reverse_iterator : Iterator sur le dernier element de la pile.
	*/
	std::vector<ILiteral*>::const_reverse_iterator end() const { return stack.crend(); }

	/**
	*  \brief Cree un etat de la pile actuelle
	*
	*  \return StackMemento* : Copie de la pile en l'etat actuelle
	*/
	StackMemento* createMemento() { StackMemento* sm = new StackMemento(); sm->setState(stack); return sm; }
	void setMemento(StackMemento* m); // deep copy
};

