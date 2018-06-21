#include "mysetdockwidget.h"
#include <QTableWidget>

MySetDockWidget::MySetDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
    :MyDockWidget(title,parent,flags)
{
    //QTableWidget *table = new QTableWidget(0,2,this);

}
