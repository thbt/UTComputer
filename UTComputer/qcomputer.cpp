#include "qcomputer.h"

#include <QIcon>
#include <QCoreApplication>
#include <QDebug>
#include <windows.h>
#include <QInputDialog>
#include <QSignalMapper>
#include <QDialogButtonBox>
#include <qlabel.h>
#include "Controller.h"

#include <cctype>

#include <direct.h>
#define GetCurrentDir _getcwd

static bool bipsonor = true;
static bool cliquable = true;

const std::string cheminVar = "./FichierSave/var.txt";

QComputer::QComputer(QWidget *parent){
    setFixedSize(450,250);
    setWindowTitle("UTComputer");
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return;
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
	std::string str(cCurrentPath);
	str += "\\Images\\icone.jpg";
    setWindowIcon(QIcon(QString::fromStdString(str)));


    //pile = new Pile();
    //controleur = new Controleur(ExpressionManager::getInstance(),*pile);

    //Menu
    menuBar = new QMenuBar();
    menuFichier = menuBar->addMenu("&Fichier");
    menuVar = menuBar->addMenu("&Variable");
    menuProg = menuBar->addMenu("&Programme");
    menuOperator = menuBar->addMenu("&Operateurs");
	OpeNumerique = menuOperator->addMenu("&Numerique");
	OpeStack = menuOperator->addMenu("&Pile");
	OpeLogique = menuOperator->addMenu("&Logique");
	menuOperator->addSeparator();
	createOperatorAction();

    //Action
    actionQuitter = new QAction("&Quitter", this);
    bipSonore = new QAction("&Desactiver bip sonore", this);
    nbVariable = new QAction("&Modifier affichage pile", this);
    clavierCliquable = new QAction("&Desactiver le clavier cliquable", this);
	creerVariable = new QAction("&Creer", this);
	modifVariable = new QAction("&Modifier", this);
	supprimerVariable = new QAction("&Supprimer", this);
	creerFonction = new QAction("&Creer", this);
	modifFonction = new QAction("&Modifier", this);
	supprimerFonction = new QAction("&Supprimer", this);



    //Ajouts actions
    menuFichier->addAction(bipSonore);
    menuFichier->addAction(nbVariable);
    menuFichier->addAction(clavierCliquable);
    menuFichier->addAction(actionQuitter);
	menuProg->addAction(creerFonction);
	menuProg->addAction(modifFonction);
	menuProg->addAction(supprimerFonction);
	menuVar->addAction(creerVariable);
	menuVar->addAction(modifVariable);
	menuVar->addAction(supprimerVariable);



    //Layout
    LayoutPrincipale = new QVBoxLayout;
    LayoutMid = new QHBoxLayout;
	LayoutCommande = new QHBoxLayout;

    //Clavier cliquable
    LayoutCliquable = new QGridLayout;
    WidgetCliquable = new QWidget;

    //Button cliquable
    button1 = new QPushButton("1");
    button1->setMaximumWidth(40);
    button2 = new QPushButton("2");
    button2->setMaximumWidth(40);
    button3 = new QPushButton("3");
    button3->setMaximumWidth(40);
    button4 = new QPushButton("4");
    button4->setMaximumWidth(40);
    button5 = new QPushButton("5");
    button5->setMaximumWidth(40);
    button6 = new QPushButton("6");
    button6->setMaximumWidth(40);
    button7 = new QPushButton("7");
    button7->setMaximumWidth(40);
    button8 = new QPushButton("8");
    button8->setMaximumWidth(40);
    button9 = new QPushButton("9");
    button9->setMaximumWidth(40);
    button0 = new QPushButton("0");
    buttonplus = new QPushButton("+");
    buttonmoins = new QPushButton("-");
    buttonfois = new QPushButton("*");
    buttondiv = new QPushButton("/");
    buttonentree = new QPushButton("Entrée");


    //Partie tactile
    WidgetCliquable->setLayout(LayoutCliquable);

    LayoutCliquable->addWidget(button7, 0, 0);
    LayoutCliquable->addWidget(button8, 0, 1);
    LayoutCliquable->addWidget(button9, 0, 2);
    LayoutCliquable->addWidget(buttonplus, 0, 5);

    LayoutCliquable->addWidget(button4, 1, 0);
    LayoutCliquable->addWidget(button5, 1, 1);
    LayoutCliquable->addWidget(button6, 1, 2);
    LayoutCliquable->addWidget(buttonmoins, 1, 5);

    LayoutCliquable->addWidget(button1, 2, 0);
    LayoutCliquable->addWidget(button2, 2, 1);
    LayoutCliquable->addWidget(button3, 2, 2);
    LayoutCliquable->addWidget(buttonfois, 2, 5);

    LayoutCliquable->addWidget(button0, 3, 0, 1,3);
    LayoutCliquable->addWidget(buttondiv, 3, 5);

    message = new QLineEdit();
    message->setReadOnly(true);
    message->setStyleSheet("QLineEdit{background: cyan; color : red;}");

    //vuePile = new QTableWidget(5,1);
    vuePile = new QTableWidget(Controller::instance().getNbDisplay(),1);
    vuePile->horizontalHeader()->hide();
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vuePile->horizontalHeader()->setStretchLastSection(true);

    QPalette p = vuePile->palette();
    QColor colorPile = QColor(0, 139, 139);
    p.setColor(QPalette::Base, colorPile);
    vuePile->setPalette(p);

	//Layout commande
    commande = new QLineEdit();
	LayoutCommande->addWidget(commande);
	LayoutCommande->addWidget(buttonentree);


    //Layout principale
    LayoutPrincipale->addWidget(message);
    LayoutPrincipale->addLayout(LayoutMid);
    LayoutPrincipale->addLayout(LayoutCommande);

    //Layout milieu
    LayoutMid->addWidget(vuePile);
    LayoutMid->addWidget(WidgetCliquable);


    //Connect
    QObject::connect(&Controller::instance(), SIGNAL(changeState()), this, SLOT(refresh()));
    QObject::connect(&Controller::instance(), SIGNAL(showError(std::string)), this, SLOT(printError(std::string)));
    QObject::connect(commande, SIGNAL(returnPressed()), this, SLOT(getNextCommande()));
    QObject::connect(button1, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button2, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button3, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button4, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button5, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button6, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button7, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button8, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button9, SIGNAL(clicked()), this, SLOT(setTexte()));
    QObject::connect(button0, SIGNAL(clicked()), this, SLOT(setTexte()));

	QObject::connect(buttonplus, SIGNAL(clicked()), this, SLOT(callOperator()));
	QObject::connect(buttonmoins, SIGNAL(clicked()), this, SLOT(callOperator()));
	QObject::connect(buttondiv, SIGNAL(clicked()), this, SLOT(callOperator()));
	QObject::connect(buttonfois, SIGNAL(clicked()), this, SLOT(callOperator()));
	QObject::connect(buttonentree, SIGNAL(clicked()), this, SLOT(getNextCommande()));

    //Connect bar
    QObject::connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(bipSonore, SIGNAL(triggered()), this, SLOT(desactiverBip()));
    QObject::connect(nbVariable, SIGNAL(triggered()), this, SLOT(choixNombreVariable()));
    QObject::connect(clavierCliquable, SIGNAL(triggered()), this, SLOT(desactiverCliquable()));

	QObject::connect(creerVariable, SIGNAL(triggered()), this, SLOT(creationVar()));
	QObject::connect(modifVariable, SIGNAL(triggered()), this, SLOT(modifVar()));
	QObject::connect(supprimerVariable, SIGNAL(triggered()), this, SLOT(supprimerVar()));
	QObject::connect(creerFonction, SIGNAL(triggered()), this, SLOT(creationFct()));
	QObject::connect(modifFonction, SIGNAL(triggered()), this, SLOT(modifFct()));
	QObject::connect(supprimerFonction, SIGNAL(triggered()), this, SLOT(supprimerFct()));

    setLayout(LayoutPrincipale);
    layout()->setMenuBar(menuBar);
}

