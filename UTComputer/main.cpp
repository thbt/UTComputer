#include <QApplication>
#include "qcomputer.h"



int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QComputer fenetre;
    fenetre.show();
    return app.exec();
}




/*
    //Exo 1
    QApplication app(argc, argv);

    QPushButton* button1 = new QPushButton("Quitter");
    QPushButton* button2 = new QPushButton("Coucou");
    button1->show();
    button2->show();
    QObject::connect(button1, SIGNAL(clicked()), &app, SLOT(quit()));
    QObject::connect(button1, SIGNAL(clicked()), &app, SLOT(show()));

    QApplication app(argc, argv);
    QWidget fenetre;
    fenetre.setFixedSize(200, 200);

    QVBoxLayout *LayoutPrincipale = new QVBoxLayout;
    QHBoxLayout *LayoutBas = new QHBoxLayout;
    QVBoxLayout *LayoutCalcule = new QVBoxLayout;
    QVBoxLayout *LayoutChiffre = new QVBoxLayout;
    QHBoxLayout *layoutLigne1 = new QHBoxLayout;
    QHBoxLayout *layoutLigne2 = new QHBoxLayout;
    QHBoxLayout *layoutLigne3 = new QHBoxLayout;


    //LIGNE
    QLineEdit ligne;

    //BOUTON
    QPushButton button1("1");
    QPushButton button2("2");
    QPushButton button3("3");
    QPushButton button4("4");
    QPushButton button5("5");
    QPushButton button6("6");
    QPushButton button7("7");
    QPushButton button8("8");
    QPushButton button9("9");
    QPushButton button0("0");
    QPushButton buttonplus("+");
    QPushButton buttonmoins("-");
    QPushButton buttonfois("*");
    QPushButton buttondiv("/");
    QPushButton buttonentree("Entrée");

    LayoutPrincipale->addWidget(&ligne);
    LayoutPrincipale->addLayout(LayoutBas);

    LayoutChiffre->addLayout(layoutLigne1);
    LayoutChiffre->addLayout(layoutLigne2);
    LayoutChiffre->addLayout(layoutLigne3);
    LayoutChiffre->addWidget(&button0);

    layoutLigne1->addWidget(&button7);
    layoutLigne1->addWidget(&button8);
    layoutLigne1->addWidget(&button9);

    layoutLigne2->addWidget(&button4);
    layoutLigne2->addWidget(&button5);
    layoutLigne2->addWidget(&button6);

    layoutLigne3->addWidget(&button1);
    layoutLigne3->addWidget(&button2);
    layoutLigne3->addWidget(&button3);

    LayoutCalcule->addWidget(&buttonplus);
    LayoutCalcule->addWidget(&buttonmoins);
    LayoutCalcule->addWidget(&buttonfois);
    LayoutCalcule->addWidget(&buttondiv);
    LayoutCalcule->addWidget(&buttonentree);

    LayoutBas->addLayout(LayoutChiffre);
    LayoutBas->addLayout(LayoutCalcule);

    fenetre.setLayout(LayoutPrincipale);
    fenetre.show();


*/
