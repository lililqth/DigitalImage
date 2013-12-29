#ifndef SHOWCOLORTABLE_H
#define SHOWCOLORTABLE_H

#include <QDialog>

namespace Ui {
    class showcolortable;
}

class showcolortable : public QDialog
{
    Q_OBJECT

public:
    explicit showcolortable(QWidget *parent = 0);
    ~showcolortable();

private:
    Ui::showcolortable *ui;
};

#endif // SHOWCOLORTABLE_H
