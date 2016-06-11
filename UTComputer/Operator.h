/**
* \file Operator.h
* \brief Contient tous les operateurs possibles dans la calculette
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/


#pragma once

#include "Literal.h"
#include "Stack.h"

/*! \class IOperator
* \brief Classe abstraite dont chaque operateur heritera
*
* Contient les methodes de base que chaque methode aura
*/
class IOperator : public IOperand {
	std::string symbol; /*!< \brief Symbole utilise par l'utilisateur pour designer l'operateur*/
	const unsigned int arity; /*!< \brief nombre d'element dont l'operateur a besoin (operateur unaire, binaire etc..)*/
public:
	/**
	*  \brief Constructeur d'un operateur
	*
	*  Construit a partir du nom et de l'arite de l'operateur
	*
	*  \param s : symbole designant l'operateur
	*  \param a : arite de l'operateur
	*/
	IOperator(std::string s, unsigned int a) : symbol(s), arity(a) {}

	/**
	*  \brief Getter du symbole
	*
	*  Renvoie le symbole correspondant a l'operateur
	*
	*  \return std::string : symbole de l'operateur
	*/
	std::string toString() const { return symbol; }

	/**
	*  \brief Methode virtuel redefini par chaque operator pour definir la fonction de l'operateur
	*
	*  Methode principale de l'operateur : execute une action definie pour chaque operateur
	*
	*  Genere une erreur si il y n'y a moins d'element dans la pile que l'arité de l'opérateur.
	*  \param s : Reference sur la stack pour executer l'operateur
	*/
	virtual void operator()(Stack* s) = 0; // Foncteur = classe-fonction

	/**
	*  \brief Getter de arity
	*
	*  Renvoie l'arite correspondant a l'operateur
	*
	*  \return std::string : arite de l'operateur
	*/
    unsigned int getArity() const { return arity; }
};

/*! \class PlusOp
* \brief Permet d'aditionner deux elements
*
* Ajoute a la pile l'addition des deux premiers element de la pile
*/
class PlusOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole + et arité 2
	*/
	PlusOp() : IOperator("+", 2) {}

	/**
	*	Ajoute a la pile l'addition du premier et du deuxieme element
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel, un rationnel ou un complexe.
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class MinusOp
* \brief Permet de soustraire deux elements
*
* Ajoute a la pile soustraction du deuxieme element de la pile par le premier
*/
class MinusOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole - et arité 2
	*/
	MinusOp() : IOperator("-", 2) {}

	/**
	*	Ajoute a la pile la soustraction du deuxieme et du premier element
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel, un rationnel ou un complexe
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class MultiOp
* \brief Permet de multiplier deux elements
*
* Ajoute a la pile la multiplication des deux premiers element de la pile
*/
class MultiOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole * et arité 2
	*/
	MultiOp() : IOperator("*", 2) {}

	/**
	*	Ajoute a la pile la multiplication du premier et du deuxieme element
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel, un rationnel ou un complexe
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class DivOp
* \brief Permet de diviser deux elements
*
* Ajoute a la pile division du premier element de la pile par le deuxieme
*/
class DivOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole / et arité 2
	*/
	DivOp() : IOperator("/", 2) {}

	/**
	*	Ajoute a la pile la division du deuxieme element par le premier
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel, un rationnel ou un complexe
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class DivEntOp
* \brief Permet la division entiere entre deux nombres
*
* Ajoute a la pile la division entiere du deuxieme element de la pile par le premier 
*/
class DivEntOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole DIV et arité 2
	*/
	DivEntOp() : IOperator("DIV", 2) {}

	/**
	*	Ajoute a la pile la division entiere du deuxieme element par le premier
	*	Genere une erreur si un de ces deux elements n'est pas un entier
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class ModulOp
* \brief Permet de faire le modulo de deux elements
*
* Permet d'ajouter a la pile le reste du modulo du deuxieme element de la pile par le premier
*/
class ModulOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole MOD et arité 2
	*/
	ModulOp() : IOperator("MOD", 2) {}

	/**
	*	Ajoute a la pile le modulo du deuxieme element par le premier
	*	Genere une erreur si un de ces deux elements n'est pas un entier
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};


/*! \class NegOp
* \brief Permet de changer le signe d'un element
*
* Change le signe du premier element de la pile et l'ajoute a la pile
*/
class NegOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole NEG et arité 1
	*/
	NegOp() : IOperator("NEG", 1) {}

	/**
	*	Recupere le premier element de la pile, change son signe et le remet en haut de la pile
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel, un rationnel ou un complexe
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class NumOp
* \brief Permet de recuperer le numerateur d'un element
*
* Ajoute a la pile le numerateur du premier element de la pile
*/
class NumOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole NUM et arité 1
	*/
	NumOp() : IOperator("NUM", 1) {}

	/**
	*	Recupere le premier element de la pile et met son numerateur dans la pile
	*   Remet l'element tel qu'il est si c'est un entier.
	*	Genere une erreur si un de ces deux elements n'est pas un entier ou un rationnel
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);

};

/*! \class DenOp
* \brief Permet de recuperer le denumerateur d'un element
*
* Ajoute a la pile le denumerateur du premier element de la pile
*/
class DenOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole DEN et arité 1
	*/
	DenOp() : IOperator("DEN", 1) {}

	/**
	*	Recupere le premier element de la pile et met son denumerateur dans la pile.
	*   Met 1 dans la pile si l'element est un entier
	*	Genere une erreur si un de ces deux elements n'est pas un entier ou un rationnel
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);

};

/*! \class $Op
* \brief Permet de creer un complexe a partir de deux elements
*
* Ajoute a la pile un complexe avec les deux premiers elements de la pile.
* Le deuxieme element correspond a la partie reel, et le premier a la partie imaginaire
*/
class $Op : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole $ et arité 2
	*/
	$Op() : IOperator("$", 2) {}

	/**
	*	Construit un complexe à partir des deux premiers elements de la pile
	*	Le premier devient la partie imaginaire, le deuxieme la partie reelle
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel ou un rationnel.
	*
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class ReOp
* \brief Permet de recuperer la partie reel d'un element
*
* Ajoute la pile la partie reel du premier element de la pile
*/
class ReOp : public IOperator{
public :
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole RE et arité 1
	*/
	ReOp() : IOperator("RE", 1) {}