void QComputer::setTexte(){
    QPushButton *senderObj = qobject_cast<QPushButton*>(sender());
    //qDebug() << senderObj->text();
    commande->setText(commande->text() + senderObj->text());
}

void QComputer::refresh(){
    int row = 0;
    vuePile->clear();
    for(std::vector<ILiteral*>::const_reverse_iterator it=Controller::instance().beginStack(); it!=Controller::instance().endStack(); ++it){
        vuePile->setItem(row, 0, new QTableWidgetItem(QString::fromStdString((*it)->toString())));
        row++;
        if(row==Controller::instance().getNbDisplay())
            break;
    }
    message->setText("");
}

void QComputer::getNextCommande(){
    Controller::instance().command(commande->text().toUtf8().constData());
    commande->clear();
}

void QComputer::choixNombreVariable(){
    int variable = QInputDialog::getInt(this, "Nombre à afficher", "Combien de variable voulez-vous afficher dans la pile ?"
                                        ,Controller::instance().getNbDisplay(),1);

    int nbchanger = variable-Controller::instance().getNbDisplay();
    if(nbchanger>0){
        for(int i(0); i<nbchanger; i++)
            vuePile->insertRow(vuePile->rowCount());
    }
    else{
        for(int i = Controller::instance().getNbDisplay(); i>variable; i--)
            vuePile->removeRow(i-1);
    }

    Controller::instance().setNbDisplay(variable);

    vuePile->repaint();
    refresh();
}

