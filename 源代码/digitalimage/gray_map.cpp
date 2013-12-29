#include "gray_map.h"
#include "ui_gray_map.h"

extern QImage img;//保存原图
extern QImage imgchange;//保存修改以后的图像
extern bool grayd;//标记是否已经灰度华
extern bool erzhid;//标记是否已经二值化
//extern openimage *openpic;
int flagright;
gray_map::gray_map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gray_map)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(GetMinimumThreshold()));
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    paintall();
}

void gray_map::paintall()
{
    w=ui->labelgray->width();//label 的宽度
    h=ui->labelgray->height();//label 的长度


    pix = new QPixmap(w,h);
    pix->fill(0xF0F0F0);
    painter = new QPainter(pix);//用于显示灰度直方图

    memset(Statistics,0.0,sizeof(Statistics));
    memset(StatisticsS,0.0,sizeof(StatisticsS));
    double aver=0.0;
    if(!imgchange.isNull())
    {
        painter->setPen(QPen(Qt::black,5));
        h-=5;
        if(flagright==0)
        {
            ww=img.width();
            hh=img.height();
        }
        else
        {
            ww=imgchange.width();
            hh=imgchange.height();
        }

        int gray;
        for(int i=0;i<ww;i++){
            for(int j=0;j<hh;j++){
                if(flagright==0)//如果需要显示原始图像的直方图
                {
                    gray = qGray(img.pixel(i,j));//灰度化该像素
                }
                else
                {
                    if(0==grayd&&0==erzhid)//如果该图像还没有被处理过
                    {
                        gray = qGray(imgchange.pixel(i,j));
                    }
                    else
                    {
                        gray = qRed(imgchange.pixel(i,j));//直接读取R以免错误
                    }
                }
                aver+=gray;
                Statistics[gray]++;//遍历图像统计灰度信息
                StatisticsS[gray]++;//遍历图像统计灰度信息
            }
        }

        painter->setPen(QPen(Qt::black,2));
        for(int i=0;i<256;i++)
        {
            //Statistics[i]/=ww*hh;
            painter->drawLine(10+(i+1),h-2.5,10+(i+1),h-Statistics[i]/(ww*hh)*5000-2.5);//绘制直方图
        }

        ui->labelgray->setPixmap(*pix);
        QString average;//平均灰度值
        average+=QString::fromLocal8Bit("平均灰度值：");
        average+=QString::number((int)aver/(hh*ww),10);
        average+="\n";
        ui->labelaverage->setText(average);


        QString middle;//中值灰度值
        int n,i;
        double standard_deviation;
        for(i=0,n=0,standard_deviation=0.0;i<256;i++)
        {
            if(Statistics[i]!=0)
            {
                standard_deviation+=(i-aver/(hh*ww))*(i-aver/(hh*ww))*Statistics[i];//*ww*hh;
                n++;
            }
        }
        i=0;
        for(int ii=0;i<n/2;ii++)
        {
            if(Statistics[ii]/(ww*hh)!=0.0)
            {
                i++;
            }
        }
        middle+=QString::fromLocal8Bit("中值灰度值： ");
        middle+=QString::number((int)i,10);
        middle+="\n";
        ui->labelmiddle->setText(middle);



        QString deviation;//标准差
        standard_deviation=sqrt(standard_deviation/(ww*hh));
        deviation+=QString::fromLocal8Bit("标准差：");
        deviation+=QString::number((int)standard_deviation,10);
        deviation+="\n";
        ui->labelStandard->setText(deviation);


        QString sum;//像素总数
        sum+=QString::fromLocal8Bit("像素总数：");
        sum+=QString::number(ww*hh,10);
        sum+="\n";
        ui->labelsum->setText(sum);
    }

    painter->end();
    QWidget::update();
}

void gray_map::painthistogram(int num)
{
    pix->fill(0xF0F0F0);
    QPainter *painter1 = new QPainter(pix);//用于显示修改后的灰度直方图

    if(num==2)
    {
        int dot[2]={0,0};
        painter1->setPen(QPen(Qt::black,1));
        for(int i=0,j=0;i<256;i++)
        {
            if(Statistics[i]>0)
            {
                dot[j++]=i;
                painter1->drawLine(10+(i+1),h-2.5,10+(i+1),-2.5);//绘制直方图
            }
        }
        painter1->setPen(QPen(Qt::white,3));
        painter1->drawLine(10+((dot[0]+dot[1])/2+1),h-2.5,10+((dot[0]+dot[1])/2+1),-2.5);//绘制直方图
        painter1->end();
        ui->labelgray->setPixmap(*pix);
        ui->labelgray->update();
        return;
    }

    bool peakfound=false;

    for(int i=1;i<255;i++)
    {
        if(num==0)
        {
            if(Statistics[i-1]<Statistics[i]&&Statistics[i]>Statistics[i+1])
            {
                peakfound=true;
            }
            if(peakfound==true&&Statistics[i-1]>Statistics[i]&&Statistics[i]<Statistics[i+1])
            {
                painter1->setPen(QPen(Qt::white,3));
                painter1->drawLine(10+(i+1),h-2.5,10+(i+1),-2.5);//绘制直方图
                painter1->setPen(Qt::black);
            }
            else
            {
                painter1->drawLine(10+(i+1),h-2.5,10+(i+1),h-Statistics[i]/(ww*hh)*5000-2.5);//绘制直方图
            }

        }
        else
        {

            painter1->drawLine(10+(i+1),h-2.5,10+(i+1),h-Statistics[i]/(ww*hh)*5000-2.5);//绘制直方图
        }
    }
    painter1->end();
    ui->labelgray->setPixmap(*pix);
    ui->labelgray->update();
}

void gray_map::GetMinimumThreshold()
{
    int Iter=0;
    int num=0;
    for(int i=0;i<256;i++)
    {
        if(Statistics[i]!=0)
        {
            num++;
        }
    }
    if(num==1)
    {
        painthistogram(1);
        return;
    }
    if(num==2)
    {
        painthistogram(2);
        return;
    }
    /*if(Statistics[0]>0&&Statistics[255]>0&&Statistics[128]==0)
    {
        int biaoji=0;
        for(int i=1;i<255;i++)
        {
            if(Statistics[i]!=0)
            {
                    biaoji=1; // 代表不是二值图
            }
        }
        if(biaoji==0)
        {
            Statistics[3]=Statistics[0];
            Statistics[252]=Statistics[255];
            Statistics[0]=0;
            Statistics[255]=0;
        }
    }*/
    while(!IsDimodal())
    {
        StatisticsS[0] = (Statistics[0]+Statistics[0]+Statistics[1])/3;
        for(int i=1;i<255;i++)
        {
            StatisticsS[i] = (Statistics[i-1]+Statistics[i]+Statistics[i+1])/3;
        }
        StatisticsS[255] = (Statistics[254]+Statistics[255]+Statistics[255])/3;
        Iter++;
        if(Iter>1000)
        {
            break;
        }
        memcpy(Statistics,StatisticsS,sizeof(StatisticsS));
    }
    painthistogram(0);
}

bool gray_map::IsDimodal()
{
    int count=0;

    for(int i=1;i<255;i++)
    {
        if(StatisticsS[i-1]<StatisticsS[i]&&StatisticsS[i]>StatisticsS[i+1])
        {
            count++;
            if(count>2)
            {
                return false;
            }
        }
    }
    if(count==2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

gray_map::~gray_map()
{
    delete ui;
}
