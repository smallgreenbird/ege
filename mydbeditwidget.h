#ifndef MYDBEDITWIDGET_H
#define MYDBEDITWIDGET_H

#include "mysubwidget.h"

class MyDBEditWidget : public MySubWidget
{
    Q_OBJECT
public:
    MyDBEditWidget(QWidget *parent = 0);
    void getDefaultState(bool &pro,bool &set,bool &info,QWidget *widget);
private:
    void setupToolBar();
    void setTableWidget();
};

#endif // MYDBEDITWIDGET_H
