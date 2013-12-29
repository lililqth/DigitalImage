#include<iostream>
#include<cstring>
#include<fstream>
#include<math.h>
#include "image.h"
#include"mainwindow.h"
#include"showorigin.h"
using namespace std;
int nr[256];
char **pbm_o;
QImage img;//保存原图
QImage imgchange;//保存修改以后的图像
QPainter  painter;
QString filename;
bool grayd;//标记是否已经灰度华
bool erzhid;//标记是否已经二值化
openimage::openimage(){
    this->setFixedSize(500,400);
}
openimage::~openimage(){

}

void openimage::paintEvent(QPaintEvent *event)
{
    QImage  imgshow;//真正用来显示的图像
    if(!img.isNull()){
        if(img.width()>500||img.height()>400)
        {
            imgshow = imgchange.scaled(500,400,  Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        else
        {
            imgshow=imgchange;

        }
        this->resize(imgshow.width(),imgshow.height());
        painter.begin(this);
        painter.drawImage(0,0,imgshow,0,0,imgshow.width(),imgshow.height());
        painter.end(); 
    }
}

void openimage::openImage()
{
    grayd=false;
    erzhid=false;
    multiple=1.0;
    filename=QFileDialog::getOpenFileName(this,
                                          QString::fromLocal8Bit("Open Image"),"",
                                          QString::fromLocal8Bit("JPG(*.jpg);;BMP(*.bmp);;ALL files(*.*)"));
    if(img.load(filename,0))
    {
        imgchange=img;
        this->update();
        emit updateoriginshow();
    }
    else
    {
        return;
    }
}


void openimage::graycore(int flag){//只对原图进行修改
    grayd=true;
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    imgchange=img;
    w=img.width();
    h=img.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            QRgb pixel = img.pixel(i,j);
            int gray = qGray(pixel);
            if(flag==1){
                erzhid=true;
                if(gray>75){
                    gray=255;
                }
                else{
                    gray=0;
                }
            }
            QRgb grayPixel = qRgb(gray,gray,gray);
            imgchange.setPixel(i,j,grayPixel);
        }
    }

}

void openimage::erzhi(){
    graycore(1);
    QWidget::update();
}
void openimage::togray(){

    graycore(0);
    QWidget::update();
}

void openimage::saveimg()
{
    if(filename.isEmpty()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    if(!((imgchange.colorTable()).isEmpty()))
    {
        savelocate = QFileDialog::getSaveFileName(this,
                                                  QString::fromLocal8Bit("Save Image"),
                                                  "",
                                                  QString::fromLocal8Bit("*.bmp")); //选择路径
    }
    else
    {
        savelocate = QFileDialog::getSaveFileName(this,
                                                  QString::fromLocal8Bit("Save Image"),
                                                  "",
                                                  QString::fromLocal8Bit("*.jpg;; *.png;; *.bmp;; *.tif;; *.GIF")); //选择路径
    }
    if(savelocate.isEmpty()){
        return;
    }
    if (QFileInfo(savelocate).suffix().isEmpty())  //若后缀为空自动添加jpg后缀
        savelocate.append(".bmp");
    if(imgchange.save(savelocate)){
        QMessageBox::information(this,QString::fromLocal8Bit("success!"),QString::fromLocal8Bit("保存成功！"));
    }
    else{
        QMessageBox::information(this,QString::fromLocal8Bit("failed!"),QString::fromLocal8Bit("图片保存失败"));
    }

}

void openimage::junhenghua(){
    graycore(0);
    //grayd=true;
    int i,j;
    int w=imgchange.width();
    int h=imgchange.height();
    int max=-1,min=999;
    double S[256];
    for(int i=0;i<256;i++){
        S[i]=0.0;
    }
    for(i=0;i<w;i++){
        for(j=0;j<h;j++){
            QRgb pixel = imgchange.pixel(i,j);
            int r=qRed(pixel);
            if(r>max){
                max=r;
            }
            if(r<min){
                min=r;
            }
            S[r]++;
        }
    }
    for(i=0;i<256;i++){
        S[i]/=w*h;
    }
    for(i=255;i>=0;i--){
        for(j=0;j<i;j++){
            S[i]+=S[j];
        }
    }
    for(i=0;i<w;i++){
        for(j=0;j<h;j++){
            int r=qRed(imgchange.pixel(i,j));
            int gray = S[r]*(max-min)+min;
            QRgb grayPixel = qRgb(gray,gray,gray);
            imgchange.setPixel(i,j,grayPixel);
        }
    }
    QWidget::update();
}



void information::paintEvent(QPaintEvent *event)//gif文件信息解析
{
    int i;
    QPainter *painter = new QPainter(this);
    QFile file(filename);
    QDataStream in(&file);
    QTextEdit *view = new QTextEdit(this);
    view->setReadOnly(true);
    if(!file.open(QIODevice::ReadOnly))
    {
        painter->drawText(50,50,100,100,Qt::AlignHCenter,QString::fromLocal8Bit("无法读取文件"));
        return;
    }



    unsigned char a[6];
    QString x;
    for(i=0;i<6;i++)//解析文件头
    {
        in>>a[i];
        x[i]=a[i];
    }
    x+="\n";

    quint8  w,ww;
    for(i=0;i<4;i++)//读取文件的尺寸
    {
        if(i==1||i==3)
        {
            in>>ww;
            continue;
        }

        in>>w;
        x+=QString::number(w,10);
        if(i==0)
        {
            x+="*";
        }
    }
    x+="\n";


    bool flag=false;
    in>>w;
    if(w&0x80>>7){
        x+=QString::fromLocal8Bit("有全局颜色列表\n");
        flag=true;
    }
    x+=QString::fromLocal8Bit("颜色深度为：");//解析颜色深度
    x+=QString::number((w&0x40>>6)*2*2+(w&0x20>>5)*2+(w&0x10>>4)+1,10);
    x+="\n";
    if(w&0x8>>3==true&&flag==true){
        x+=QString::fromLocal8Bit("全局颜色列表分类排列\n");//全局颜色列表分类排列
    }
    if(w&0x8>>3==false&&flag==true)
    {
        x+=QString::fromLocal8Bit("全局颜色列表非分类排列\n");//全局颜色列表非分类排列
    }


    if(flag==true){
        x+=QString::fromLocal8Bit("列表索引数：2^");
        x+=QString::number((w&0x4>>2)*2*2+(w&0x2>>1)*2+(w&0x1)+1,10);
        x+="\n";
    }
    in>>w;
    in>>w;
    x+=QString::fromLocal8Bit("像素宽高比为");
    x+=QString::number(w,10);
    view->setText(x);
    view->show();
}



void information::closeEvent(QPaintEvent *event)
{
    //this->setDisabled(false);
}
void openimage::getcaiyang()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    slider *getvalue = new slider(this,1,16,8,QString::fromLocal8Bit("采样间隔"),2);
    getvalue->show();
}

