#include "label.h"
#include <QPushButton>
#include <QMouseEvent>

void Label::mousePressEvent(QMouseEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if(mouseEvent->button() == Qt::LeftButton)
        emit clicked();
    QLabel::mousePressEvent(event);
}
