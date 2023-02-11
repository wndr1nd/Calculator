#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QLineEdit>
#include <QWidget>
#include <QLabel>
#include "mybutton.h"


class Calculator:public QWidget
{
    Q_OBJECT
public:
    Calculator();

private slots:
    void digitClicked();
    void doubleOperand();
    void unarOperand();
    void equal();
    void backspace();
    void point();
    void changeSign();

private:
    MyButton* createButton(const QString& text, const char * member);
    void abortOperation();
    QLineEdit *display;
    MyButton* operation;
    double operand;
    QString pending_operation;
    QString plus_sign = "+";
    QString minus_sign = "-";
    QString div_sign = "/";
    QString pow_sign = "*";
    QString change_sign = "+/-";
    QString square_sign = "x²";
    QString divided_sign = "1/x";


    MyButton * buttlist[10];

};

#endif // CALCULATOR_H