void openimage::caiyang(int jiange)
{

    //bool ok=false;
    //int jiange=QInputDialog::getInt(this,QString::fromLocal8Bit(""),QString::fromLocal8Bit("请输入采样间隔"),8,1,16,0,&ok,0);
    //if(ok==false)
    //{
    //  return;
    //}
    int i,j,k,l,w,h;
    graycore(0);//首先执行灰度化
    // grayd=true;
    w=img.width();
    h=img.height();
    for(i=0;i<w;i+=jiange)
    {
        for(j=0;j<h;j+=jiange)
        {
            QRgb pixel = imgchange.pixel(i,j);
            for(k=i;k<i+jiange;k++)
            {
                for(l=j;l<j+jiange;l++)
                {
                    if(k<w&&l<h)
                    {
                        imgchange.setPixel(k,l,pixel);
                    }
                }
            }
        }
    }
    QWidget::update();
}

void openimage::lianghua()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }

    bool ok=false;
    int  dengji=QInputDialog::getInt(this,QString::fromLocal8Bit(""),QString::fromLocal8Bit("请输入量化等级"),16,2,256,0,&ok,0);
    if(ok==false)
    {
        return;
    }

    graycore(0);

    int w=img.width();
    int h=img.height();
    int step=256/(dengji);
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            QRgb pixel = img.pixel(i,j);
            int r=qRed(pixel);//获取灰度值
            for(int k=0;k<dengji-1;k++){
                if(r>step*k&&r<=step*(k+1))
                {
                    QRgb grayPixel = qRgb(step*k,step*k,step*k);
                    /*if(qRed(grayPixel)!=0&&qRed(grayPixel)!=128)
                    {
                        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("出错"));
                        printf("%d\n",qRed(grayPixel));
                    }*/
                    imgchange.setPixel(i,j,grayPixel);
                    break;
                }
            }
        }
    }
    QWidget::update();
}

void openimage::weipingmian()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    int w=img.width();
    int h=img.height();
    imgchange=img;
    imgchange.fill(0xFFFFFF);
    for(int k=0;k<8;k++)
    {
        for(int i=0; i<w; i++){
            for(int j=0;j<h; j++){
                QRgb pixel = img.pixel(i,j);
                QRgb grayPixel;
                int gray = qGray(pixel);
                if(gray>>k&1)
                {
                    grayPixel = qRgb(255,255,255);

                }
                else
                {
                    grayPixel = qRgb(0,0,0);
                }
                switch(k)
                {
                case 0:
                    imgchange.setPixel(i/4.1,j/2.1,grayPixel);
                case 1:
                    imgchange.setPixel(i/4.1+w/4,j/2.1,grayPixel);
                case 2:
                    imgchange.setPixel(i/4.1+w/4*2,j/2.1,grayPixel);
                case 3:
                    imgchange.setPixel(i/4.1+w/4*3,j/2.1,grayPixel);
                case 4:
                    imgchange.setPixel(i/4.1,j/2.1+h/2,grayPixel);
                case 5:
                    imgchange.setPixel(i/4.1+w/4,j/2.1+h/2,grayPixel);
                case 6:
                    imgchange.setPixel(i/4.1+w/4*2,j/2.1+h/2,grayPixel);
                case 7:
                    imgchange.setPixel(i/4.1+w/4*3,j/2.1+h/2,grayPixel);
                }
            }
        }
    }
    QWidget::update();
}


void openimage::ContrastUp()
{
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }

    graycore(0);

    w=imgchange.width();
    h=imgchange.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            QRgb pixel = imgchange.pixel(i,j);
            int gray = qGray(pixel);
            gray=2*gray;
            QRgb grayPixel = qRgb(gray,gray,gray);
            imgchange.setPixel(i,j,grayPixel);
        }
    }
    QWidget::update();
}

void openimage::Negative()
{
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }

    graycore(0);

    w=imgchange.width();
    h=imgchange.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            QRgb pixel = imgchange.pixel(i,j);
            int gray = qGray(pixel);
            gray=255-gray;
            QRgb grayPixel = qRgb(gray,gray,gray);
            imgchange.setPixel(i,j,grayPixel);
        }
    }
    QWidget::update();
}

