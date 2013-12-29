#ifndef GRAY_MAP_H
#define GRAY_MAP_H

#include <QWidget>
#include "image.h"
#include<math.h>
namespace Ui {
class gray_map;
}

class gray_map : public QWidget
{
    Q_OBJECT

public:
    explicit gray_map(QWidget *parent = 0);
    ~gray_map();
    QPainter *painter;
    QPixmap *pix;
    double  Statistics[256];
    double  StatisticsS[256];
    int w;//label 的宽度
    int h;//label 的长度
    int ww;//图像的宽度
    int hh;//图像的长度
    bool IsDimodal();
    void paintall();
    void painthistogram(int );
public slots:
    void GetMinimumThreshold();
private:
    Ui::gray_map *ui;

};

#endif // GRAY_MAP_H
