#include"image.h"
#include<math.h>
extern QImage img;
extern QImage imgchange;
extern QPainter * painter;
QImage imgzhuan;
QImage imgzhuanbeifen;
void openimage::suofangzuijin(){
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    bool ok=false;
    double a=QInputDialog::getDouble(this,QString::fromLocal8Bit(""),QString::fromLocal8Bit("请输入缩放比例"),1.5,0.1,10.0,1,&ok,0);
    multiple*=a;
    if(false==ok)
    {
        return;
    }
    int w=imgchange.width();
    int h=imgchange.height();
    int ww=(int)(w*a);
    int hh=(int)(h*a);
    int i,j,ii,jj;
    QImage imgzoom=imgchange;
    imgzoom=imgzoom.scaled(ww,hh,
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    ww=imgzoom.width();
    hh=imgzoom.height();
    for(i=0;i<ww;i++){
        for(j=0;j<hh;j++){
            ii=(int)(i/a);
            jj=(int)(j/a);
            QRgb pixel = imgchange.pixel(ii,jj);
            imgzoom.setPixel(i,j,pixel);
        }
    }
    this->resize(imgzoom.width(),imgzoom.height());
    imgchange=imgzoom;
    QString string=QString::fromLocal8Bit("已从")+
            QString::number ( w,10 )+
            QString::fromLocal8Bit("*")+
            QString::number ( h,10 )+
            QString::fromLocal8Bit(" 缩放到 ")+
            QString::number ( ww,10 )+
            QString::fromLocal8Bit("*")+
            QString::number ( hh,10 );
    QMessageBox::information(this,QString::fromLocal8Bit("成功！"),string);
    QWidget::update();
}

void openimage::suofangxianxing(){
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    bool ok=false;
    double a=QInputDialog::getDouble(this,QString::fromLocal8Bit(""),QString::fromLocal8Bit("请输入缩放比例"),1.5,0.1,3.0,1,&ok,0);
    multiple*=a;
    if(false==ok)
    {
        return;
    }
    int w=imgchange.width();
    int h=imgchange.height();
    int ww=(int)(w*a);
    int hh=(int)(h*a);
    int i,j;
    QImage imgzoom=imgchange;
    imgzoom=imgzoom.scaled(ww,hh,
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    ww=imgzoom.width();
    hh=imgzoom.height();
    double ii,jj;
    QRgb pixelll,pixellh,pixelhl,pixelhh;
    int xLower,xHigher,zLower,zHigher;

    for(i=0;i<ww-1;i++){
        for(j=0;j<hh-1;j++){
            ii=i/a;
            jj=j/a;
            xLower=(int)ii;
            xHigher=xLower+1;
            zLower=int(jj);
            zHigher=zLower+1;//计算四个点


            pixelll = imgchange.pixel(xLower,zLower);
            pixellh = imgchange.pixel(xLower,zHigher);
            pixelhl = imgchange.pixel(xHigher,zLower);
            pixelhh = imgchange.pixel(xHigher,zHigher);//获取四个点像素
            int r11,r12,r21,r22,rr;
            r11=qRed(pixelll);
            r12=qRed(pixellh);
            r21=qRed(pixelhl);
            r22=qRed(pixelhh);
            rr=(int)(r11*(xLower+1-ii)*(zLower+1-jj)+r12*(xLower+1-ii)*(jj-zLower)
                     +r21*(ii-xLower)*(zLower+1-jj)+r22*(ii-xLower)*(jj-zLower));

            int g11,g12,g21,g22,gg;
            g11=qGreen(pixelll);
            g12=qGreen(pixellh);
            g21=qGreen(pixelhl);
            g22=qGreen(pixelhh);
            gg=(int)(g11*(xLower+1-ii)*(zLower+1-jj)+g12*(xLower+1-ii)*(jj-zLower)
                     +g21*(ii-xLower)*(zLower+1-jj)+g22*(ii-xLower)*(jj-zLower));

            int b11,b12,b21,b22,bb;
            b11=qBlue(pixelll);
            b12=qBlue(pixellh);
            b21=qBlue(pixelhl);
            b22=qBlue(pixelhh);
            bb=(int)(b11*(xLower+1-ii)*(zLower+1-jj)+b12*(xLower+1-ii)*(jj-zLower)
                     +b21*(ii-xLower)*(zLower+1-jj)+b22*(ii-xLower)*(jj-zLower));

            QRgb pixel = qRgb(rr,gg,bb);
            imgzoom.setPixel(i,j,pixel);
        }
    }
    this->resize(imgzoom.width(),imgzoom.height());
    imgchange=imgzoom;
    QString string=QString::fromLocal8Bit("已从")+
            QString::number ( w,10 )+
            QString::fromLocal8Bit("*")+
            QString::number ( h,10 )+
            QString::fromLocal8Bit(" 缩放到 ")+
            QString::number ( ww,10 )+
            QString::fromLocal8Bit("*")+
            QString::number ( hh,10 );
    QMessageBox::information(this,QString::fromLocal8Bit("成功！"),string);
    QWidget::update();

}

void openimage::jingxiang(){
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }
    int w=imgchange.width();
    int h=imgchange.height();
    int i,j;
    for(i=0;i<w/2;i++){
        for(j=0;j<h;j++){
            QRgb pixel = imgchange.pixel(i,j);
            QRgb pixel1 = imgchange.pixel(w-i-1,j);
            imgchange.setPixel(w-i-1,j,pixel);
            imgchange.setPixel(i,j,pixel1);
        }
    }
    QWidget::update();
}

void openimage::xuanzhuan()
{
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }

   /* imgzhuan=img;
    imgzhuan.fill(0xF0F0F0);
    imgchange=img;
    wchange=img.width();//需要缩放图像的尺寸
    hchange=img.height();
    wwchange=hchange/(sqrt(wchange*wchange+hchange*hchange))*wchange;//理论变小后的尺寸
    hhchange=hchange/(sqrt(wchange*wchange+hchange*hchange))*hchange;
    imgzhuanbeifen = img.scaled(wwchange,hhchange,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    wwchange=imgzhuanbeifen.width();//实际变小后的尺寸
    hhchange=imgzhuanbeifen.height();*/
    slider *getvalue = new slider(this,-90,90,0,QString::fromLocal8Bit("旋转角度"),1);
    getvalue->show();
}

