#include "myjqeditwidget.h"
#include <QLayout>

MyJqEditWidget::MyJqEditWidget(QWidget *parent)
    : MySubWidget("7",parent)
{
    MyJqChildWidget *widget = new MyJqChildWidget(this);
    this->setCentralWidget(widget);

}

void MyJqEditWidget::getDefaultState(bool &pro,bool &set,bool &info,QWidget *widget)
{
    pro = true;
    set = false;
    info = false;
    widget = m_setWidget;
}
