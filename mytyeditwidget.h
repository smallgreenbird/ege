#ifndef MYTYEDITWIDGET_H
#define MYTYEDITWIDGET_H

#include "mysubwidget.h"

class MyTyEditWidget : public MySubWidget
{
    Q_OBJECT
public:
    MyTyEditWidget(QWidget *parent = 0);
    void getDefaultState(bool &pro,bool &set,bool &info,QWidget *widget);

private:
    void setupToolBar();
    void setupDockWidgets();
};

#endif // MYTYEDITWIDGET_H