void openimage::GammaTransformation()
{
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    graycore(0);
    w=imgchange.width();
    h=imgchange.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            QRgb pixel = imgchange.pixel(i,j);
            double gray = (double)qGray(pixel)/255.0;
            gray=pow(gray,5)*255;
            QRgb grayPixel = qRgb(gray,gray,gray);
            imgchange.setPixel(i,j,grayPixel);
        }
    }
    QWidget::update();
}

void openimage::Logarithm()
{
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    graycore(0);
    w=imgchange.width();
    h=imgchange.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            QRgb pixel = imgchange.pixel(i,j);
            double gray = (double)qGray(pixel)/255.0;
            gray=log(1+gray*200)/log(201)*255;
            QRgb grayPixel = qRgb(gray,gray,gray);
            imgchange.setPixel(i,j,grayPixel);
        }
    }
    QWidget::update();
}

void openimage::Neighborhood(int n)//邻域平均法
{
    int H[3][10]={{1,1,1,1,0,1,1,1,1,8},{1,2,1,2,4,2,1,2,1,16},{0,1,0,1,4,1,0,1,0,8}};
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    imgchange=img;
    w=imgchange.width();
    h=imgchange.height();
    double gray=0.0;
    for(int i=0; i<w; i++)
    {//遍历图像
        for(int j=0;j<h; j++)
        {
            gray=0;
            if(i-1>=0&&i+1<w&&j-1>=0&&j+1<h)
            {
                /*for(int k=-1;k<=1;k++)
                {//遍历9个像素
                    for(int l=-1;l<=1;l++)
                    {
                        if(k!=0||l!=0)
                        {
                            gray+= (double)qGray(imgchange.pixel(i+k,j+l));
                        }
                    }
                }*/
                gray=(double)qGray(imgchange.pixel(i-1,j-1))*H[n][0]+(double)qGray(imgchange.pixel(i-1,j))*H[n][1]
                        +(double)qGray(imgchange.pixel(i-1,j+1))*H[n][2]+(double)qGray(imgchange.pixel(i,j-1))*H[n][3]
                        +(double)qGray(imgchange.pixel(i,j))*H[n][4]+(double)qGray(imgchange.pixel(i,j+1))*H[n][5]
                        +(double)qGray(imgchange.pixel(i+1,j-1))*H[n][6]+(double)qGray(imgchange.pixel(i+1,j))*H[n][7]
                        +(double)qGray(imgchange.pixel(i+1,j+1))*H[n][8];
                gray/=H[n][9];
                if(abs(gray-qGray(imgchange.pixel(i,j)))>0)
                {
                    QRgb grayPixel = qRgb(gray,gray,gray);
                    imgchange.setPixel(i,j,grayPixel);
                }
            }

        }
    }
    QWidget::update();
}

void openimage::NeighborH0()//模板一
{
    Neighborhood(0);
}

void openimage::NeighborH1()//模板二
{
    Neighborhood(1);
}

void openimage::NeighborH2()//模板三
{
    Neighborhood(2);
}

void openimage::RobertsSharpen()//罗伯兹锐化
{
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    imgchange=img;
    w=imgchange.width();
    h=imgchange.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            if(i+1<w&&j+1<h)
            {
                double red = abs(qRed(imgchange.pixel(i,j))-qRed(imgchange.pixel(i+1,j+1)))
                        +abs(qRed(imgchange.pixel(i+1,j))-qRed(imgchange.pixel(i,j+1)));
                double green = abs(qGreen(imgchange.pixel(i,j))-qGreen(imgchange.pixel(i+1,j+1)))
                        +abs(qGreen(imgchange.pixel(i+1,j))-qGreen(imgchange.pixel(i,j+1)));
                double blue = abs(qBlue(imgchange.pixel(i,j))-qBlue(imgchange.pixel(i+1,j+1)))
                        +abs(qBlue(imgchange.pixel(i+1,j))-qBlue(imgchange.pixel(i,j+1)));

                QRgb grayPixel = qRgb(red,green,blue);
                imgchange.setPixel(i,j,grayPixel);
            }
        }
    }
    QWidget::update();

}

void openimage::LaplaceSharpen()//拉普拉斯算子
{
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    imgchange=img;
    w=imgchange.width();
    h=imgchange.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            if(i+1<w&&j+1<h&&i-1>=0&&j-1>=0)
            {
                double gray = 4*qGray(imgchange.pixel(i,j))-qGray(imgchange.pixel(i+1,j))
                        -qGray(imgchange.pixel(i-1,j))-qGray(imgchange.pixel(i,j+1))-qGray(imgchange.pixel(i,j-1));
                if(gray<0)
                {
                    gray=0;
                }
                if(gray>255)
                {
                    gray=255;
                }
                QRgb grayPixel = qRgb(gray,gray,gray);
                imgchange.setPixel(i,j,grayPixel);
            }
        }
    }
    QWidget::update();

}

void openimage::HighPassSharpen()//高通滤波
{
    int w,h;
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    imgchange=img;
    w=imgchange.width();
    h=imgchange.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            if(i+1<w&&j+1<h&&i-1>=0&&j-1>=0)
            {
                double gray = 5*qGray(imgchange.pixel(i,j))-qGray(imgchange.pixel(i+1,j))
                        -qGray(imgchange.pixel(i-1,j))-qGray(imgchange.pixel(i,j+1))-qGray(imgchange.pixel(i,j-1));
                if(gray<0)
                {
                    gray=0;
                }
                if(gray>255)
                {
                    gray=255;
                }
                QRgb grayPixel = qRgb(gray,gray,gray);
                imgchange.setPixel(i,j,grayPixel);
            }
        }
    }
    QWidget::update();
}


