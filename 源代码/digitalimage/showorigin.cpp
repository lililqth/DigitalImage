#include"showorigin.h"
extern QImage img;//保存原图

showorigin::showorigin(){
    this->setFixedSize(500,400);
    //this->setStyleSheet("border-radius: 10px border: 1px solid #AFBFD6; ");
}

void showorigin::paintEvent(QPaintEvent *event)
{
    QImage  imgshoworigin;//真正用来显示的图像
    if(!img.isNull()){
        if(img.width()>500||img.height()>400)
        {
               imgshoworigin = img.scaled(500,400,  Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        else
        {
            imgshoworigin=img;
        }
        //int cx=(525-imgshoworigin.width())/2;
        //int cy=(300-imgshoworigin.height())/2;
        //this->move(cx,cy);
        this->resize(imgshoworigin.width(),imgshoworigin.height());
        painterorigin.begin(this);
        painterorigin.drawImage(0,0,imgshoworigin,0,0,imgshoworigin.width(),imgshoworigin.height());
        painterorigin.end();
    }
}



