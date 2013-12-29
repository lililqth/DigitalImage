#ifndef GETMATRIX_H
#define GETMATRIX_H

#include <QDialog>

namespace Ui {
    class getmatrix;
}

class getmatrix : public QDialog
{
    Q_OBJECT

public:
    explicit getmatrix(QWidget *parent = 0);
    ~getmatrix();
    int m00,m01,m02,m10,m11,m12,m20,m21,m22;

public slots:
    void getm();
    void clickokbutton();
    void clickcancelbutton();

private:
    Ui::getmatrix *ui;
};

#endif // GETMATRIX_H
