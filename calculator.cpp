#include "calculator.h"
#include <QGridLayout>
#include <QToolButton>
#include <QDebug>
#include <vector>

Calculator::Calculator()
{
    display = new QLineEdit;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);

    display->setReadOnly(true);

    display->setAlignment(Qt::AlignRight);


    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 10);
    display->setFont(font);
    display->setFixedHeight(100);

    display->setText("0");

    for (int i = 0; i < 10; ++i)
    {
        buttlist[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }


    MyButton * backspaceButt = createButton("Delete", SLOT(backspace()));
    MyButton * pointButt = createButton(".", SLOT(point()));
    MyButton * minusButt = createButton(minus_sign, SLOT(doubleOperand()));
    MyButton * plusButt = createButton(plus_sign, SLOT(doubleOperand()));
    MyButton * powButt = createButton(pow_sign, SLOT(doubleOperand()));
    MyButton * divButt = createButton(div_sign, SLOT(doubleOperand()));
    MyButton * equalButt = createButton("=", SLOT(equal()));
    MyButton * changeButt = createButton(change_sign, SLOT(changeSign()));
    MyButton * squareButt = createButton(square_sign, SLOT(unarOperand()));
    MyButton * dividedButt = createButton(divided_sign, SLOT(unarOperand()));

    minusButt->setFont(font);
    pointButt->setFont(font);
    backspaceButt->setFont(font);
    plusButt->setFont(font);
    powButt->setFont(font);
    divButt->setFont(font);
    equalButt->setFont(font);
    changeButt->setFont(font);
    squareButt->setFont(font);
    dividedButt->setFont(font);

    for (int i = 0; i < 10; ++i)
    {
        buttlist[i]->setFont(font);
    }


    minusButt->setCheckable(true);
    plusButt->setCheckable(true);
    powButt->setCheckable(true);
    divButt->setCheckable(true);

    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButt, 3, 4, 1, 1);
    mainLayout->addWidget(buttlist[0], 7, 1);
    mainLayout->addWidget(pointButt, 7, 2);
    mainLayout->addWidget(divButt, 4, 4);
    mainLayout->addWidget(minusButt, 6, 4);
    mainLayout->addWidget(plusButt, 7, 4);
    mainLayout->addWidget(powButt, 5, 4);
    mainLayout->addWidget(equalButt, 7, 3);
    mainLayout->addWidget(changeButt, 3, 1);
    mainLayout->addWidget(squareButt, 3, 3);
    mainLayout->addWidget(dividedButt, 3, 2);

    for (int i = 1; i < 10; ++i)
    {
        int row = ((9 - i) / 3) + 4;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(buttlist[i], row, column);
    }

    operation = nullptr;

    setLayout(mainLayout);


}


MyButton *Calculator::createButton(const QString &text, const char *member)
{
    MyButton *btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}


void Calculator::abortOperation()
{
    display->setText("error");
}


void Calculator::digitClicked()
{
    MyButton *btn = (MyButton *)sender();
    int dig = btn->text().toInt();

    if (display->text() == "0")
    {
        display->clear();

    }
    display->setText(display->text() + QString::number(dig));
}

void Calculator::doubleOperand()
{
    operation = (MyButton *)sender();

    operand = display->text().toDouble();

    display->clear();

    operation->setChecked(true);




}
void Calculator::unarOperand()
{
    MyButton *btn = (MyButton *)sender();
    double oper = display->text().toDouble();

    if (btn->text() == square_sign)
    {
        oper *= oper;
    }else if (btn->text() == divided_sign)
    {
        oper = 1/oper;
    }

    display->setText(QString::number(oper));
}

void Calculator::equal()
{
    double tmp = 0, second_operand;
    second_operand = display->text().toDouble();

    if (operation->text() == plus_sign && operation->isChecked())
    {
        tmp = operand + second_operand;

    }else if(operation->text() == minus_sign && operation->isChecked())
    {
        tmp = operand - second_operand;

    }else if (operation->text() == pow_sign && operation->isChecked())
    {
        tmp = operand * second_operand;

    }else if (operation->text() == div_sign && operation->isChecked())
    {
        if (second_operand == 0)
        {
            operation->setChecked(false);
            abortOperation();
            return;
        }
        tmp = operand / second_operand;
    }

    display->setText(QString::number(tmp, 'g', 15));
    operation->setChecked(false);

}
void Calculator::backspace()
{
    display->setText("0");
    if (operation)
    {
        if (operation->isChecked())
        {
            operation->setChecked(false);
        }
    }
}

void Calculator::point()
{
    if (!display->text().contains("."))
    {
        display->setText(display->text() + ".");
    }
}

void Calculator::changeSign()
{
    QString text = display->text();
    double res = text.toDouble();
    if (res > 0)
    {
        text.prepend("-");
    }
    else if (res < 0)
    {
        text.remove(0,1);
    }

    display->setText(text);

}
