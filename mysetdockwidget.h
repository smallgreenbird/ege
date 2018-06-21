#ifndef MYSETDOCKWIDGET_H
#define MYSETDOCKWIDGET_H

#include "mydockwidget.h"

class MySetDockWidget : public MyDockWidget
{
    Q_OBJECT
public:
    MySetDockWidget(const QString &title, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
};

#endif // MYSETDOCKWIDGET_H