void openimage::makexuanzhuan(int a)
{
    /*int w=wchange;
    int h=hchange;
    int ww=wwchange;
    int hh=hhchange;
    int i,j;
    int x=w/2;
    int y=h/2;
    imgchange=imgzhuanbeifen;
    imgzhuan=img;
    imgzhuan.fill(0xF0F0F0);
    int xx=ww/2;
    int yy=hh/2;//小图
    double aa=(double)(a)/180*3.1415926;
    for(i=0;i<ww;i++){
        for(j=0;j<hh;j++){
            int ii,jj;
            QRgb pixel = imgchange.pixel(i,j);
            ii=(i-xx)*cos(aa)-(j-yy)*sin(aa)+x;
            jj=(i-xx)*sin(aa)+(j-yy)*cos(aa)+y;
            if((ii>0&&ii<w-1)&&(jj>0&&jj<h-1)){
                imgzhuan.setPixel(ii,jj,pixel);
                imgzhuan.setPixel(ii+1,jj+1,pixel);
                imgzhuan.setPixel(ii+1,jj-1,pixel);
                imgzhuan.setPixel(ii-1,jj+1,pixel);
                imgzhuan.setPixel(ii-1,jj-1,pixel);
            }
        }
    }
    imgchange=imgzhuan;*/
    QImage imgRotate;
    QMatrix matrix;
    matrix.rotate(a);
    imgRotate = img.transformed(matrix);
    imgchange=imgRotate;
    QWidget::update();
}

void openimage::pingyi()
{
    QImage imgpingyi=imgchange;
    if(img.isNull())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("请打开一张图片！"));
        return;
    }

    int w=imgchange.width();
    int h=imgchange.height();
    bool ok=false;
    int a=QInputDialog::getInteger(this,QString::fromLocal8Bit(""),QString::fromLocal8Bit("请输入平移距离"),w/2,-w,+w,0,&ok,0);
    int i,j;
    for(i=0;i<w;i++){
        for(j=0;j<h;j++){
            QRgb pixel = imgchange.pixel(i,j);
            if(i+a>=0&&i+a<w)
            {
                imgpingyi.setPixel(i+a,j,pixel);
            }
            else if(i+a>=w)
            {
                imgpingyi.setPixel(i+a-w,j,pixel);
            }
            else
            {
                imgpingyi.setPixel(i+a+w,j,pixel);
            }

        }
    }
    imgchange=imgpingyi;
    QWidget::update();
}

