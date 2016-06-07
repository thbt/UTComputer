#pragma once

#include <QObject>

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <stack>

#include "Stack.h"
#include "Operator.h"


class Controller : public QObject {
    Q_OBJECT

    Controller();

    unsigned int NumberDisplay;
    Stack stack;
    std::map<std::string, std::function<void(Stack* s)>> dispatcher;
	std::map<std::string, ILiteral*> vars;
    std::stack<StackMemento*> undoStack;
    std::stack<StackMemento*> redoStack;

public:
    static Controller& instance();

    void command(const std::string& str);
    void execute(std::string op);

    void undo();
    void redo();

    unsigned int getNbDisplay() const;
    void setNbDisplay(unsigned int nb);

	std::vector<std::string> getOperators();

    std::vector<ILiteral*>::const_reverse_iterator beginStack() const{
        return stack.begin();
    }

    std::vector<ILiteral*>::const_reverse_iterator endStack() const{
        return stack.end();
    }

signals :
    void changeState();
    void showError(std::string error);
};
