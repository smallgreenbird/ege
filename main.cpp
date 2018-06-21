#include "mainwindow.h"

#include <QApplication>
#include <QPainterPath>
#include <QPainter>
#include <QMap>
#include <QDebug>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QApplication::setStyle("windowsxp");
    MainWindow mainWin;
    QFont font("Microsoft YaHei", 10, 50);
    mainWin.setFont(font);
    mainWin.show();
    return app.exec();
}