	/**
	*	Recupere le premier element de la pile et met sa partie reelle dedans.
	*	L'element est inchangé si c'est un entier, un reel ou un rationnel.
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel, un rationnel ou un complexe
	*
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class ImOp
* \brief Permet de recuperer la partie imaginaire d'un element
*
* Ajoute la pile la partie imaginaire du premier element de la pile
*/
class ImOp : public IOperator{
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole IM et arité 1
	*/
	ImOp() : IOperator("IM", 1) {}

	/**
	*	Recupere le premier element de la pile et met sa partie reelle dedans.
	*	On met 0 dans la pile si c'est un entier, un reel ou un rationnel.
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel, un rationnel ou un complexe
	*
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class DupOp
* \brief Clone un element
*
* Ajoute la pile la copie du premier element de la pile
*/
class DupOp : public IOperator{
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole DUP et arité 1
	*/
	DupOp() : IOperator("DUP", 1) {}

	/**
	*	Recupere le premier element de la pile et le met deux fois dans la pile.
	*	Genere une erreur si un de ces deux elements n'est pas un entier, un reel, un rationnel ou un complexe
	*
	*   \param s : Reference sur la stack pour executer l'operateur
	*/
	void operator()(Stack* s);
};

/*! \class DropOp
* \brief Permet de supprimer le premier element de la pile
*
* Supprime le premier element de la pile
*/
class DropOp : public IOperator{
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole DROP et arité 1
	*/
	DropOp() : IOperator("DROP", 1) {}
	void operator()(Stack* s);
};

/*! \class SwapOp
* \brief Permet d'echanger la position de deux premiers elements
*
* Echange la position des deux premiers elements de la pile
*/
class SwapOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole SWAP et arité 0
	*/
	SwapOp() : IOperator("SWAP", 2) {}
	void operator()(Stack* s);
};

/*! \class ClearOp
* \brief Vide la pile
*
* Permet de supprimer tous les élements de la pile
*/
class ClearOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole CLEAR et arité 0
	*/
	ClearOp() : IOperator("CLEAR", 0) {}
	void operator()(Stack* s);
};

