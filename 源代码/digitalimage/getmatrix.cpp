#include "getmatrix.h"
#include "ui_getmatrix.h"
#include "image.h"
getmatrix::getmatrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getmatrix)
{
    ui->setupUi(this);
    connect(ui->OkButton,SIGNAL(clicked()),this,SLOT(clickokbutton()));
    connect(ui->OkButton,SIGNAL(clicked()),parent,SLOT(convolution()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(clickcancelbutton()));
    m00=m01=m02=m10=m11=m12=m20=m21=m21=0;


}

getmatrix::~getmatrix()
{
    delete ui;
}

void getmatrix::getm()
{
    m00=ui->lineEdit_1->text().toInt();
    m01=ui->lineEdit_2->text().toInt();
    m02=ui->lineEdit_3->text().toInt();
    m10=ui->lineEdit_4->text().toInt();
    m11=ui->lineEdit_5->text().toInt();
    m12=ui->lineEdit_6->text().toInt();
    m20=ui->lineEdit_7->text().toInt();
    m21=ui->lineEdit_8->text().toInt();
    m22=ui->lineEdit_9->text().toInt();
}

void getmatrix::clickokbutton()
{
    getm();
    this->close();
}

void getmatrix::clickcancelbutton()
{
    this->close();
}


