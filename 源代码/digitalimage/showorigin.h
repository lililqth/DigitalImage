#ifndef SHOWORIGIN_H
#define SHOWORIGIN_H
#include<QImage>
#include<QPaintEvent>
#include<QPainter>
#include<QLabel>
#include <QApplication>

class showorigin:public QWidget
{
    Q_OBJECT
public :
    showorigin();
    void paintEvent(QPaintEvent*);
    QPainter  painterorigin;
};
#endif // SHOWORIGIN_H
