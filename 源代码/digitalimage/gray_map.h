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
    int w;//label �Ŀ��
    int h;//label �ĳ���
    int ww;//ͼ��Ŀ��
    int hh;//ͼ��ĳ���
    bool IsDimodal();
    void paintall();
    void painthistogram(int );
public slots:
    void GetMinimumThreshold();
private:
    Ui::gray_map *ui;

};

#endif // GRAY_MAP_H
