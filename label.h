#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QMouseEvent>

class Label : public QLabel
{
    Q_OBJECT

public:
    explicit Label(QWidget *parent = 0) : QLabel(parent) { }

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();
};

#endif // LABEL_H
