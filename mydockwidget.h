#ifndef MYDOCKWIDGET_H
#define MYDOCKWIDGET_H

#include <QWidget>
#include <QDockWidget>

class MyDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    MyDockWidget(const QString &title, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
};

#endif // MYDOCKWIDGET_H
