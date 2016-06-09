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


class QComputer : public QWidget {
	Q_OBJECT
		//Layout
	QVBoxLayout *LayoutPrincipale;
	QHBoxLayout *LayoutMid;
	QHBoxLayout *LayoutCommande;

	//Layout cliquable
	QWidget *WidgetCliquable;
	QGridLayout *LayoutCliquable;

	//Menu
	QMenuBar* menuBar;
	QMenu *menuFichier;
	QMenu *menuVar;
	QMenu *menuProg;
	QMenu *menuOperator;

	//Sous menu
	QMenu *OpeStack;
	QMenu *OpeNumerique;
	QMenu *OpeLogique;

	//Actions menu
	QAction *actionQuitter;
	QAction *bipSonore;
	QAction *nbVariable;
	QAction *clavierCliquable;
	QAction *creerVariable;
	QAction *modifVariable;
	QAction *supprimerVariable;
	QAction *creerFonction;
	QAction *modifFonction;
	QAction *supprimerFonction;


	//Composants
	QLineEdit* message;
	QTableWidget* vuePile;
	QLineEdit* commande;

	//Composants cliclaque
	QPushButton* button1;
	QPushButton* button2;
	QPushButton* button3;
	QPushButton* button4;
	QPushButton* button5;
	QPushButton* button6;
	QPushButton* button7;
	QPushButton* button8;
	QPushButton* button9;
	QPushButton* button0;
	QPushButton* buttonplus;
	QPushButton* buttonmoins;
	QPushButton* buttonfois;
	QPushButton* buttondiv;
	QPushButton* buttonentree;

	//Pile* pile;
	//Controleur* controleur;

public:
	explicit QComputer(QWidget *parent = 0);
	void createOperatorAction();
	public slots:
		void refresh();
		void getNextCommande();
		void printError(std::string error);
		void setTexte();
		void desactiverBip();
		void choixNombreVariable();
		void desactiverCliquable();
		void callOperator();
		void creationVar();
		void modifVar();
		void supprimerVar();
		void creationFct();
		void modifFct();
		void supprimerFct();
		void setVariable(QString value);
};
