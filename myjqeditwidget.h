#ifndef MYJQEDITWIDGET_H
#define MYJQEDITWIDGET_H

#include "mysubwidget.h"
#include "myjqchildwidget.h"

class MyJqEditWidget : public MySubWidget
{
    Q_OBJECT
public:
    MyJqEditWidget(QWidget *parent = 0);
    void getDefaultState(bool &pro,bool &set,bool &info,QWidget *widget);
};

#endif // MYJQEDITWIDGET_H
