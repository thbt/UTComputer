/**
* \file Controller.h
* \brief Contient le controller de la calculette
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/


#pragma once

#include <QObject>

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <stack>

#include "Stack.h"
#include "Operator.h"


/*! \class Controller
* \brief Gere les variables, les programmes, le parser, les etats de la pile et les erreurs
*
* Controleur de la calculette
* Permet le lien entre la pile et la vue, en controlant les donn√©es envoyes par l'utilisation
* et en les mettant dans la pile
*/
class Controller : public QObject {
    Q_OBJECT

    Controller();

    unsigned int NumberDisplay; /*!< \brief Nombre de variable a afficher */
    Stack stack; /*!< \brief Pile de la calculette */
    std::map<std::string, std::function<void(Stack* s)>> dispatcher; /*!< \brief Operateurs de la calculette */
	std::map<std::string, std::string> vars; /*!< \brief Variables crees par l'utilisateur */
	std::map<std::string, std::string> prgms; /*!< \brief Programmes crees par l'utilisateur */
    std::stack<StackMemento*> undoStack; /*!< \brief Etats precedents de la calculette */
    std::stack<StackMemento*> redoStack; /*!< \brief Etats suivants de la calculette */

public:
	/** Instance singleton du controleur */
    static Controller& instance();

	/**
	*  \brief Execute des fonctions selon la string.
	*
	*  Methode qui permet de lire une string envoyee en parametre, de la parse et 
	* d'effectuer des actions selon celle-ci.
	*
	*  \param str : la commande a† executer.
	*/
    void command(const std::string& str);

	/**
	*  \brief Execute l'operateur envoye en param.
	*
	*  Recherche l'operateur dans la liste dispatcher et l'execute.
	*  Si l'operateur a execute est UNDO ou REDO on appelle nous meme la methode correspondant dans le controler.
	*
	*  \param op : l'operateur a executer.
	*/
    void execute(std::string op);

	/**
	*  \brief Fais un undo sur la pile
	*
	*  Ajoute l'etat actuel de la pile dans redo si jamais on veut annuler le undo
	*  Affiche l'etat de la pile en haut de la pile de undo
	*  Throw si la pile de undo est vide et donc qu'il n'y a rien a undo.
	*/
    void undo();

	/**
	*  \brief Fais un redo sur la pile.
	*
	*  Ajoute l'etat actuel de la pile dans undo si jamais on veut annuler le redo
	*  Affiche l'etat de la pile en haut de la pile de redo
	*  Throw si la pile de undo est vide et donc qu'il n'y a rien a redo.
	*/
    void redo();

	/**
	*  \brief Getter de NbDisplay.
	*
	*  Appeler par la vue pour savoir le nombre d'element a afficher.
	* 
	* \return unsigned int : nombre d'element a afficher.
	*/
    unsigned int getNbDisplay() const;

	/**
	*  \brief Setter nbDisplay.
	*
	*  Permet de mettre a jour le nombre d'element a afficher.
	*/
    void setNbDisplay(unsigned int nb);

	/**
	*  \brief Getter des keys de dispatcher.
	*
	*  Renvoie la liste des noms des operateurs stockes dans dispatcher.
	*
	* \return std::vector<std::string> : liste des noms des operateurs.
	*/
	std::vector<std::string> getOperators();

	/**
	*  \brief renvoie le debut de l'iterator de la pile.
	*
	*  Renvoie un iterator sur le debut de la pile.
	*
	* \return std::vector<ILiteral*>::const_reverse_iterator Iterator sur le debut de la pile.
	*/
    std::vector<ILiteral*>::const_reverse_iterator beginStack() const{
        return stack.begin();
    }

	/**
	*  \brief renvoie la fin de l'iterator de la pile.
	*
	*  Renvoie un iterator sur la fin de la pile.
	*
	* \return std::vector<ILiteral*>::const_reverse_iterator Iterator sur la fin de la pile.
	*/
    std::vector<ILiteral*>::const_reverse_iterator endStack() const{
        return stack.end();
    }

	/**
	*  \brief Creer une variable ou un programme.
	*
	*  Creer, selon le nom, une variable ou un programme et l'ajoute a la map correspondante
	*  avec en cle sa valeur.
	*
	* \param name nom de l'atome. Le nom commence par une majuscule.
	* \param value valeur de l'atome. Un programme doit commencer par [ sinon c'est une variable.
	*/
	void createAtome(std::string name, std::string value);

	/**
	*  \brief Recuper les atomes dans des fichiers.
	*
	*  Recupere dans les fichiers les variables et les parametres.
	*  et initialise les listes au lancement du programme.
	*/
	void initAtome();

	/**
	*  \brief Supprime un atome.
	*
	*  Supprime un atome selon son nom. Si il n'est pas dans vars il est forcement dans prgms.
	*
	* \param name Nom de l'atome a supprimer.
	*/
	void deleteAtome(std::string name);
	std::map<std::string, std::string> getVariables();
	std::map<std::string, std::string> getPrograms();
	std::string getPathVar();

	/**
	*  \brief Renvoie le chemin ou sont stockes les programmes.
	*
	*  Renvoie le chemin absolu (par rapport au projet) ou sont stockes les programmes.
	*
	* \return std::string : chemin ou sont stockes les programmes.
	*/
	std::string getPathProg();

	/**
	*  \brief Sauvegarde les atomes dans des fichiers.
	*
	*  Appeler a la fin du programme pour sauvegarder vars et prgms dans des fichiers separes.
	*/
	void saveAtome();

signals :
	/**
	*  \brief Signal pour prevenir qu'il y a un changement de l'etat de la pile.
	*
	*  Signal a la vue qu'il y a un changement d'etat de la pile.
	*/
    void changeState();

	/**
	*  \brief Signal pour prevenir qu'il y a une erreur a afficher.
	*
	*  Signal a la vue l'erreur a afficher.
	*
	* \param error l'erreur a afficher.
	*/
    void showError(std::string error);
};
