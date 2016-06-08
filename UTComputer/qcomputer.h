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

	//Layout cliquable
	QWidget *WidgetCliquable;
	QGridLayout *LayoutCliquable;

	//Menu
	QMenuBar* menuBar;
	QMenu *menuFichier;
	QMenu *menuVar;
	QMenu *menuProg;
	QMenu *menuCaract;

	//Actions menu
	QAction *actionQuitter;
	QAction *bipSonore;
	QAction *nbVariable;
	QAction *clavierCliquable;


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
	public slots:
	void refresh();
	void getNextCommande();
	void printError(std::string error);
	void setTexte();
	void desactiverBip();
	void choixNombreVariable();
	void desactiverCliquable();
};