void openimage::showconvolution(){
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    martrix = new getmatrix(this);
    martrix->setWindowModality(Qt::ApplicationModal);
    martrix->show();
}

void openimage::convolution()
{
    int w,h;
    graycore(0);
    w=imgchange.width();
    h=imgchange.height();
    for(int i=0; i<w; i++){
        for(int j=0;j<h; j++){
            if(i+1<w&&j+1<h&&i-1>=0&&j-1>=0)
            {
                double gray =
                        martrix->m00*qGray(imgchange.pixel(i-1,j-1))+martrix->m01*qGray(imgchange.pixel(i-1,j))+martrix->m02*qGray(imgchange.pixel(i-1,j+1))
                        +martrix->m10*qGray(imgchange.pixel(i,j-1))+martrix->m11*qGray(imgchange.pixel(i,j))+martrix->m12*qGray(imgchange.pixel(i,j+1))
                        +martrix->m20*qGray(imgchange.pixel(i+1,j-1))+martrix->m21*qGray(imgchange.pixel(i+1,j))+martrix->m22*qGray(imgchange.pixel(i+1,j+1));
                if(gray<0)
                {
                    gray=0;
                }
                if(gray>255)
                {
                    gray=255;
                }
                QRgb grayPixel = qRgb(gray,gray,gray);
                imgchange.setPixel(i,j,grayPixel);
            }
        }
    }
    QWidget::update();

}

void openimage::GrayPallet()//针对有调色板的灰度图像
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
    imgchange=img;
    QVector<QRgb> grayColorTable;
    uint rgb=0;
    for(int i=0;i<256;i++){
        grayColorTable.append(rgb);
        rgb+=0x00010101;//r,g,b值分别加1，a值不变,见QRgb说明
    }
    imgchange.setColorTable(grayColorTable);
    imgchange.save("graypallte.jpg");
    imgchange.load("graypallte.jpg");
    QWidget::update();
}

void openimage::Transform()//真彩图像转256色
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    if(!((img.colorTable()).isEmpty()))
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("只能转换真彩色图像！"));
        return;
    }
    int colorstatistic[4096];//原始数据
    int colorindex[4096];//存放颜色索引
    memset(colorstatistic,0,sizeof(colorstatistic));
    memset(colorindex,0,sizeof(colorindex));
    int w=img.width();
    int h=img.height();
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            int r=(qRed(img.pixel(i,j)))&0xf0;
            int g=(qGreen(img.pixel(i,j)))&0xf0;
            int b=(qBlue(img.pixel(i,j)))&0xf0;
            int index = (r<<4)+g+(b>>4);
            colorstatistic[index]++;
        }
    }
    int palCounts=0;
    for(int i=0;i<4096;i++)//i代表颜色索引
    {
        if(colorstatistic[i]!=0)
        {
            colorstatistic[palCounts]=colorstatistic[i];//保存各种颜色索引出现的次数
            colorindex[palCounts]=i;//保存各种颜色的索引，与colorstatistic中的颜色出现的次数一一对应
            palCounts++;
        }
    }

    for(int i=0;i<palCounts-1;i++)
    {
        for(int j=i+1;j<palCounts;j++)
        {
            if(colorstatistic[j]>colorstatistic[i])
            {
                int temp=colorstatistic[i];
                colorstatistic[i]=colorstatistic[j];//根据出现的次数
                colorstatistic[j]=temp;

                temp=colorindex[i];
                colorindex[i]=colorindex[j];//对颜色索引排序
                colorindex[j]=temp;
            }
        }
    }

    QImage imgindex8;
    imgindex8=img.convertToFormat(QImage::Format_Indexed8);
    memset(colorstatistic,0,sizeof(colorstatistic));
    for(int i=0;i<256;i++){//获取调色板
        int r=(colorindex[i]&0xf00)>>4;
        int g=colorindex[i]&0x0f0;
        int b=(colorindex[i]&0x00f)<<4;
        imgindex8.setColor(i,qRgb(r,g,b));
        colorstatistic[i]=i;  //此时已经不需要颜色出现的次数,出现最多的256种颜色对应调色板中的256种颜色
    }
    //===============================测试colortable=========================================================/
    //imgchange=imgindex8;
    //showcolortable *showtable = new showcolortable(this);
    //showtable->show();

    //=======================================================================================================/
    if(palCounts>256)
    {
        for(int i=256;i<palCounts;i++)
        {
            long error=999999999999;
            int red=(colorindex[i]&0xf00)>>4;//colorindex中存放的是colorstatistic的颜色索引
            int green=(colorindex[i]&0x0f0);
            int blue=(colorindex[i]&0x00f)<<4;

            int clrIndex=0;

            for(int j=0;j<256;j++)
            {
                long error2=(long)((qBlue(imgindex8.color(j))-blue)*(qBlue(imgindex8.color(j))-blue)+
                                   (qGreen(imgindex8.color(j))-green)*(qGreen(imgindex8.color(j))-green)+
                                   (qRed(imgindex8.color(j))-red)*(qRed(imgindex8.color(j))-red));
                if(error2<error)
                {
                    error=error2;
                    clrIndex=j;
                }
            }
            colorstatistic[i]=clrIndex;//保存所有颜色在调色板中的对应颜色
        }
    }


    int MapTable[4096];
    memset(MapTable,0,sizeof(MapTable));
    for(int i=0;i<4096;i++)
    {
        int index=colorindex[i];//获取原图中的颜色
        MapTable[index]=colorstatistic[i];//获取在颜色表中的映射
    }


    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            int r=(qRed(img.pixel(i,j)))&0xf0;
            int g=(qGreen(img.pixel(i,j)))&0xf0;
            int b=(qBlue(img.pixel(i,j)))&0xf0;
            int index = (r<<4)+g+(b>>4);
            imgindex8.setPixel(i,j,MapTable[index]);
        }
    }
    imgindex8.save("index8.bmp");
    //imgindex8.save("index8.jpg",QImage::Format_Indexed8,-1);
    imgindex8.load("index8.bmp");
    imgchange=imgindex8;
    QWidget::update();

}

