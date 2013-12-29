#include "mainwindow.h"
#include "ui_mainwindow.h"
extern QImage img;
extern QString filename;
extern int flagright;
openimage *openpic;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    this->setFixedSize(1080,500);//设置窗口大小
    openpic = new openimage();//添加显示图片
    origin = new showorigin();//添加显示原始图片
    QWidget * cenwidget= new QWidget(this);
    setCentralWidget(cenwidget);
    cenwidget->resize(QSize(this->width(),this->height()));
    QHBoxLayout *layout = new QHBoxLayout(cenwidget);//设置主控件//  layout->setAlignment(Qt::AlignCenter);
    QVBoxLayout *layoutleft = new QVBoxLayout();
    QVBoxLayout *layoutright = new QVBoxLayout();
    QLabel * labelleft = new QLabel(cenwidget);

    QLabel * labelright = new QLabel(cenwidget);


    QPushButton * showgrayleft = new QPushButton(QString::fromLocal8Bit("灰度直方图"),cenwidget);
    connect(showgrayleft,SIGNAL(clicked()),this,SLOT(creatzhifangtuorigin()));
    QPushButton * showgrayright = new QPushButton(QString::fromLocal8Bit("灰度直方图"),cenwidget);
    connect(showgrayright,SIGNAL(clicked()),this,SLOT(creatzhifangtu()));


    labelleft->setText(QString::fromLocal8Bit("原始图像"));
    labelright->setText(QString::fromLocal8Bit("修改后的图像"));
    layoutleft->addWidget(labelleft);//添加标题
    layoutright->addWidget(labelright);

    layoutleft->addWidget(origin);//添加图片
    layoutright->addWidget(openpic);

    layoutleft->addWidget(showgrayleft);//添加按钮
    layoutright->addWidget(showgrayright);

    layoutleft->addStretch(0);//添加弹簧
    layoutright->addStretch(0);

    layout->addLayout(layoutleft);
    layout->addLayout(layoutright);
    createActions();
    createMenus();
    cenwidget->setLayout(layout);
    cenwidget->show();
}

