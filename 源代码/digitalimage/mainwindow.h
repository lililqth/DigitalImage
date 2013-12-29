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
    QAction *ContrastUpAction;//对比度增强
    QAction *NegativeAction;//负片
    QAction *GammaTransformationAction;//伽马变换
    QAction *LogarithmAction;//对数变换

    QAction *NeighbourhoodH0;
    QAction *NeighbourhoodH1;
    QAction *NeighbourhoodH2;

    QAction *RobertsSharpenAction;//罗伯兹差分
    QAction *LaplaceSharpenAction;//拉普拉斯算子
    QAction *HighPassSharpenAction;//高通滤波
    QAction *ConvolutionAction;//卷积

    QAction *ShowColorTableAction;//分析调色板

    QAction *GrayPalletAction;//调色板图像的灰度化
    QAction *TransformAction;//真彩转256色
    QAction *KirschAction;//Kirsch边缘检测
    QAction *GratingTrackAction;//光栅扫描跟踪
    QAction *ToThinAction;//细化
    QAction *houghTransformAction;//霍夫变换直线
    QAction *houghTransformCircleAction;//霍夫变换圆
    QAction *HuffmanCodingAction;//哈夫曼编码
    QAction *huffmanDecodeAction;//哈夫曼解码
    QAction *fanoCodingAction;//fano编码
    QAction *fanoDecodeAction;//fano解码
    QAction *runCodingAction;//游程编码
    QAction *runDecodeAction;//游程解码
    QMenu *filemenu;
    QMenu *suofangmenu;
    QMenu *PointOperationsMenu;
    QMenu *GeometricOperationMenu;
    QMenu *quantizationMenu;//量化
    QMenu *ImageIntensificationMenu;//图像增强
    QMenu *SmoothnessMenu; //图像平滑
    QMenu *SharpenMenu;//图像锐化
    QMenu *EdgeDetectionMenu;//边缘检测
    QMenu *MathMorphology;//数学形态学
    QMenu *codingMenu;//编码解码
    QToolBar *toolbar;

private:
    Ui::MainWindow *ui;
public slots:
    void creatzhifangtu();
    void creatzhifangtuorigin();
    void showinformation();
    void ShowColorTable();//分析调色板
};



#endif // MAINWINDOW_H
