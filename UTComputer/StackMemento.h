/**
* \file StackMemento.h
* \brief Pattern memento, represente un etat de la stack a un moment T
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/

#pragma once

#include <vector>

#include "Literal.h"

/**
* \brief Pattern memento, represente un etat de la stack a un moment T
* Pattern Memento
* Originator = Stack : c'est l'objet dont on souhaite conserver les etats au fur et a mesure de l'utilisation
* Memento = StackMemento : classe amie de l'originator, c'est l'originator qui s'occupera de créer les instances
* Caretaker = Controller : c'est lui qui a besoin de travailler avec le pattern memento
*/
class StackMemento {
	friend class Stack; /*!< \brief Permet l'acces aux methodes de stack */

	std::vector<ILiteral*> state; /*!< \brief Representation d'une stack a un moment T */
	StackMemento() {};

	/**
	*  \brief Copie l'etat de la stack recu en parametre
	*
	*  Fais une copie du vector de litteral recu en paramtre
	*
	*  \param s : liste de litteral representant une stack.
	*/
	void setState(const std::vector<ILiteral*>& s); // deep copy

	/**
	*  \brief Getter de l'etat
	*
	*  \return std::vector<ILiteral*>& : return l'etat de la stack
	*/
	std::vector<ILiteral*> getState() const { return state; }
public:
	~StackMemento();
};
