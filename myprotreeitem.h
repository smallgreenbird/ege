#ifndef MYPROTREEITEM_H
#define MYPROTREEITEM_H

#include <QTreeWidgetItem>

class MyProTreeItem : public QTreeWidgetItem
{
public:
    MyProTreeItem(QTreeWidget *parent, const QStringList &strings, QString mod, int type = Type);
    MyProTreeItem(QTreeWidgetItem *parent, const QStringList &strings, QString mod, int type = Type);

private:
    QString m_Type;

public:
    QString getType(){return m_Type;}
};

#endif // MYPROTREEITEM_H
