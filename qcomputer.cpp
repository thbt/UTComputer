#include "qcomputer.h"
#include <QIcon>
#include <QCoreApplication>
#include <QDebug>
#include <windows.h>
#include <QInputDialog>

static bool bipsonor = true;

QComputer::QComputer(QWidget *parent){
    setFixedSize(300,250);
    setWindowTitle("UTComputer");
    setWindowIcon(QIcon("D:/Cours/UTC/P16/LO21/UTComputer/Images/icone.jpg"));


    pile = new Pile();
    controleur = new Controleur(ExpressionManager::getInstance(),*pile);

    //Menu
    menuBar = new QMenuBar();
    menuFichier = menuBar->addMenu("&Fichier");
    menuVar = menuBar->addMenu("&Variable");
    menuProg = menuBar->addMenu("&Programme");
    menuCaract = menuBar->addMenu("&Caractere");
    Parametres = menuFichier->addMenu("&Paramètres");

    //Action
    actionQuitter = new QAction("&Quitter", this);
    bipSonore = new QAction("&Desactiver bip sonore", this);
    nbVariable = new QAction("&Modifier affichage pile", this);


    //Ajouts actions
    menuFichier->addAction(bipSonore);
    menuFichier->addAction(nbVariable);
    menuFichier->addAction(actionQuitter);



    //Layout
    LayoutPrincipale = new QVBoxLayout;
    LayoutMid = new QHBoxLayout;

    //Clavier tactile
    LayoutTactile = new QGridLayout;

    //Button tactile
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
    LayoutTactile->addWidget(button7, 0, 0);
    LayoutTactile->addWidget(button8, 0, 1);
    LayoutTactile->addWidget(button9, 0, 2);
    LayoutTactile->addWidget(buttonplus, 0, 5);

    LayoutTactile->addWidget(button4, 1, 0);
    LayoutTactile->addWidget(button5, 1, 1);
    LayoutTactile->addWidget(button6, 1, 2);
    LayoutTactile->addWidget(buttonmoins, 1, 5);

    LayoutTactile->addWidget(button3, 2, 0);
    LayoutTactile->addWidget(button2, 2, 1);
    LayoutTactile->addWidget(button1, 2, 2);
    LayoutTactile->addWidget(buttonfois, 2, 5);

    LayoutTactile->addWidget(button0, 3, 0, 1,3);
    LayoutTactile->addWidget(buttonentree, 3, 5);


    message = new QLineEdit();
    message->setReadOnly(true);
    message->setStyleSheet("QLineEdit{background: cyan; color : red;}");

    vuePile = new QTableWidget(pile->getNbItemsToAffiche(),1);
    vuePile->horizontalHeader()->hide();
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vuePile->horizontalHeader()->setStretchLastSection(true);

    QPalette p = vuePile->palette();
    QColor colorPile = QColor(0, 139, 139);
    p.setColor(QPalette::Base, colorPile);
    vuePile->setPalette(p);

    commande = new QLineEdit();


    //Layout principale
    LayoutPrincipale->addWidget(message);
    LayoutPrincipale->addLayout(LayoutMid);
    LayoutPrincipale->addWidget(commande);

    //Layout milieu
    LayoutMid->addWidget(vuePile);
    LayoutMid->addLayout(LayoutTactile);




    //Connect
    QObject::connect(pile, SIGNAL(modificationEtat()), this, SLOT(refresh()));
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

    //Connect bar
    QObject::connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(bipSonore, SIGNAL(triggered()), this, SLOT(desactiverBip()));
    QObject::connect(nbVariable, SIGNAL(triggered()), this, SLOT(choixNombreVariable()));

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
    for(Pile::iterator it=pile->begin(); it!=pile->end(); ++it){
        vuePile->setItem(row, 0, new QTableWidgetItem(QString::number((*it).getValue())));
        row++;
    }
}

void QComputer::getNextCommande(){
    controleur->commande(commande->text());

    message->setText(pile->getMessage());

    if(bipsonor==true){
        if(pile->getMessage()!="")
            Beep(523,200);
    }

    commande->clear();
}

void QComputer::choixNombreVariable(){
    int variable = QInputDialog::getInt(this, "Nombre à afficher", "Combien de variable voulez-vous afficher dans la pile ?"
                                        ,pile->getNbItemsToAffiche(),1);

    int nbchanger = variable-pile->getNbItemsToAffiche();
    if(nbchanger>0){
        for(int i(0); i<nbchanger; i++)
            vuePile->insertRow(vuePile->rowCount());
    }
    else{
        for(int i = pile->getNbItemsToAffiche(); i>variable; i--)
            vuePile->removeRow(i-1);
    }

    pile->setNbItemsToAffiche(variable);

    vuePile->repaint();
    refresh();
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
