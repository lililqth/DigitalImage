#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H
#include<QImage>
#include<QPaintEvent>
#include<QFileDialog>
#include<QMessageBox>
#include<QFileDialog>
#include<QPainter>
#include<QLabel>
#include<QRgb>
#include <QTextCodec>
#include <QApplication>
#include<QDialog>
#include<QVBoxLayout>
#include<QPen>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QPushButton>
#include<QInputDialog>
#include<QFile>
#include<QDataStream>
#include<QTextEdit>
#include<QPixmap>
#include<math.h>
#include<QTextStream>
#include"getmatrix.h"
#include"slider.h"
#include"HuffmanTree.cpp"



class openimage:public QWidget
{
    Q_OBJECT

public:
    int wchange;//用于图像旋转
    int hchange;
    int wwchange;
    int hhchange;
    QString savelocate;
    getmatrix *martrix;
    double multiple;
    openimage();
    ~openimage();
protected:
    void paintEvent(QPaintEvent*);
signals:
    void updateoriginshow();
public slots:
    void openImage();
    void graycore(int flag);
    void togray();
    void erzhi();
    void saveimg();
    void junhenghua();
    void suofangzuijin();
    void suofangxianxing();
    void jingxiang();
    void xuanzhuan();//获取旋转角度
    void makexuanzhuan(int a);//进行旋转
    void pingyi();
    void caiyang(int);//采样间隔
    void getcaiyang();//获取采样间隔
    void lianghua();//量化等级
    void weipingmian();
    void ContrastUp();//对比度增强
    void Negative();//负片
    void GammaTransformation();//伽马变换
    void Logarithm();//对数变换
    void Neighborhood(int );//邻域平均法
    void NeighborH0();//模板一
    void NeighborH1();
    void NeighborH2();
    void RobertsSharpen();
    void LaplaceSharpen();
    void HighPassSharpen();
    void showconvolution();//输入卷积矩阵
    void convolution();//计算卷积
    void GrayPallet();//调色板图像灰度化
    void Transform();//真彩图像转256色
    void Kirsch();//Kirsch算子边缘检测
    void GratingTrack();//光栅扫面跟踪法
    void ToThin();//细化
    void houghTransform();//霍夫变换
    void houghCircleTransform();//霍夫变换检测圆
    void huffmanCoding();//哈夫曼编码
    void huffmanDecode();//哈夫曼解码
    void getRgb_num();
    void fanoCoding();//fano编码
    void fanoDecode();//fano解码
    void runCoding();//游程编码
    void runDecode();//游程解码
};




class information:public QWidget//显示图片信息窗口
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QPaintEvent *);
};


#endif // IMAGEWIDGET_H
