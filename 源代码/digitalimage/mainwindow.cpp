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
    this->setFixedSize(1080,500);//���ô��ڴ�С
    openpic = new openimage();//�����ʾͼƬ
    origin = new showorigin();//�����ʾԭʼͼƬ
    QWidget * cenwidget= new QWidget(this);
    setCentralWidget(cenwidget);
    cenwidget->resize(QSize(this->width(),this->height()));
    QHBoxLayout *layout = new QHBoxLayout(cenwidget);//�������ؼ�//  layout->setAlignment(Qt::AlignCenter);
    QVBoxLayout *layoutleft = new QVBoxLayout();
    QVBoxLayout *layoutright = new QVBoxLayout();
    QLabel * labelleft = new QLabel(cenwidget);

    QLabel * labelright = new QLabel(cenwidget);


    QPushButton * showgrayleft = new QPushButton(QString::fromLocal8Bit("�Ҷ�ֱ��ͼ"),cenwidget);
    connect(showgrayleft,SIGNAL(clicked()),this,SLOT(creatzhifangtuorigin()));
    QPushButton * showgrayright = new QPushButton(QString::fromLocal8Bit("�Ҷ�ֱ��ͼ"),cenwidget);
    connect(showgrayright,SIGNAL(clicked()),this,SLOT(creatzhifangtu()));


    labelleft->setText(QString::fromLocal8Bit("ԭʼͼ��"));
    labelright->setText(QString::fromLocal8Bit("�޸ĺ��ͼ��"));
    layoutleft->addWidget(labelleft);//��ӱ���
    layoutright->addWidget(labelright);

    layoutleft->addWidget(origin);//���ͼƬ
    layoutright->addWidget(openpic);

    layoutleft->addWidget(showgrayleft);//��Ӱ�ť
    layoutright->addWidget(showgrayright);

    layoutleft->addStretch(0);//��ӵ���
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
    openaction = new QAction(QString::fromLocal8Bit("��"), this);
    connect(openaction,SIGNAL(triggered()),openpic,SLOT(openImage()));

    tograyaction = new QAction(QString::fromLocal8Bit("�ҶȻ�"),this);
    connect(tograyaction,SIGNAL(triggered()),openpic,SLOT(togray()));
    erzhiaction = new QAction(QString::fromLocal8Bit("��ֵ��"),this);
    connect(erzhiaction,SIGNAL(triggered()),openpic,SLOT(erzhi()));
    saveaction = new QAction(QString::fromLocal8Bit("����"),this);
    connect(saveaction,SIGNAL(triggered()),openpic,SLOT(saveimg()));
   // zhifangtuaction = new QAction(QString::fromLocal8Bit("�Ҷ�ֱ��ͼ"),this);
    //connect(zhifangtuaction,SIGNAL(triggered()),this,SLOT(creatzhifangtu()));
    junhenghuaaction = new QAction(QString::fromLocal8Bit("���⻯"),this);
    connect(junhenghuaaction,SIGNAL(triggered()),openpic,SLOT(junhenghua()));

    suofangzuijinlingaction = new QAction(QString::fromLocal8Bit("���������"),this);
    connect(suofangzuijinlingaction,SIGNAL(triggered()),openpic,SLOT(suofangzuijin()));
    suofangshaungxianxingaction = new QAction(QString::fromLocal8Bit("˫��������"),this);
    connect(suofangshaungxianxingaction,SIGNAL(triggered()),openpic,SLOT(suofangxianxing()));
    jingxiangaction = new QAction(QString::fromLocal8Bit("����"),this);
    connect(jingxiangaction,SIGNAL(triggered()),openpic,SLOT(jingxiang()));
    xuanzhuanaction = new QAction(QString::fromLocal8Bit("��ת"),this);
    connect(xuanzhuanaction,SIGNAL(triggered()),openpic,SLOT(xuanzhuan()));
    pingyiaction = new QAction(QString::fromLocal8Bit("ƽ��"),this);
    connect(pingyiaction,SIGNAL(triggered()),openpic,SLOT(pingyi()));

    showinfaction = new QAction(QString::fromLocal8Bit("��Ϣ"),this);
    connect(showinfaction,SIGNAL(triggered()),this,SLOT(showinformation()));

    caiyangaction = new QAction(QString::fromLocal8Bit("�������"),this);
    connect(caiyangaction,SIGNAL(triggered()),openpic,SLOT(getcaiyang()));
    lianghuaaction = new QAction(QString::fromLocal8Bit("�����ȼ�"),this);
    connect(lianghuaaction,SIGNAL(triggered()),openpic,SLOT(lianghua()));
    weipingmianaction = new QAction(QString::fromLocal8Bit("λƽ�����"),this);
    connect(weipingmianaction,SIGNAL(triggered()),openpic,SLOT(weipingmian()));

    ContrastUpAction = new QAction(QString::fromLocal8Bit("�Աȶ���ǿ"),this);
    connect(ContrastUpAction,SIGNAL(triggered()),openpic,SLOT(ContrastUp()));
    NegativeAction = new QAction(QString::fromLocal8Bit("��Ƭ"),this);
    connect(NegativeAction,SIGNAL(triggered()),openpic,SLOT(Negative()));
    GammaTransformationAction = new QAction(QString::fromLocal8Bit("٤��任(Gamma=5.0)"),this);
    connect(GammaTransformationAction,SIGNAL(triggered()),openpic,SLOT(GammaTransformation()));
    LogarithmAction = new QAction(QString::fromLocal8Bit("�����任(v=200)"),this);
    connect(LogarithmAction,SIGNAL(triggered()),openpic,SLOT(Logarithm()));

    NeighbourhoodH0 = new QAction(QString::fromLocal8Bit("����ƽ����ģ��һ"),this);
    connect(NeighbourhoodH0,SIGNAL(triggered()),openpic,SLOT(NeighborH0()));
    NeighbourhoodH1 = new QAction(QString::fromLocal8Bit("����ƽ����ģ���"),this);
    connect(NeighbourhoodH1,SIGNAL(triggered()),openpic,SLOT(NeighborH1()));
    NeighbourhoodH2 = new QAction(QString::fromLocal8Bit("����ƽ����ģ����"),this);
    connect(NeighbourhoodH2,SIGNAL(triggered()),openpic,SLOT(NeighborH2()));

    RobertsSharpenAction = new QAction(QString::fromLocal8Bit("�޲��Ĳ��(��ɫ)"),this);
    connect(RobertsSharpenAction,SIGNAL(triggered()),openpic,SLOT(RobertsSharpen()));
    LaplaceSharpenAction = new QAction(QString::fromLocal8Bit("������˹����"),this);
    connect(LaplaceSharpenAction,SIGNAL(triggered()),openpic,SLOT(LaplaceSharpen()));
    HighPassSharpenAction = new QAction(QString::fromLocal8Bit("��ͨ�˲�"),this);
    connect(HighPassSharpenAction,SIGNAL(triggered()),openpic,SLOT(HighPassSharpen()));
    ConvolutionAction = new QAction(QString::fromLocal8Bit("����ģ����"),this);
    connect(ConvolutionAction,SIGNAL(triggered()),openpic,SLOT(showconvolution()));

    ShowColorTableAction = new QAction(QString::fromLocal8Bit("��ɫ��"),this);
    connect(ShowColorTableAction,SIGNAL(triggered()),SLOT(ShowColorTable()));

    GrayPalletAction = new QAction(QString::fromLocal8Bit("��ɫ��ͼ��ҶȻ�"),this);
    connect(GrayPalletAction,SIGNAL(triggered()),openpic,SLOT(GrayPallet()));

    TransformAction = new QAction(QString::fromLocal8Bit("���ɫת256ɫ"),this);
    connect(TransformAction,SIGNAL(triggered()),openpic,SLOT(Transform()));

    KirschAction = new QAction(QString::fromLocal8Bit("Kirsch��������"),this);
    connect(KirschAction,SIGNAL(triggered()),openpic,SLOT(Kirsch()));

    GratingTrackAction = new QAction(QString::fromLocal8Bit("��դɨ��"),this);
    connect(GratingTrackAction,SIGNAL(triggered()),openpic,SLOT(GratingTrack()));

    ToThinAction = new QAction(QString::fromLocal8Bit("ϸ��"),this);
    connect(ToThinAction,SIGNAL(triggered()),openpic,SLOT(ToThin()));
    houghTransformAction = new QAction(QString::fromLocal8Bit("����任���ֱ��"),this);
    connect(houghTransformAction,SIGNAL(triggered()),openpic,SLOT(houghTransform()));
    houghTransformCircleAction = new QAction(QString::fromLocal8Bit("����任���Բ"),this);
    connect(houghTransformCircleAction,SIGNAL(triggered()),openpic,SLOT(houghCircleTransform()));

    HuffmanCodingAction = new QAction(QString::fromLocal8Bit("����������"),this);
    connect(HuffmanCodingAction,SIGNAL(triggered()),openpic,SLOT(huffmanCoding()));
    huffmanDecodeAction = new QAction(QString::fromLocal8Bit("����������"),this);
    connect(huffmanDecodeAction,SIGNAL(triggered()),openpic,SLOT(huffmanDecode()));
    fanoCodingAction = new QAction(QString::fromLocal8Bit("fano����"),this);
    connect(fanoCodingAction,SIGNAL(triggered()),openpic,SLOT(fanoCoding()));
    fanoDecodeAction = new QAction(QString::fromLocal8Bit("fano����"),this);
    connect(fanoDecodeAction,SIGNAL(triggered()),openpic,SLOT(fanoDecode()));
    runCodingAction = new QAction(QString::fromLocal8Bit("�γ̱���"),this);
    connect(runCodingAction,SIGNAL(triggered()),openpic,SLOT(runCoding()));
    runDecodeAction = new QAction(QString::fromLocal8Bit("�γ̽���"),this);
    connect(runDecodeAction,SIGNAL(triggered()),openpic,SLOT(runDecode()));
}



