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
    int wchange;//����ͼ����ת
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
    void xuanzhuan();//��ȡ��ת�Ƕ�
    void makexuanzhuan(int a);//������ת
    void pingyi();
    void caiyang(int);//�������
    void getcaiyang();//��ȡ�������
    void lianghua();//�����ȼ�
    void weipingmian();
    void ContrastUp();//�Աȶ���ǿ
    void Negative();//��Ƭ
    void GammaTransformation();//٤��任
    void Logarithm();//�����任
    void Neighborhood(int );//����ƽ����
    void NeighborH0();//ģ��һ
    void NeighborH1();
    void NeighborH2();
    void RobertsSharpen();
    void LaplaceSharpen();
    void HighPassSharpen();
    void showconvolution();//����������
    void convolution();//������
    void GrayPallet();//��ɫ��ͼ��ҶȻ�
    void Transform();//���ͼ��ת256ɫ
    void Kirsch();//Kirsch���ӱ�Ե���
    void GratingTrack();//��դɨ����ٷ�
    void ToThin();//ϸ��
    void houghTransform();//����任
    void houghCircleTransform();//����任���Բ
    void huffmanCoding();//����������
    void huffmanDecode();//����������
    void getRgb_num();
    void fanoCoding();//fano����
    void fanoDecode();//fano����
    void runCoding();//�γ̱���
    void runDecode();//�γ̽���
};




class information:public QWidget//��ʾͼƬ��Ϣ����
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QPaintEvent *);
};


#endif // IMAGEWIDGET_H