void MainWindow::createActions(){

    connect(openpic,SIGNAL(updateoriginshow()),origin,SLOT(update()));
    openaction = new QAction(QString::fromLocal8Bit("打开"), this);
    connect(openaction,SIGNAL(triggered()),openpic,SLOT(openImage()));

    tograyaction = new QAction(QString::fromLocal8Bit("灰度化"),this);
    connect(tograyaction,SIGNAL(triggered()),openpic,SLOT(togray()));
    erzhiaction = new QAction(QString::fromLocal8Bit("二值化"),this);
    connect(erzhiaction,SIGNAL(triggered()),openpic,SLOT(erzhi()));
    saveaction = new QAction(QString::fromLocal8Bit("保存"),this);
    connect(saveaction,SIGNAL(triggered()),openpic,SLOT(saveimg()));
   // zhifangtuaction = new QAction(QString::fromLocal8Bit("灰度直方图"),this);
    //connect(zhifangtuaction,SIGNAL(triggered()),this,SLOT(creatzhifangtu()));
    junhenghuaaction = new QAction(QString::fromLocal8Bit("均衡化"),this);
    connect(junhenghuaaction,SIGNAL(triggered()),openpic,SLOT(junhenghua()));

    suofangzuijinlingaction = new QAction(QString::fromLocal8Bit("最近邻缩放"),this);
    connect(suofangzuijinlingaction,SIGNAL(triggered()),openpic,SLOT(suofangzuijin()));
    suofangshaungxianxingaction = new QAction(QString::fromLocal8Bit("双线性缩放"),this);
    connect(suofangshaungxianxingaction,SIGNAL(triggered()),openpic,SLOT(suofangxianxing()));
    jingxiangaction = new QAction(QString::fromLocal8Bit("镜像"),this);
    connect(jingxiangaction,SIGNAL(triggered()),openpic,SLOT(jingxiang()));
    xuanzhuanaction = new QAction(QString::fromLocal8Bit("旋转"),this);
    connect(xuanzhuanaction,SIGNAL(triggered()),openpic,SLOT(xuanzhuan()));
    pingyiaction = new QAction(QString::fromLocal8Bit("平移"),this);
    connect(pingyiaction,SIGNAL(triggered()),openpic,SLOT(pingyi()));

    showinfaction = new QAction(QString::fromLocal8Bit("信息"),this);
    connect(showinfaction,SIGNAL(triggered()),this,SLOT(showinformation()));

    caiyangaction = new QAction(QString::fromLocal8Bit("采样间隔"),this);
    connect(caiyangaction,SIGNAL(triggered()),openpic,SLOT(getcaiyang()));
    lianghuaaction = new QAction(QString::fromLocal8Bit("量化等级"),this);
    connect(lianghuaaction,SIGNAL(triggered()),openpic,SLOT(lianghua()));
    weipingmianaction = new QAction(QString::fromLocal8Bit("位平面分离"),this);
    connect(weipingmianaction,SIGNAL(triggered()),openpic,SLOT(weipingmian()));

    ContrastUpAction = new QAction(QString::fromLocal8Bit("对比度增强"),this);
    connect(ContrastUpAction,SIGNAL(triggered()),openpic,SLOT(ContrastUp()));
    NegativeAction = new QAction(QString::fromLocal8Bit("负片"),this);
    connect(NegativeAction,SIGNAL(triggered()),openpic,SLOT(Negative()));
    GammaTransformationAction = new QAction(QString::fromLocal8Bit("伽马变换(Gamma=5.0)"),this);
    connect(GammaTransformationAction,SIGNAL(triggered()),openpic,SLOT(GammaTransformation()));
    LogarithmAction = new QAction(QString::fromLocal8Bit("对数变换(v=200)"),this);
    connect(LogarithmAction,SIGNAL(triggered()),openpic,SLOT(Logarithm()));

    NeighbourhoodH0 = new QAction(QString::fromLocal8Bit("邻域平均法模板一"),this);
    connect(NeighbourhoodH0,SIGNAL(triggered()),openpic,SLOT(NeighborH0()));
    NeighbourhoodH1 = new QAction(QString::fromLocal8Bit("邻域平均法模板二"),this);
    connect(NeighbourhoodH1,SIGNAL(triggered()),openpic,SLOT(NeighborH1()));
    NeighbourhoodH2 = new QAction(QString::fromLocal8Bit("邻域平均法模板三"),this);
    connect(NeighbourhoodH2,SIGNAL(triggered()),openpic,SLOT(NeighborH2()));

    RobertsSharpenAction = new QAction(QString::fromLocal8Bit("罗伯茨差分(彩色)"),this);
    connect(RobertsSharpenAction,SIGNAL(triggered()),openpic,SLOT(RobertsSharpen()));
    LaplaceSharpenAction = new QAction(QString::fromLocal8Bit("拉普拉斯算子"),this);
    connect(LaplaceSharpenAction,SIGNAL(triggered()),openpic,SLOT(LaplaceSharpen()));
    HighPassSharpenAction = new QAction(QString::fromLocal8Bit("高通滤波"),this);
    connect(HighPassSharpenAction,SIGNAL(triggered()),openpic,SLOT(HighPassSharpen()));
    ConvolutionAction = new QAction(QString::fromLocal8Bit("任意模板卷积"),this);
    connect(ConvolutionAction,SIGNAL(triggered()),openpic,SLOT(showconvolution()));

    ShowColorTableAction = new QAction(QString::fromLocal8Bit("调色板"),this);
    connect(ShowColorTableAction,SIGNAL(triggered()),SLOT(ShowColorTable()));

    GrayPalletAction = new QAction(QString::fromLocal8Bit("调色板图像灰度化"),this);
    connect(GrayPalletAction,SIGNAL(triggered()),openpic,SLOT(GrayPallet()));

    TransformAction = new QAction(QString::fromLocal8Bit("真彩色转256色"),this);
    connect(TransformAction,SIGNAL(triggered()),openpic,SLOT(Transform()));

    KirschAction = new QAction(QString::fromLocal8Bit("Kirsch方向算子"),this);
    connect(KirschAction,SIGNAL(triggered()),openpic,SLOT(Kirsch()));

    GratingTrackAction = new QAction(QString::fromLocal8Bit("光栅扫描"),this);
    connect(GratingTrackAction,SIGNAL(triggered()),openpic,SLOT(GratingTrack()));

    ToThinAction = new QAction(QString::fromLocal8Bit("细化"),this);
    connect(ToThinAction,SIGNAL(triggered()),openpic,SLOT(ToThin()));
    houghTransformAction = new QAction(QString::fromLocal8Bit("霍夫变换检测直线"),this);
    connect(houghTransformAction,SIGNAL(triggered()),openpic,SLOT(houghTransform()));
    houghTransformCircleAction = new QAction(QString::fromLocal8Bit("霍夫变换检测圆"),this);
    connect(houghTransformCircleAction,SIGNAL(triggered()),openpic,SLOT(houghCircleTransform()));

    HuffmanCodingAction = new QAction(QString::fromLocal8Bit("哈夫曼编码"),this);
    connect(HuffmanCodingAction,SIGNAL(triggered()),openpic,SLOT(huffmanCoding()));
    huffmanDecodeAction = new QAction(QString::fromLocal8Bit("哈夫曼解码"),this);
    connect(huffmanDecodeAction,SIGNAL(triggered()),openpic,SLOT(huffmanDecode()));
    fanoCodingAction = new QAction(QString::fromLocal8Bit("fano编码"),this);
    connect(fanoCodingAction,SIGNAL(triggered()),openpic,SLOT(fanoCoding()));
    fanoDecodeAction = new QAction(QString::fromLocal8Bit("fano解码"),this);
    connect(fanoDecodeAction,SIGNAL(triggered()),openpic,SLOT(fanoDecode()));
    runCodingAction = new QAction(QString::fromLocal8Bit("游程编码"),this);
    connect(runCodingAction,SIGNAL(triggered()),openpic,SLOT(runCoding()));
    runDecodeAction = new QAction(QString::fromLocal8Bit("游程解码"),this);
    connect(runDecodeAction,SIGNAL(triggered()),openpic,SLOT(runDecode()));
}



