#ifndef SLIDER_H
#define SLIDER_H

#include <QDialog>
#include"image.h"
#include"mainwindow.h"
namespace Ui {
    class slider;
}

class slider : public QDialog
{
    Q_OBJECT

public:
    explicit slider(QWidget *parent = 0,int min=0,int max=100,int current=50,QString text="",int flag=1);
    ~slider();

private:
    Ui::slider *ui;

};

#endif // SLIDER_H
