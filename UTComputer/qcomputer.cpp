#include "qcomputer.h"

#include <QIcon>
#include <QCoreApplication>
#include <QDebug>
#include <windows.h>
#include <QInputDialog>

#include "Controller.h"

static bool bipsonor = true;
static bool cliquable = true;

QComputer::QComputer(QWidget *parent){
    setFixedSize(350,250);
    setWindowTitle("UTComputer");
    setWindowIcon(QIcon("D:/Cours/UTC/P16/LO21/UTComputer/Images/icone.jpg"));


    //pile = new Pile();
    //controleur = new Controleur(ExpressionManager::getInstance(),*pile);

    //Menu
    menuBar = new QMenuBar();
    menuFichier = menuBar->addMenu("&Fichier");
    menuVar = menuBar->addMenu("&Variable");
    menuProg = menuBar->addMenu("&Programme");
    menuCaract = menuBar->addMenu("&Caracteres spéciaux");

    //Action
    actionQuitter = new QAction("&Quitter", this);
    bipSonore = new QAction("&Desactiver bip sonore", this);
    nbVariable = new QAction("&Modifier affichage pile", this);
    clavierCliquable = new QAction("&Desactiver le clavier cliquable", this);;


    //Ajouts actions
    menuFichier->addAction(bipSonore);
    menuFichier->addAction(nbVariable);
    menuFichier->addAction(clavierCliquable);
    menuFichier->addAction(actionQuitter);



    //Layout
    LayoutPrincipale = new QVBoxLayout;
    LayoutMid = new QHBoxLayout;

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

    LayoutCliquable->addWidget(button3, 2, 0);
    LayoutCliquable->addWidget(button2, 2, 1);
    LayoutCliquable->addWidget(button1, 2, 2);
    LayoutCliquable->addWidget(buttonfois, 2, 5);

    LayoutCliquable->addWidget(button0, 3, 0, 1,3);
    LayoutCliquable->addWidget(buttonentree, 3, 5);


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

    commande = new QLineEdit();


    //Layout principale
    LayoutPrincipale->addWidget(message);
    LayoutPrincipale->addLayout(LayoutMid);
    LayoutPrincipale->addWidget(commande);

    //Layout milieu
    LayoutMid->addWidget(vuePile);
    LayoutMid->addWidget(WidgetCliquable);


    //Connect
    QObject::connect(&Controller::instance(), SIGNAL(changeState()), this, SLOT(refresh()));
    QObject::connect(&Controller::instance(), SIGNAL(showError(error)), this, SLOT(printError(error)));
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
    QObject::connect(clavierCliquable, SIGNAL(triggered()), this, SLOT(desactiverCliquable()));

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