void MainWindow::createMenus()
{
    filemenu = menuBar()->addMenu(QString::fromLocal8Bit("�ļ�"));
    filemenu->addAction(openaction);
    filemenu->addAction(saveaction);


    PointOperationsMenu = menuBar()->addMenu(QString::fromLocal8Bit("������"));
    PointOperationsMenu->addAction(tograyaction);
    PointOperationsMenu->addAction(GrayPalletAction);
    PointOperationsMenu->addAction(erzhiaction);
    PointOperationsMenu->addAction(junhenghuaaction);
    PointOperationsMenu->addAction(ContrastUpAction);
    PointOperationsMenu->addAction(NegativeAction);
    PointOperationsMenu->addAction(GammaTransformationAction);
    PointOperationsMenu->addAction(LogarithmAction);



    GeometricOperationMenu = menuBar()->addMenu(QString::fromLocal8Bit("��������"));
    GeometricOperationMenu->addAction(xuanzhuanaction);
    GeometricOperationMenu->addAction(jingxiangaction);
    suofangmenu = GeometricOperationMenu->addMenu(QString::fromLocal8Bit("����"));
    suofangmenu->addAction(suofangzuijinlingaction);
    suofangmenu->addAction(suofangshaungxianxingaction);
    GeometricOperationMenu->addAction(pingyiaction);

    quantizationMenu = menuBar()->addMenu(QString::fromLocal8Bit("����������"));
    quantizationMenu->addAction(caiyangaction);
    quantizationMenu->addAction(lianghuaaction);
    quantizationMenu->addAction(weipingmianaction);

    ImageIntensificationMenu = menuBar()->addMenu(QString::fromLocal8Bit("ͼ����ǿ"));
    SmoothnessMenu = ImageIntensificationMenu->addMenu(QString::fromLocal8Bit("ƽ��"));
    SharpenMenu = ImageIntensificationMenu->addMenu(QString::fromLocal8Bit("��"));
    SmoothnessMenu->addAction(NeighbourhoodH0);
    SmoothnessMenu->addAction(NeighbourhoodH1);
    SmoothnessMenu->addAction(NeighbourhoodH2);
    SharpenMenu->addAction(RobertsSharpenAction);
    SharpenMenu->addAction(LaplaceSharpenAction);
    SharpenMenu->addAction(HighPassSharpenAction);
    ImageIntensificationMenu->addAction(ConvolutionAction);

    EdgeDetectionMenu = menuBar()->addMenu(QString::fromLocal8Bit("��Ե���"));
    EdgeDetectionMenu->addAction(KirschAction);
    EdgeDetectionMenu->addAction(LaplaceSharpenAction);
    EdgeDetectionMenu->addAction(GratingTrackAction);

    MathMorphology = menuBar()->addMenu(QString::fromLocal8Bit("��ѧ��̬ѧ"));
    MathMorphology->addAction(ToThinAction);
    MathMorphology->addAction(houghTransformAction);
    MathMorphology->addAction(houghTransformCircleAction);

    codingMenu = menuBar()->addMenu(QString::fromLocal8Bit("�������"));
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
        QMessageBox::information(this,QString::fromLocal8Bit("���棡"),QString::fromLocal8Bit("���һ��ͼƬ��"));
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
        QMessageBox::information(this,QString::fromLocal8Bit("���棡"),QString::fromLocal8Bit("���һ��ͼƬ��"));
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
        QMessageBox::information(this,QString::fromLocal8Bit("���棡"),QString::fromLocal8Bit("���һ��ͼƬ��"));
        return;
    }

    if(filename[filename.length()-3]!='G'&&filename[filename.length()-3]!='g')
    {
        QMessageBox::information(this,QString::fromLocal8Bit("���棡"),QString::fromLocal8Bit("���ܽ���GIF�ļ���ʽ��"));
        return;
    }

    information * inf = new information();
    inf->setFixedSize(200,300);
    inf->setWindowTitle(QString::fromLocal8Bit("��Ϣ"));
    inf->move(this->x()+100,this->y()+100);
    inf->setWindowModality(Qt::ApplicationModal);
    inf->show();
    return;
}

void MainWindow::ShowColorTable()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("���棡"),QString::fromLocal8Bit("���һ��ͼƬ��"));
        return;
    }
    if((img.colorTable()).isEmpty())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("���棡"),QString::fromLocal8Bit("��ɫ�岻���ڣ�"));
        return;
    }
    showcolortable *showtable = new showcolortable(this);
    showtable->show();
}