/*! \class EqualOp
* \brief Regarde l'egalite entre deux elements
*
* Regarde l'egalite entre les deux premiers elements de la pile
*/
class EqualOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole = et arité 2
	*/
	EqualOp() : IOperator("=", 2) {}
	void operator()(Stack* s);
};

/*! \class DifferentOp
* \brief Regarde l'inegalite entre deux elements
*
* Regarde l'inegalite entre les deux premiers elements de la pile
*/
class DifferentOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole != et arité 2
	*/
	DifferentOp() : IOperator("!=", 2) {}
	void operator()(Stack* s);
};

/*! \class InfEqOp
* \brief Regarde si un element est inferieur ou egale a un autre
*
* Regarde si le deuxieme elmement de la pile est inferieur ou egale au premier
*/
class InfEqOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole <= et arité 2
	*/
	InfEqOp() : IOperator("<=", 2) {}
	void operator()(Stack* s);
};

/*! \class InfOp
* \brief Regarde si un element est inferieur a un autre
*
* Regarde si le deuxieme elmement de la pile est inferieur au premier
*/
class InfOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole < et arité 2
	*/
	InfOp() : IOperator("<", 2){}
	void operator()(Stack* s);
};

/*! \class SupOp
* \brief Regarde si un element est superieur a un autre
*
* Regarde si le deuxieme elmement de la pile est superieur au premier
*/
class SupOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole > et arité 2
	*/
	SupOp() : IOperator(">", 2){}
	void operator()(Stack* s);
};

/*! \class SupEqOp
* \brief Regarde si un element est superieur ou egale a un autre
*
* Regarde si le deuxieme elmement de la pile est superieur ou egale au premier
*/
class SupEqOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole >= et arité 2
	*/
	SupEqOp() : IOperator(">=", 2){}
	void operator()(Stack* s);
};

/*! \class AndOp
* \brief ET logique entre deux elements
*
* ET logique entre le premier et le deuxieme element.
* 0 = non, tout le reste = oui
*/
class AndOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole AND et arité 2
	*/
	AndOp() : IOperator("AND", 2){}
	void operator()(Stack* s);
};

/*! \class OrOp
* \brief OR logique entre deux elements
*
* OR logique entre le premier et le deuxieme element.
* 0 = non, tout le reste = oui
*/
class OrOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole OR et arité 2
	*/
	OrOp() : IOperator("OR", 2){}
	void operator()(Stack* s);
};

/*! \class NotOp
* \brief NOT logique d'un element
*
* NOT logique du premier element
* 0 = non, tout le reste = oui
*/
class NotOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole NOT et arité 1
	*/
	NotOp() : IOperator("NOT", 1){}
	void operator()(Stack* s);
};

/*! \class UndoOp
* \brief Execute la methode UNDO du controler
*
*/
class UndoOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole UNDO et arité 0
	*/
	UndoOp() : IOperator("UNDO", 0) {}
	void operator()(Stack* s);
};

/*! \class RedoOp
* \brief Execute la methode Redo du controleur
*
*/
class RedoOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole REDO et arité 0
	*/
	RedoOp() : IOperator("REDO", 0) {}
	void operator()(Stack* s);
};

/*! \class EvalOp
* \brief Evalue une expression
*
* Evalue une evaluation et la transforme en notation polonaise
*/
class EvalOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole EVAL et arité 1
	*/
	EvalOp() : IOperator("EVAL", 1) {}
	void operator()(Stack* s);
};

/*! \class IftOp
* \brief Operateur de boucle : evalue le deuxieme element si le premier est vrai
*
* Operateur de boucle, si le premier element est non-nul, alors on evalue le deuxieme
*/
class IftOp : public IOperator {
public:
	/**
	*  \brief Constructeur de l'operateur
	*
	*  Construit l'operateur avec le symbole IFT et arité 2
	*/
	IftOp() : IOperator("IFT", 2) {}
	void operator()(Stack* s);
};