void openimage::Kirsch()
{
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    imgchange=img;
    int H[8][9]={{-5,3,3,-5,0,3,-5,3,3},{3,3,3,-5,0,3,-5,-5,3},{3,3,3,3,0,3,-5,-5,-5},
                 {3,3,3,3,0,-5,3,-5,-5},{3,3,-5,3,0,-5,3,3,-5},{3,-5,-5,3,0,-5,3,3,3},
                 {-5,-5,-5,3,0,3,3,3,3},{-5,-5,3,-5,0,3,3,3,3}};
    int w,h;
    w=imgchange.width();
    h=imgchange.height();
    double gray=0.0;
    for(int i=0; i<w; i++)
    {//遍历图像
        for(int j=0;j<h; j++)
        {
            gray=0;
            if(i-1>=0&&i+1<w&&j-1>=0&&j+1<h)
            {
                double max=-999;
                for(int n=0;n<8;n++)
                {
                    gray=(double)qGray(imgchange.pixel(i-1,j-1))*H[n][0]+(double)qGray(imgchange.pixel(i-1,j))*H[n][1]
                            +(double)qGray(imgchange.pixel(i-1,j+1))*H[n][2]+(double)qGray(imgchange.pixel(i,j-1))*H[n][3]
                            +(double)qGray(imgchange.pixel(i,j))*H[n][4]+(double)qGray(imgchange.pixel(i,j+1))*H[n][5]
                            +(double)qGray(imgchange.pixel(i+1,j-1))*H[n][6]+(double)qGray(imgchange.pixel(i+1,j))*H[n][7]
                            +(double)qGray(imgchange.pixel(i+1,j+1))*H[n][8];
                    gray=abs(gray);
                    if(gray>max)
                    {
                        max=gray;
                    }
                }
                if(max<0)
                {
                    max=0;
                }
                if(max>255)
                {
                    max=255;
                }

                QRgb grayPixel = qRgb(max,max,max);
                imgchange.setPixel(i,j,grayPixel);
            }
        }
    }

    QWidget::update();
}

void openimage::GratingTrack()
{
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    imgchange=img;
    int w = imgchange.width();
    int h = imgchange.height();
    QImage imgGrat;
    imgGrat=imgchange;
    imgGrat.fill(0x000000);
    bool ok=false;
    QString string=QInputDialog::getText(this,QString::fromLocal8Bit(""),QString::fromLocal8Bit("请输入检测门限和跟踪门限并用空格隔开"),QLineEdit::Normal,"250 50",&ok,0);
    if(true==ok)
    {
        int b = (string.section(' ',0,0)).toInt(0,10);
        int t = (string.section(' ',1,1)).toInt(0,10);
        QRgb rgb = qRgb(255,255,255);

        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                if(qGray(imgchange.pixel(j,i))>b)
                {
                    imgGrat.setPixel(j,i,rgb);
                }
            }

            qDebug("开始跟踪 %d",i);
            for(int k=i;k<h-1;k++)
            {
                for(int j=0;j<w;j++)
                {
                    int flag=0;
                    if(255==qGray(imgGrat.pixel(j,k)))
                    {
                        if(j-1>=0&&abs(qGray(imgchange.pixel(j-1,k))-255)<t)//标记左下方
                        {

                            flag=1;
                            imgGrat.setPixel(j-1,k+1,rgb);
                        }
                        else if(abs(qGray(imgchange.pixel(j,k))-255)<t)
                        {
                            flag=1;
                            imgGrat.setPixel(j,k+1,rgb);
                        }
                        else if(j+1<w&&abs(qGray(imgchange.pixel(j+1,k))-255)<t)
                        {
                            flag=1;
                            imgGrat.setPixel(j+1,k+1,rgb);
                        }
                    }
                }
            }
        }
        imgchange=imgGrat;
        QWidget::update();
    }
}

void openimage::ToThin()
{
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    graycore(1);
    int w = imgchange.width();
    int h = imgchange.height();
    int flag=0;
    QRgb rgb = qRgb(255,255,255);
    int cishu=1;
    while(cishu--)
    {
        for(int i=0;i<w;i++)
        {
            for(int j=0;j<h;j++)
            {
                flag=0;
                if(i-1>=0&&i+1<w&&j-1>=0&&j+1<h)
                {

                    if(0!=qRed(imgchange.pixel(i,j)))
                    {
                        continue;
                    }
                    if(0==qRed(imgchange.pixel(i,j-1))*qRed(imgchange.pixel(i-1,j))*qRed(imgchange.pixel(i+1,j)))
                    {
                        flag++;
                    }
                    if(0==qRed(imgchange.pixel(i,j-1))*qRed(imgchange.pixel(i-1,j))*qRed(imgchange.pixel(i,j+1)))
                    {
                        flag++;
                    }
                    int shuzu[7]={qRed(imgchange.pixel(i,j-1))/*2*/,qRed(imgchange.pixel(i+1,j-1))/*3*/,qRed(imgchange.pixel(i+1,j))/*4*/,qRed(imgchange.pixel(i+1,j+1))/*5*/
                                  ,qRed(imgchange.pixel(i+1,j))/*6*/,qRed(imgchange.pixel(i-1,j+1))/*7*/,qRed(imgchange.pixel(i-1,j))/*8*/};
                    int num0=0;
                    for(int k=0;k<7;k++)
                    {
                        if(0==shuzu[k])
                        {
                            num0++;
                        }
                    }
                    if(num0>2&&num0<=6)
                    {
                        flag++;
                    }
                    if(3==flag)
                    {
                        imgchange.setPixel(i,j,rgb);
                    }
                }
            }
        }
    }
    QWidget::update();
}

