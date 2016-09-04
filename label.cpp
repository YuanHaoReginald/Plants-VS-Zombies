#include "label.h"
#include <QPushButton>
#include <QMouseEvent>

Label::Label(QWidget *parent) : QLabel(parent)
{
    setParent(parent);
}

void Label::mousePressEvent(QMouseEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if(mouseEvent->button() == Qt::LeftButton)
        emit clicked();
    QLabel::mousePressEvent(event);
}
