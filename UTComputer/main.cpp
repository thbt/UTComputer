#include <QApplication>
#include "qcomputer.h"
#include "ExpressionParser.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QComputer fenetre;
    fenetre.show();

	parse("3+1*5");

    return app.exec();
}