int originalRecord[50000][180];//0，到180度每1度取一个离散值共180个值
void openimage::houghTransform()
{
    if(img.isNull()){
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片"));
        return ;
    }
    int w,h;
    w=imgchange.width();
    h=imgchange.height();
    int statisticRecord[180][600];//统计每一对（ R，theta ）的出现次数
    memset(originalRecord,0,sizeof(originalRecord));
    memset(statisticRecord,0,sizeof(statisticRecord));
    int dotNum=0;
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            int gray = qRed(imgchange.pixel(i,j));
            if(gray>=100)
                continue;
            for(int k=0;k<180;k++){
                double theta = (double)((double)k/180.0)*3.1415926;
                if(dotNum>=50000){
                    qDebug("out of range");
                    goto out;
                }
                double costheta = cos(theta);
                double sintheta = sin(theta);
                originalRecord[dotNum][k] = (int)((double)i*costheta+(double)j*sintheta);
            }
            dotNum++;
        }
    }
out:
    for(int i=0;i<dotNum;i++){
        for(int j=0;j<180;j++){
            statisticRecord[j][originalRecord[i][j]+260]++;
        }
    }
    int threshold = 50;
    for(int i=0;i<180;i++){
        double theta1 = (double)i/180.0*3.1415926;
        double costheta1 = cos(theta1);
        double sintheta1 = sin(theta1);
        for(int j=0;j<600;j++){
            if(statisticRecord[i][j]>threshold){
                for(int k=0;k<w;k++){
                    for(int l=0;l<h;l++){
                        double x = k*costheta1;
                        double y = l*sintheta1;
                        double ans = x+y;
                        double absAns = ans-j+260;
                        if(absAns<0){
                            absAns=-absAns;
                        }
                        if(absAns<0.08)
                        {
                            imgchange.setPixel(k,l,qRgb(255,0,0));
                        }
                    }
                }
            }
        }
    }
    QWidget::update();
}

