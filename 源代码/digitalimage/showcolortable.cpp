#include "showcolortable.h"
#include "ui_showcolortable.h"
extern QImage img;
extern  QImage imgchange;
showcolortable::showcolortable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showcolortable)
{
    ui->setupUi(this);
    int num=img.numColors();

    QString text = QString::fromLocal8Bit("调色板数量为：");
    text+=QString::number(num);
    text+="\n";
    text+=QString::fromLocal8Bit("颜色深度为:");
    text+=QString::number( img.depth());

    text+="\n";
   for(int i=0;i<num;i++)
    {
        if(i>=0&&i<9)
        {
            text+=QString::number(i+1)+".  ("+QString::number(qRed(img.color(i)))+","+QString::number(qGreen(img.color(i)))+","+QString::number(qBlue(img.color(i)))+")";
        }
        else if(i>=9&&i<99)
        {
            text+=QString::number(i+1)+". ("+QString::number(qRed(img.color(i)))+","+QString::number(qGreen(img.color(i)))+","+QString::number(qBlue(img.color(i)))+")";
        }
        else
        {
             text+=QString::number(i+1)+".("+QString::number(qRed(img.color(i)))+","+QString::number(qGreen(img.color(i)))+","+QString::number(qBlue(img.color(i)))+")";
        }
        text+="\n";
    }
    ui->textEdit->setText(text);
}

showcolortable::~showcolortable()
{
    delete ui;
}
