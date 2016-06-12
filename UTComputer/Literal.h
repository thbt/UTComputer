/**
* \file Literal.h
* \brief Contient les littéraux de la calculette
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/

#pragma once
#include <iostream>
#include <string>

/*
class IOperand {
public:
	virtual std::string toString() const = 0;
};*/

/**
	\enum Type

	\brief Contient tous les types disponible pour un literal.
*/
enum Type { INTEGER, RATIONAL, REAL, COMPLEX, EXPRESSION, PROGRAM };

/**
	\class ILiteral

	\brief Classe abstraite dont tous les litteraux vont heriter.

	Contient les methodes de base que chaque litteral doit avoir.
	Possede aussi un type.
*/
class ILiteral  {
	Type type; /*!< \brief Type du littéral */
public:
	/**
	*  \brief Constructeur de littéral.
	*
	*  Construis un littéral en initialisant son type.
	*
	*  \param t : type du littéral.
	*/
	ILiteral(Type t) : type(t) {}

	/**
	*  \brief Getter du type
	*
	*  Retourne le type du litteral
	*
	*  \return Type : type du litteral
	*/
	Type getType() const { return type; }

	/**
	*  \brief Methode virtuelle. Permettra de cloner le litteral
	*  \return ILiteral : le litteral créer
	*/
	virtual ILiteral* clone() const = 0;

	/**
	*  \brief Methode virtuelle. Permettra d'afficher le litteral sous forme de string
	*
	*  \return std::string : chaine de caractere representant le litteral
	*/
	virtual std::string toString() const = 0;
};

/**
\class INumberLiteral

\brief Classe abstraite dont tous les litteraux nombre hériteront

Herite de ILiteral, et ajoute la methode isNul pour savoir si un nombre est nul.
*/
class INumberLiteral : public ILiteral {
public:
	/**
	*  \brief Constructeur de INumberLiteral.
	*
	*  Construis un littéral en initialisant son type.
	*
	*  \param t : type du littéral.
	*/
	INumberLiteral(Type t) : ILiteral(t) {}
	
	/**
	*  \brief Voir la définition de ILiteral
	*/
	virtual ILiteral* clone() const = 0;

	/**
	*  \brief Voir la définition de ILiteral
	*/
	virtual std::string toString() const = 0;

	/**
	*  \brief Methode virtuelle qui renvoie vrai si le nombre est nul
	*
	*  \return bool : vrai si il est nul, faux sinon
	*/
	virtual bool isNul() const = 0;

};

/**
\class IntegerLiteral

\brief Representation d'un entier

Herite de INumberLiteral. Represente un entier avec un attribut int
*/
class IntegerLiteral : public INumberLiteral {
	int value; /*!< \brief Valeur de l'entier */
public:
	/**
	*  \brief Constructeur de IntegerLiteral.
	*
	*  Construis un littéral en initialisant son type a INTEGER et sa valeur a v.
	*
	*  \param v : valeur de l'entier.
	*/
	IntegerLiteral(int v) : INumberLiteral(INTEGER), value(v) {}

	/**
	*  \brief Voir la définition de ILiteral
	*/
	ILiteral* clone() const { return new IntegerLiteral(*this); }

	/**
	*  \brief Getter de value.
	*
	*  Retourne la valeur de value.
	*
	*  \return int : valeur de l'entier.
	*/
	int getValue() const { return value; }

	/**
	*  \brief Renvoie vrai si value vaut 0
	*
	*	\return bool : vrai si value vaut 0, faux sinon.
	*/
	bool isNul() const {
		if (value == 0)
			return true;
		return false;
	}

	/**
	*  \brief Voir la définition de ILiteral
	*
	*  Renvoie simplement la valeur de value sous forme de string
	*/
	std::string toString() const { return std::to_string(value); }
};

/**
\class RationalLiteral

\brief Representation d'un rationnel

Herite de INumberLiteral. Represente un rationnel avec un attribut int pour le numerateur et un pour le denominateur.
*/
class RationalLiteral : public INumberLiteral {
	int numerator;  /*!< \brief Valeur du numerateur */
	int denominator;  /*!< \brief Valeur du denominateur */
public:
	/**
	*  \brief Constructeur de RationalLiteral.
	*
	*  Construis un littéral en initialisant son type a RATIONAL et son numerateur et son denominateur avec deux entiers.
	*  Il appelle aussi la methode simplification pour simplifier la fraction.
	*
	*  \param n : valeur du numerateur.
	*  \param d : valeur du denumerateur.
	*/
	RationalLiteral(int n, int d) : INumberLiteral(RATIONAL), numerator(n), denominator(d) { simplification(); }

	/**
	*  \brief Voir la définition de ILiteral.
	*/
	ILiteral* clone() const { return new RationalLiteral(*this); }

	/**
	*  \brief Voir la définition de ILiteral.
	*
	*	Affiche sous la forme numerateur / denominateur.
	*/
	std::string toString() const { return std::to_string(numerator) + "/" + std::to_string(denominator); }

	/**
	*	\brief Getter du denominateur et du numerateur simultanement.
	*	
	*	Renvoie les deux valeurs dans une paire de int.
	*
	*	\return std::pair<int, int> : pair de la forme <numerateur, denominateur>.
	*/
	std::pair<int, int> getValue() const {
		std::pair<int, int> twoValues;
		twoValues.first = numerator;
		twoValues.second = denominator;
		return twoValues;
	}

	/**
	*  \brief Renvoie vrai si le numerateur vaut 0.
	*
	*	\return bool : vrai si le numerateur vaut 0, faux sinon.
	*/
	bool isNul() const {
		if (numerator == 0)
			return true;
		return false;
	}

