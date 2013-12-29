#include <QApplication>
#include "mainwindow.h"
#include<QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPixmap pixmap=QPixmap("hello1.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QString::fromLocal8Bit("Setting up the main window..."),topRight, Qt::white);
    splash->showMessage(QString::fromLocal8Bit("Loading modules..."), topRight,Qt::white);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK")); //路径名支持中文
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK")); //QString支持中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK")); //string支持中文
    QApplication::setFont(QFont(QString::fromLocal8Bit("宋体"), 10, QFont::Normal));
    w.setWindowTitle(QString::fromLocal8Bit("数字图像处理"));
    w.show();
    splash->finish(&w);
    delete splash;
    return a.exec();
}