void openimage::houghCircleTransform()//霍夫变换检测圆
{
    int nWidth =imgchange.width();
    int nHeight =imgchange.height();
    int min;
    if(nWidth<nHeight)
        min=nWidth;
    else
        min=nHeight;
    min=min/2;
    if(min>100)
        min=100;
    int *** param;
    param=(int ***)malloc(sizeof(int **)*min);
    for(int j=0;j<min;j++){
        param[j]=(int **)malloc(sizeof(int *)*(nHeight));
        for(int i=0;i<nHeight;i++)
            param[j][i]=(int *)malloc(sizeof(int)*nWidth);
    }

    for(int i=0;i<min;i++)
        for(int j=0;j<nHeight;j++)
            for(int k=0;k<nWidth;k++)
                param[i][j][k]=0;


    int row,col,rr,gg,bb,r,g,b,counter,q;
    int k,count,max=0,max1=0,maxpx,maxpy,avg,sum,kmax=0,kx,ky,kr;

    for(k=1;k<min;k++)
    {
        for (int i = 0; i <=nHeight-1; i++)
        {
            for (int j = 0; j <=nWidth-1; j++)
            {
                if(qRed(imgchange.pixel(j,i))!=0)
                    continue;
                for(int y=i-k;y<i+k;y++)
                    for(int x=j-k;x<j+k;x++)
                    {
                        if(y<0||y>=nHeight||x<0||x>=nWidth)
                            continue;
                        if((x-j)*(x-j)+(y-i)*(y-i)<(k*k+30)&&(x-j)*(x-j)+(y-i)*(y-i)>(k*k-30))
                            param[k][y][x]+=1;
                    }
            }
        }
        max=50;
        for(int k=0;k<min;k++)
        {
            for(int i=0;i<nHeight;i++)
            {
                for(int j=0;j<nWidth;j++)
                {
                    if(param[k][i][j]>max)
                    {
                        for(int y=0;y<nHeight;y++)
                        {
                            for(int x=0;x<nWidth;x++)
                            {
                                if((y-i)*(y-i)+(x-j)*(x-j)==k*k/*+1)&&((y-i)*(y-i)+(x-j)*(x-j)>k*k-1)*/)
                                {
                                    imgchange.setPixel(j,i,qRgb(255,0,0));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    QWidget::update();
}

void openimage::huffmanCoding()
{
    getRgb_num();
    Huff *huf  = new Huff(256,nr);
    char **pbm;
    pbm=huf->pbm;
    pbm_o=huf->pbm;
    QString suffix=tr("所有文件 (*.*)");

    QString fileName=QFileDialog::getOpenFileName(this,
                                                  QString(tr("打开(Open)")),
                                                  QDir::currentPath(),
                                                  suffix);
    QFile file(fileName);
    if(fileName.isNull()||fileName.isEmpty())
        return ;
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Can't open the file!");
    }
    QTextStream stream(&file);
    int geshiint,wint,hint;
    geshiint=imgchange.format();
    stream << geshiint <<endl;
    wint = imgchange.width();
    stream << wint <<endl;
    hint = imgchange.height();
    stream << hint <<endl;
    int r,g,b;
    QColor rgb;
    for(int i=0;i<256;i++)
    {
        stream<<*pbm<<endl;
        pbm++;
    }
    pbm=huf->pbm;
    for(int i=0;i<imgchange.width();i++)
        for(int ii=0;ii<imgchange.height();ii++)
        {
            rgb.setRgb((imgchange.pixel(i,ii)));
            rgb.getRgb(&r,&g,&b);
            QString str(pbm[r]);
            stream<< str << endl;
        }
    file.close();
}
void openimage::getRgb_num()
{
    int r,g,b;
    QColor rgb;
    for(int i=0;i<256;i++)
        nr[i]=0;
    for(int i=0;i<imgchange.width();i++)
        for(int ii=0;ii<imgchange.height();ii++)
        {
            rgb.setRgb((imgchange.pixel(i,ii)));
            rgb.getRgb(&r,&g,&b);
            nr[r]++;
        }

}

void openimage::huffmanDecode()
{
    QString suffix=tr("所有文件 (*.*)");
    QString fileName=QFileDialog::getOpenFileName(this,
                                                  QString(tr("打开(Open)")),
                                                  QDir::currentPath(),
                                                  suffix);
    QFile file(fileName);
    if(fileName.isNull()||fileName.isEmpty())
        return ;
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Can't open file");
    }

    QTextStream stream(&file);
    int geshiint,wint,hint;
    stream>>geshiint>>wint>>hint;
    QImage * Img = new QImage(wint,hint,(QImage::Format)geshiint);
    int r,g,b;
    QString strl[257];
    for(int i=0;i<256;i++)
    {
        stream>> strl[i];
    }
    QColor rgb;
    for(int i=0;i<Img->width();i++)
        for(int ii=0;ii<Img->height();ii++)
        {
            QString str;
            stream>> str ;
            int B=1;
            int num=0;
            for(;num<256;num++)
            {
                if(str==strl[num])
                {
                    B=0;
                    break;
                }
            }
            if(B) qDebug("Error");
            rgb.setRgb(num,num,num);
            Img->setPixel(i,ii,rgb.rgb());
        }
    file.close();  
    imgchange = *Img;
    img = *Img;

    QWidget::update();
}
void openimage::fanoCoding()
{
    getRgb_num();
    QString suffix=tr("所有文件 (*.*)");
    QString fileName=QFileDialog::getOpenFileName(this,
                                                  QString(tr("打开(Open)")),
                                                  QDir::currentPath(),
                                                  suffix);
    QFile file(fileName);
    if(fileName.isNull()||fileName.isEmpty())
        return ;
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Can't open the file!");
    }
    QTextStream stream(&file);
    double* hist = new double[256];
    double* feq = new double[256];
    int* hMap = new int[256];
    QString strCode[256];

    bool* bFlag = new bool[256];
    double feqSum = 0.0;
    double feqTotal = 0.0;

    for (int i = 0; i < 256; i++)
    {
        hist[i] = 0.0;//灰度值的个数
        hMap[i] = i;
        bFlag[i] = false;
    }
    for (int i = 0; i < 256; i++)
    {
        hist[i] = nr[i];//灰度值的个数

    }

    for (int i = 0; i < 256; i++)
    {
        hist[i] /= (double)(imgchange.width()*imgchange.height());
        feq[i] = hist[i];//灰度值的频率
        feqTotal += feq[i];//总频率
    }

    double fTemp = 0;
    int iTemp = 0;//从小的大排序
    for (int i = 0; i < 255; i++)
    {
        for (int j = 0; j < 255 - i; j++)
        {
            if (hist[j] > hist[j + 1])
            {
                fTemp = hist[j];//频率
                hist[j] = hist[j + 1];
                hist[j + 1] = fTemp;

                iTemp = hMap[j];//对应map
                hMap[j] = hMap[j + 1];
                hMap[j + 1] = iTemp;
            }
        }
    }

    for (int i = 0; i < 255; i++)
    {
        if (hist[i] == 0.0)
            continue;

        int gCount = 0;

        while (gCount < 256)
        {
            gCount = i;

            for (int j = i; j < 256; j++)
            {
                if (bFlag[j] == false)
                {

                    feqSum += hist[j];
                    if (feqSum > feqTotal / 2)
                        strCode[hMap[j]] = strCode[hMap[j]].append(QString("0"));
                    else
                        strCode[hMap[j]] = strCode[hMap[j]].append(QString("1"));

                    if (feqTotal == feqSum)
                    {
                        feqSum = 0.0;
                        feqTotal = 0.0;
                        int k;
                        if (j == 255)
                            k = i;
                        else
                            k = j + 1;
                        int m;
                        for (m = k; m < 256; m++)
                        {
                            if(strCode[hMap[m]].length()<=0 || strCode[hMap[k]].length()<=0) continue;
                            if ((strCode[hMap[m]].mid(strCode[hMap[m]].length()-1) != (strCode[hMap[k]].mid((strCode[hMap[k]].length()) - 1))
                                 || (strCode[hMap[m]].length()) != (strCode[hMap[k]].length())))
                                break;
                            feqTotal += hist[m];
                        }
                        if (k + 1 == m)
                            bFlag[k] = true;
                    }
                }
                else
                {
                    gCount++;

                    feqSum = 0.0;
                    feqTotal = 0.0;
                    int k;
                    if (j == 255)
                        k = i;
                    else
                        k = j + 1;
                    int m;
                    for (m = k; m < 256; m++)
                    {
                        if(strCode[hMap[m]].length()<=0 || strCode[hMap[k]].length()<=0) continue;
                        if ((strCode[hMap[m]].mid((strCode[hMap[m]].length()) - 1) != (strCode[hMap[k]].mid((strCode[hMap[k]].length()) - 1))
                             || (strCode[hMap[m]].length()) != (strCode[hMap[k]].length())))
                            break;
                        feqTotal += hist[m];
                    }
                    if (k + 1 == m)
                        bFlag[k] = true;
                }
            }
        }
        break;
    }
    int geshiint,wint,hint;
    geshiint=imgchange.format();
    stream << geshiint <<endl;
    wint = imgchange.width();
    stream << wint <<endl;
    hint = imgchange.height();
    stream << hint <<endl;
    int r,g,b;
    QColor rgb;
    for(int i=0;i<256;i++)
    {
        stream<<strCode[hMap[i]]<<endl;
    }
    // pbm=huf->pbm;
    for(int i=0;i<imgchange.width();i++)
        for(int ii=0;ii<imgchange.height();ii++)
        {
            rgb.setRgb((imgchange.pixel(i,ii)));
            rgb.getRgb(&r,&g,&b);
            stream<< strCode[hMap[r]] << endl;
        }
    file.close();
}
void openimage::fanoDecode()
{
    QString suffix=tr("所有文件 (*.*)");
    QString fileName=QFileDialog::getOpenFileName(this,
                                                  QString(tr("打开(Open)")),
                                                  QDir::currentPath(),
                                                  suffix);
    QFile file(fileName);
    if(fileName.isNull()||fileName.isEmpty())
        return ;
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Can't open the file!");
    }
    QTextStream stream(&file);
    int geshiint,wint,hint;
    stream>>geshiint>>wint>>hint;
    QImage *Img = new QImage(wint,hint,(QImage::Format)geshiint);
    QString strl[257];
    for(int i=0;i<256;i++)
    {
        stream>> strl[i];
    }
    QColor rgb;
    for(int i=0;i<Img->width();i++)
        for(int ii=0;ii<Img->height();ii++)
        {
            QString str;
            stream>> str ;
            int B=1;
            int num=0;
            for(;num<256;num++)
            {
                if(str==strl[num])
                {
                    B=0;
                    break;
                }
            }
            if(B) qDebug("Error");
            rgb.setRgb(num,num,num);
            Img->setPixel(i,ii,rgb.rgb());
        }
    file.close();
    imgchange = *Img;
    img = *Img;
    QWidget::update();
}

void openimage::runCoding()
{
    int r,g,b;
    QColor col;
    QRgb val;
    for(int h=0;h<imgchange.height();h++)///灰度
        for(int w=0;w<imgchange.height();w++)
        {
            val = imgchange.pixel(w,h);
            col.setRgb(val);
            col.getRgb(&r,&g,&b);
            int t=r>128?255:0;
            val = qRgb(t,t,t);
            imgchange.setPixel(w,h,val);
        }
    getRgb_num();

    QString suffix=tr("所有文件 (*.*)");

    QString fileName=QFileDialog::getOpenFileName(this,
                                                  QString(tr("打开(Open)")),
                                                  QDir::currentPath(),
                                                  suffix);
    QFile file(fileName);
    if(fileName.isNull()||fileName.isEmpty())
        return ;
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Can't open the file!");
    }
    QTextStream stream(&file);
    int geshiint,wint,hint;
    geshiint=imgchange.format();
    stream << geshiint <<endl;
    wint = imgchange.width();
    stream << wint <<endl;
    hint = imgchange.height();
    stream << hint <<endl;
    QString y("1"),l("0"),v,t;
    int count=0;
    for(int i=0;i<imgchange.width();i++)
        for(int ii=0;ii<imgchange.height();ii++)
        {
            val = imgchange.pixel(i,ii);
            col.setRgb(val);
            col.getRgb(&r,&g,&b);
            t = r>128?y:l;
            if(i==0 && ii==0) v=t;
            if(t==v)
            {
                count++;
            }
            else
            {
                stream<<v<<endl<<count<<endl;
                count=1;
                v=t;
            }
            if(i==(imgchange.width()-1) && ii==(imgchange.height()-1))
            {
                stream<<v<<endl<<count<<endl;
            }

        }

    file.close();
}
void openimage::runDecode()
{
    QString suffix=tr("所有文件 (*.*)");

    QString fileName=QFileDialog::getOpenFileName(this,
                                                  QString(tr("打开(Open)")),
                                                  QDir::currentPath(),
                                                  suffix);
    QFile file(fileName);
    if(fileName.isNull()||fileName.isEmpty())
        return ;
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Can't open the file!");
    }
    QTextStream stream(&file);
    int geshiint,wint,hint;
    stream>>geshiint>>wint>>hint;
    QImage *Img = new QImage(wint,hint,(QImage::Format)geshiint);
    int r,g;
    QColor rgb;
    QString v;
    int count=0;
    int i=0;
    int ii=0;
    while(1) {
        stream>>v;
        stream>>count;
        while(count--)
        {
            r=(v==QString("1"))?255:0;
            rgb.setRgb(r,r,r);
            Img->setPixel(i,ii,rgb.rgb());
            ii++;
            if(ii>=Img->height())
            {ii=0;i++;}
        }
        if(i>=Img->width()) break;
    }

    file.close();
    imgchange = *Img;
    img = *Img;
    QWidget::update();
}