	/**
	*	\brief Simplifie la fraction.
	*
	*	Utilise le pgcd pour trouver une fraction equivalente avec un numerateur et un denominateur plus petit.
	*/
	void simplification();

};

/**
\class RealLiteral

\brief Representation d'un reel.

Herite de IReelLiteral. Represente un reel avec un attribut double pour la valeur.
*/
class RealLiteral : public INumberLiteral {
	double value; /*!< \brief Valeur du reel */
public:
	/**
	*  \brief Constructeur de RealLiteral.
	*
	*  Construis un littéral en initialisant son type a REAL et sa valeur avec un double.
	*
	*  \param v : valeur du reel.
	*/
	RealLiteral(double v) : INumberLiteral(REAL), value(v) {}

	/**
	*  \brief Voir la définition de ILiteral.
	*/
	ILiteral* clone() const { return new RealLiteral(*this); }

	/**
	*  \brief Voir la définition de ILiteral.
	*
	*	Renvoie simplement la valeur du litteral sous forme de string.
	*/
	std::string toString() const { return std::to_string(value); }

	/**
	*	\brief Getter de value.
	*
	*	Renvoie la valeur du reel.
	*
	*	\return double : valeur du reel.
	*/
	double getValue() const { return value; }


	/**
	*  \brief Renvoie vrai si value vaut 0.
	*
	*	\return bool : vrai si value vaut 0, faux sinon.
	*/
	bool isNul() const {
		if (value == 0)
			return true;
		return false;
	}
};

/**
\class ComplexLiteral

\brief Representation d'un complexe.

Herite de IReelLiteral. Represente un complexe avec deux attributs INumberLiteral.
*/
class ComplexLiteral : public ILiteral {
	INumberLiteral* real; /*!< \brief Partie reel du complexe. */
	INumberLiteral* imaginary; /*!< \brief Partie imaginaire du complexe. */
public:
	/**
	*  \brief Constructeur de RealLiteral.
	*
	*  Construis un littéral en initialisant son type a COMPLEX et real / imaginaire avec les parametres.
	*
	*  \param r : Partie reel du nouveau complexe.
	*  \param i : Partie imaginaire du nouveau complexe.
	*/
	ComplexLiteral(INumberLiteral* r = new IntegerLiteral(0), INumberLiteral* i = new IntegerLiteral(0)) 
		: ILiteral(COMPLEX), real(r), imaginary(i) {}

	/**
	*  \brief Voir la définition de ILiteral
	*/
	ILiteral* clone() const { return new ComplexLiteral(*this); }

	/**
	*  \brief Voir la définition de ILiteral
	*
	*	Affiche sous la forme partieReel&partieImaginaire
	*/
	std::string toString() const { return real->toString() + "$" + imaginary->toString(); }

	/**
	*	\brief Retourne la partie reel du complexe
	*
	*	\return INumberLiteral& : Partie reelle du complexe
	*/
	INumberLiteral& Re() const { return *real; }

	/**
	*	\brief Retourne la partie imaginaire du complexe
	*
	*	\return INumberLiteral& : Partie imaginaire du complexe
	*/
	INumberLiteral& Im() const { return *imaginary; }

	/**
	*	\brief Retourne le type de la partie reel du complexe
	*
	*	\return Type : Type de la partie reelle du complexe
	*/
	Type getTypeReal() const { return real->getType(); }

	/**
	*	\brief Retourne le type de la partie imaginaire du complexe
	*
	*	\return Type : Type de la partie imaginaire du complexe
	*/
	Type getTypeIm() const { return imaginary->getType(); }
};

/**
\class ExpressionLiteral

\brief Representation d'une expression.

Herite de IReelLiteral. Represente une expression avec la chaine de caractere
*/
class ExpressionLiteral : public ILiteral {
	std::string expression; /*!< \brief String representant l'expression. */
public:
	/**
	*  \brief Constructeur de ExpressionLiteral.
	*
	*  Construis un littéral en initialisant son type a EXPRESSION et avec un string
	*
	*  \param e : String de l'expression.
	*/
	ExpressionLiteral(std::string e) : ILiteral(EXPRESSION), expression(e) {}

	/**
	*  \brief Voir la définition de ILiteral
	*/
	ILiteral* clone() const { return new ExpressionLiteral(*this); }

	/**
	*	\brief Getter de expression.
	*
	*	Renvoie la valeur de l'expression.
	*
	*	\return std::string : valeur de l'expression.
	*/
	std::string getValue() const {
		return expression;
	}

	/**
	*  \brief Voir la définition de ILiteral
	*/
	std::string toString() const { return expression; }

	/**
	*	\brief Renvoie vrai si l'expression vaut ""
	*
	*	\return bool : vrai si expression = "", sinon faux.
	*/
	bool isNul() const { return expression == ""; }
};

/**
\class ProgramLiteral

\brief Representation d'une expression.

Herite de IReelLiteral. Represente une expression avec la chaine de caractere
*/
class ProgramLiteral : public ILiteral {
	std::string program;
public:
	ProgramLiteral(std::string p) : ILiteral(PROGRAM), program(p) {}

	/**
	*  \brief Voir la définition de ILiteral
	*/
	ILiteral* clone() const { return new ProgramLiteral(*this); }

	std::string getValue() const {
		return program;
	}
	
	/**
	*  \brief Voir la définition de ILiteral
	*/

	std::string toString() const { return program; }
	bool isNul() const { return program == ""; }
};