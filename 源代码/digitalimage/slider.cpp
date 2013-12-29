#include "slider.h"
#include "ui_slider.h"

extern openimage *openpic;
slider::slider(QWidget *parent,int min,int max,int current,QString text,int flag):
    QDialog(parent),
    ui(new Ui::slider)
{
    ui->setupUi(this);
    ui->horizontalSlider->setMinimum(min);
    ui->horizontalSlider->setMaximum(max);
    ui->horizontalSlider->setValue(current);
    ui->label->setText(text);
    ui->label_min->setText(QString::number(min));
    ui->label_max->setText(QString::number(max));
    if(flag==1)//Ðý×ª
    {
        connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),openpic,SLOT(makexuanzhuan(int)));
    }
    if(flag==2)
    {
        connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),openpic,SLOT(caiyang(int)));
    }
}


slider::~slider()
{
    delete ui;
}


