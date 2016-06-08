#include <QApplication>
#include <iostream>
#include "qcomputer.h"
#include "ExpressionParser.h"
#include <Windows.h>


int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QComputer fenetre;
    fenetre.show();

	parse("3+1*5");

    return app.exec();
}
