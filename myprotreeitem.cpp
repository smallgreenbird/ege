#include "myprotreeitem.h"

MyProTreeItem::MyProTreeItem(QTreeWidget *parent, const QStringList &strings, QString mod, int type)
    : QTreeWidgetItem(parent,strings,type)
    , m_Type(mod)
{

}

MyProTreeItem::MyProTreeItem(QTreeWidgetItem *parent, const QStringList &strings, QString mod, int type)
    : QTreeWidgetItem(parent,strings,type)
    , m_Type(mod)
{

}
