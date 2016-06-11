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
	std::map<std::string, std::string> variables;
	std::map<std::string, std::string> programs;
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

	void createAtome(std::string name, std::string value);
	void initAtome();
	void deleteAtome(std::string name);
	std::map<std::string, std::string> getVariables();
	std::map<std::string, std::string> getPrograms();
	std::string getPathVar();
	std::string getPathProg();
	void saveAtome();

signals :
    void changeState();
    void showError(std::string error);
};