void QComputer::creationVar() {
	QDialog* d = new QDialog();
	QVBoxLayout* mainLayout = new QVBoxLayout();
	QHBoxLayout* nameLayout = new QHBoxLayout();
	QHBoxLayout* valeurLayout = new QHBoxLayout();
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	QLabel* labelNom = new QLabel("Nom :");
	QLabel* labelVal = new QLabel("Valeur :");
	QLineEdit* lineNom = new QLineEdit();
	QLineEdit* lineVal = new QLineEdit();

	QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
	QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

	nameLayout->addWidget(labelNom);
	nameLayout->addWidget(lineNom);
	valeurLayout->addWidget(labelVal);
	valeurLayout->addWidget(lineVal);
	//buttonLayout->addWidget(buttonBox)

	mainLayout->addLayout(nameLayout);
	mainLayout->addLayout(valeurLayout);
	mainLayout->addWidget(buttonBox);
	

	d->setLayout(mainLayout);

	int result = d->exec();
	if (result == QDialog::Accepted)
	{
		std::string nom = lineNom->text().toStdString();
		std::string valeur = lineVal->text().toStdString();
		if (!std::isupper(nom[0]) || (nom.find('|') != std::string::npos)) {
			message->setText("Nom de variable invalide.");
		}
		else if (valeur[0] <= '0' || valeur[0] >= '9') {
			message->setText("Valeur incorrecte");
		}
		else {
			Controller::instance().createAtome(nom, valeur);
			message->setText("");
		}
	}
}


void QComputer::modifVar() {


}

void QComputer::supprimerVar() {


}

void QComputer::creationFct() {

}

void QComputer::modifFct() {

}

void QComputer::supprimerFct() {


}


void QComputer::desactiverBip(){
    if(bipsonor==true){
        bipsonor=false;
        bipSonore->setText("Activer bip sonore");
    }
    else{
        bipsonor=true;
        bipSonore->setText("Desactiver bip sonore");
    }

}

void QComputer::desactiverCliquable(){
    if(cliquable==true){
        cliquable=false;
        clavierCliquable->setText("Activer clavier cliquable");
        WidgetCliquable->hide();
    }
    else{
        cliquable=true;
        clavierCliquable->setText("Desactiver clavier cliquable");
        WidgetCliquable->show();
    }
}

void QComputer::printError(std::string error){
    message->setText(QString::fromStdString(error));

    if(bipsonor==true){
            Beep(523,200);
    }
}

void QComputer::callOperator() {
	QAction *senderObj = qobject_cast<QAction*>(sender());
	if(commande->text()=="")
		commande->setText(senderObj->text());
	else
		commande->setText(commande->text() + " " + senderObj->text());
}

void QComputer::createOperatorAction(){
	//operateur stack : DUP, DROP, SWAP , LASTOP, UNDO, REDO, CLEAR
	//operateur numerique : +, -, *, /, DIV, NEG, NUM, DEN, $, RE, IM?
	//operateur logique : =, !=, =<, <, >, AND, OR, NOT 
	for (std::string t : Controller::instance().getOperators()) {
		QAction *ope = new QAction(QString::fromStdString(t), this);
		if (t == "DUP" || t == "DROP" || t == "SWAP" || t == "LASTOP" || t == "UNDO" || t == "REDO" || t == "CLEAR" || t == "MOD") { 
			OpeStack->addAction(ope);
		}
		else if (t == "+" || t == "-" || t == "*" || t == "/" || t == "DIV" || t == "NEG" || t == "NUM" || t == "DEN" || t == "$" || t == "RE" || t == "IM") {
			OpeNumerique->addAction(ope);
		}
		else if (t == "=" || t == "!=" || t == "<=" || t == ">" || t == ">=" || t == "<" || t == "AND" || t == "OR" || t == "NOT" || t == "EQUAL") {
			OpeLogique->addAction(ope);
		}
		else {
			menuOperator->addAction(ope);
		}
		connect(ope, SIGNAL(triggered()), this, SLOT(callOperator()));
	}
}
