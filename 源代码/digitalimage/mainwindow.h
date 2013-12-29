#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QToolBar>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSize>
#include <QTextCodec>
#include <QAction>
#include<QMenu>
#include<QString>
#include<QLabel>
#include"image.h"
#include"gray_map.h"
#include"getmatrix.h"
#include"showorigin.h"
#include"showcolortable.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //openimage *open;
    showorigin *origin;
    void createActions();
    void createMenus();
    QAction *openaction;
    QAction *tograyaction;
    QAction *saveaction;
    QAction *erzhiaction;
   // QAction *zhifangtuaction;
    QAction *junhenghuaaction;
    QAction *suofangzuijinlingaction;
    QAction *suofangshaungxianxingaction;
    QAction *jingxiangaction;
    QAction *xuanzhuanaction;
    QAction *pingyiaction;
    QAction *showinfaction;
    QAction *caiyangaction;
    QAction *lianghuaaction;
    QAction *weipingmianaction;
    QAction *ContrastUpAction;//�Աȶ���ǿ
    QAction *NegativeAction;//��Ƭ
    QAction *GammaTransformationAction;//٤��任
    QAction *LogarithmAction;//�����任

    QAction *NeighbourhoodH0;
    QAction *NeighbourhoodH1;
    QAction *NeighbourhoodH2;

    QAction *RobertsSharpenAction;//�޲��Ȳ��
    QAction *LaplaceSharpenAction;//������˹����
    QAction *HighPassSharpenAction;//��ͨ�˲�
    QAction *ConvolutionAction;//���

    QAction *ShowColorTableAction;//������ɫ��

    QAction *GrayPalletAction;//��ɫ��ͼ��ĻҶȻ�
    QAction *TransformAction;//���ת256ɫ
    QAction *KirschAction;//Kirsch��Ե���
    QAction *GratingTrackAction;//��դɨ�����
    QAction *ToThinAction;//ϸ��
    QAction *houghTransformAction;//����任ֱ��
    QAction *houghTransformCircleAction;//����任Բ
    QAction *HuffmanCodingAction;//����������
    QAction *huffmanDecodeAction;//����������
    QAction *fanoCodingAction;//fano����
    QAction *fanoDecodeAction;//fano����
    QAction *runCodingAction;//�γ̱���
    QAction *runDecodeAction;//�γ̽���
    QMenu *filemenu;
    QMenu *suofangmenu;
    QMenu *PointOperationsMenu;
    QMenu *GeometricOperationMenu;
    QMenu *quantizationMenu;//����
    QMenu *ImageIntensificationMenu;//ͼ����ǿ
    QMenu *SmoothnessMenu; //ͼ��ƽ��
    QMenu *SharpenMenu;//ͼ����
    QMenu *EdgeDetectionMenu;//��Ե���
    QMenu *MathMorphology;//��ѧ��̬ѧ
    QMenu *codingMenu;//�������
    QToolBar *toolbar;

private:
    Ui::MainWindow *ui;
public slots:
    void creatzhifangtu();
    void creatzhifangtuorigin();
    void showinformation();
    void ShowColorTable();//������ɫ��
};



#endif // MAINWINDOW_H
