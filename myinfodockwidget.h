#ifndef MYINFODOCKWIDGET_H
#define MYINFODOCKWIDGET_H

#include "mydockwidget.h"

class MyInfoDockWidget : public MyDockWidget
{
    Q_OBJECT
public:
    MyInfoDockWidget(const QString &title, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
};

#endif // MYINFODOCKWIDGET_H
