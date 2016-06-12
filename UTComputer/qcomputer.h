/**
* \file qcomputer.h
* \brief Vue de la calculette
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/


#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>

/*! \class QComputer
* \brief Vue de la calculette
*
* Partie IHM de la calculette
*/
class QComputer : public QWidget {
	Q_OBJECT
	//Layout
	QVBoxLayout *LayoutPrincipale; /*!< \brief Layout globale de la vue */
	QHBoxLayout *LayoutMid; /*!< \brief Layout du milieu, contient l'affichage de la pile et du pave cliquable */
	QHBoxLayout *LayoutCommande; /*!< \brief Layout du bas, contient  la commande et le bouton d'entree*/

	//Layout cliquable
	QWidget *WidgetCliquable; /*!< \brief Contient les boutons du pave cliquable */
	QGridLayout *LayoutCliquable; /*!< \brief Layout du pave cliquable */

	//Menu
	QMenuBar* menuBar; /*!< \brief Barre d'outils */
	QMenu *menuFichier; /*!< \brief Menu des fichiers */
	QMenu *menuVar; /*!< \brief Menu des variables */
	QMenu *menuProg; /*!< \brief Menu des programmes */
	QMenu *menuOperator; /*!< \brief Menu des operateurs */

	//Sous menu
	QMenu *OpeStack; /*!< \brief Contient les operateurs de stack */
	QMenu *OpeNumerique; /*!< \brief Contient les operateurs numerique */
	QMenu *OpeLogique; /*!< \brief Contient les operateurs logique */
	QMenu *voirPrgm; /*!< \brief Affichage de tous les programmes */
	QMenu *voirVar; /*!< \brief Affichages de toutes les variables*/

	//Actions menu
	QAction *actionQuitter; /*!< \brief Action pour quitter la pile */
	QAction *bipSonore; /*!< \brief Action pour activer / desactiver le bip sonore */
	QAction *nbVariable; /*!< \brief Action pour choisir le nombre de variable*/
	QAction *clavierCliquable; /*!< \brief Action pour activer / desactiver le pave cliquable */
	QAction *creerVariable; /*!< \brief Action pour afficher l'ecran de creation d'une variable */
	QAction *modifVariable; /*!< \brief Action pour afficher l'ecran de modification d'une variable */
	QAction *supprimerVariable; /*!< \brief Action pour afficher l'ecran de suppression d'une variable */
	QAction *creerFonction; /*!< \brief Action pour afficher l'ecran de creation d'un programme */
	QAction *modifFonction;/*!< \brief Action pour afficher l'ecran de modification d'un programme */
	QAction *supprimerFonction; /*!< \brief Action pour afficher l'ecran de suppression d'un programme */



	//Composants
	QLineEdit* message; /*!< \brief Affiche les messages d'erreur */
	QTableWidget* vuePile; /*!< \brief Affiche la pile */
	QLineEdit* commande; /*!< \brief Affiche la commande */

	//Composants cliclaque
	QPushButton* button1; /*!< \brief Button cliquable chiffre 1 */
	QPushButton* button2; /*!< \brief Button cliquable chiffre 2 */
	QPushButton* button3; /*!< \brief Button cliquable chiffre 3 */
	QPushButton* button4; /*!< \brief Button cliquable chiffre 4 */
	QPushButton* button5; /*!< \brief Button cliquable chiffre 5 */
	QPushButton* button6; /*!< \brief Button cliquable chiffre 6 */
	QPushButton* button7; /*!< \brief Button cliquable chiffre 7 */
	QPushButton* button8; /*!< \brief Button cliquable chiffre 8 */
	QPushButton* button9; /*!< \brief Button cliquable chiffre 9 */
	QPushButton* button0; /*!< \brief Button cliquable chiffre 0 */
	QPushButton* buttonplus; /*!< \brief Button cliquable operateur + */
	QPushButton* buttonmoins; /*!< \brief Button cliquable operateur - */
	QPushButton* buttonfois; /*!< \brief Button cliquable operateur * */
	QPushButton* buttondiv; /*!< \brief Button cliquable operateur / */
	QPushButton* buttonentree; /*!< \brief Button cliquable entree */

public:
	explicit QComputer(QWidget *parent = 0);

	/**
	*  \brief Creer dynamiquement les actions operateur
	*
	*  Parcourir la liste des operateurs et cree une action pour chacun d'entre eux
	*/
	void createOperatorAction();

	/**
	*  \brief Creer dynamiquement les actions de variables et de programme
	*
	*	Parcourir la liste des variables et des programmes et cree une action pour chacun d'entre eux
	*/
	void createVarAndProgAction();

	/**
	*  \brief Permet de gerer les actions a affectuer avant de quitter l'application
	*
	*	Sauvegarde les variables et les programmes dans un fichier avant de quitter l'application
	*/
	void closeEvent(QCloseEvent *event);

	public slots:
		/**
		*  \brief Met a jour la vue quand il recoit un signal du controleur
		*
		*	Met a jour l'affichage de la pile
		*/
		void refresh();

		/**
		*  \brief Envoie la commande au controleur quand l'utilisateur appuie sur le bouton ou la touche entree
		*/
		void getNextCommande();

		/**
		*  \brief Affiche l'erreur envoye par le controleur
		*/
		void printError(std::string error);

		/**
		*  \brief Ajoute du texte dans la ligne de commande quand on presse un bouton
		*/
		void setTexte();

		/**
		*  \brief Active / Desactive le bip sonore
		*/
		void desactiverBip();

		/**
		*  \brief Affiche la vue de choix du nombre de variable puis met a jour la vue
		*/
		void choixNombreVariable();

		/**
		*  \brief Active / Desactive le clavier cliquable
		*/
		void desactiverCliquable();

		/**
		*  \brief Ajoute le nom d'un operator dans la ligne de commande quand on presse une action operateur
		*/
		void callOperator();

		/**
		*  \brief Affiche le menu de creation de variable puis cree la variable via le controleur
		*/
		void creationVar();

		/**
		*  \brief Affiche le menu d'edition de variable puis modifie la variable via le controleur
		*/
		void modifVar(std::string name = "");

		/**
		*  \brief Affiche le menu de suppression de variable puis supprime la variable via le controleur
		*/
		void supprimerVar();

		/**
		*  \brief Affiche le menu de creation de programme puis cree le programme via le controleur
		*/
		void creationFct();

		/**
		*  \brief Affiche le menu d'edition de programme puis modifie le programme via le controleur
		*/
		void modifFct(std::string name = "");

		/**
		*  \brief Affiche le menu de suppression de programme puis supprime le programme via le controleur
		*/
		void supprimerFct();

		/**
		*  \brief Affiche la valeur de la variable dans le menu de creation et de modification
		*
		*  \param value : nom de la variable
		*/
		void setVariable(QString value);

		/**
		*  \brief Affiche la valeur du programme dans le menu de creation et de modification
		*/
		void setFct();

		/**
		*  \brief Sauvegarde et quitte l'application quand on appuie sur le bouton quitter
		*/
		void saveAndQuit();

		/**
		*  \brief Remet la pile dans son etat precedent quand on appuie sur CTRL+Z
		*/
		void executeCtrlZ();

		/**
		*  \brief Remet la pile dans son etat suivant quand on appuie sur CTRL+Y
		*/
		void executeCtrlY();

		/**
		*  \brief Appelle la methode de mise a jour des variables et des fonctions
		*/
		void modifVarFct();
};