void MainWindow::createMenus()
{
    filemenu = menuBar()->addMenu(QString::fromLocal8Bit("文件"));
    filemenu->addAction(openaction);
    filemenu->addAction(saveaction);


    PointOperationsMenu = menuBar()->addMenu(QString::fromLocal8Bit("点运算"));
    PointOperationsMenu->addAction(tograyaction);
    PointOperationsMenu->addAction(GrayPalletAction);
    PointOperationsMenu->addAction(erzhiaction);
    PointOperationsMenu->addAction(junhenghuaaction);
    PointOperationsMenu->addAction(ContrastUpAction);
    PointOperationsMenu->addAction(NegativeAction);
    PointOperationsMenu->addAction(GammaTransformationAction);
    PointOperationsMenu->addAction(LogarithmAction);



    GeometricOperationMenu = menuBar()->addMenu(QString::fromLocal8Bit("几何运算"));
    GeometricOperationMenu->addAction(xuanzhuanaction);
    GeometricOperationMenu->addAction(jingxiangaction);
    suofangmenu = GeometricOperationMenu->addMenu(QString::fromLocal8Bit("缩放"));
    suofangmenu->addAction(suofangzuijinlingaction);
    suofangmenu->addAction(suofangshaungxianxingaction);
    GeometricOperationMenu->addAction(pingyiaction);

    quantizationMenu = menuBar()->addMenu(QString::fromLocal8Bit("采样与量化"));
    quantizationMenu->addAction(caiyangaction);
    quantizationMenu->addAction(lianghuaaction);
    quantizationMenu->addAction(weipingmianaction);

    ImageIntensificationMenu = menuBar()->addMenu(QString::fromLocal8Bit("图像增强"));
    SmoothnessMenu = ImageIntensificationMenu->addMenu(QString::fromLocal8Bit("平滑"));
    SharpenMenu = ImageIntensificationMenu->addMenu(QString::fromLocal8Bit("锐化"));
    SmoothnessMenu->addAction(NeighbourhoodH0);
    SmoothnessMenu->addAction(NeighbourhoodH1);
    SmoothnessMenu->addAction(NeighbourhoodH2);
    SharpenMenu->addAction(RobertsSharpenAction);
    SharpenMenu->addAction(LaplaceSharpenAction);
    SharpenMenu->addAction(HighPassSharpenAction);
    ImageIntensificationMenu->addAction(ConvolutionAction);

    EdgeDetectionMenu = menuBar()->addMenu(QString::fromLocal8Bit("边缘检测"));
    EdgeDetectionMenu->addAction(KirschAction);
    EdgeDetectionMenu->addAction(LaplaceSharpenAction);
    EdgeDetectionMenu->addAction(GratingTrackAction);

    MathMorphology = menuBar()->addMenu(QString::fromLocal8Bit("数学形态学"));
    MathMorphology->addAction(ToThinAction);
    MathMorphology->addAction(houghTransformAction);
    MathMorphology->addAction(houghTransformCircleAction);

    codingMenu = menuBar()->addMenu(QString::fromLocal8Bit("编码解码"));
    codingMenu->addAction(HuffmanCodingAction);
   // codingMenu->addAction(huffmanDecodeAction);
    codingMenu->addAction(fanoCodingAction);
   // codingMenu->addAction(fanoDecodeAction);
    codingMenu->addAction(runCodingAction);
    codingMenu->addAction(runDecodeAction);

    menuBar()->addAction(showinfaction);
    menuBar()->addAction(ShowColorTableAction);
    menuBar()->addAction(TransformAction);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatzhifangtuorigin()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    flagright=0;
    gray_map *map = new gray_map();
    map->setFixedSize(330,300);
    map->move(20,300);
    map->show();
}
void MainWindow::creatzhifangtu()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    flagright=1;
    gray_map *map1 = new gray_map();
    map1->setFixedSize(330,300);
    map1->move(500,300);
    map1->show();
}

void MainWindow::showinformation()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }

    if(filename[filename.length()-3]!='G'&&filename[filename.length()-3]!='g')
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("仅能解析GIF文件格式！"));
        return;
    }

    information * inf = new information();
    inf->setFixedSize(200,300);
    inf->setWindowTitle(QString::fromLocal8Bit("信息"));
    inf->move(this->x()+100,this->y()+100);
    inf->setWindowModality(Qt::ApplicationModal);
    inf->show();
    return;
}

void MainWindow::ShowColorTable()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    if((img.colorTable()).isEmpty())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("调色板不存在！"));
        return;
    }
    showcolortable *showtable = new showcolortable(this);
    showtable->show();
}
