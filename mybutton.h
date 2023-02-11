#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QToolButton>

class MyButton: public QToolButton
{
public:
    explicit MyButton(const QString& text, QWidget *parent = nullptr)
    {
        setText(text);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }
};

#endif // MYBUTTON_H
