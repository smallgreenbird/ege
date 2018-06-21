#ifndef MYPRODOCKWIDGET_H
#define MYPRODOCKWIDGET_H

#include "mydockwidget.h"
#include <QTreeWidget>

class MyProDockWidget : public MyDockWidget
{
    Q_OBJECT
public:
    MyProDockWidget(const QString &title, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

private:
    bool creatTree(QTreeWidget *tree);
public slots:
    void TreeItemDoubleClicked(QTreeWidgetItem *item,int column);

signals:
    void addSubWidget(QString name,QString type);
};

#endif // MYPRODOCKWIDGET_H
