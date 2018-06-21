#include "mysubwidget.h"
#include <QStatusBar>

MySubWidget::MySubWidget(QString type, QWidget *parent)
    : QMainWindow(parent)
    , m_type(type)
    , m_setWidget(new QWidget(this))
{
    this->statusBar()->hide();
}

void MySubWidget::getDefaultState(bool &pro,bool &set,bool &info,QWidget *widget)
{
    pro = true;
    set = true;
    info = true;
    widget = m_setWidget;
}
