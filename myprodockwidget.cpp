#include "myprodockwidget.h"
#include "myprotreeitem.h"
#include <QDomDocument>
#include <QFile>
#include <QDebug>

MyProDockWidget::MyProDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
    : MyDockWidget(title,parent,flags)
{
    QTreeWidget *tree = new QTreeWidget(this);
    setWidget(tree);
    creatTree(tree);

    QObject::connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(TreeItemDoubleClicked(QTreeWidgetItem*,int)));
}

void MyProDockWidget::TreeItemDoubleClicked(QTreeWidgetItem *item,int column)
{
    MyProTreeItem *treeitem = dynamic_cast<MyProTreeItem *>(item);
    if(treeitem == NULL)
        return;
    QString type = treeitem->getType();
    QString name = treeitem->text(column);
    emit addSubWidget(name,type);
}

bool MyProDockWidget::creatTree(QTreeWidget *tree)
{
    QDomDocument doc("project");
    QFile file("D:\\qtcode\\mainwindow\\project.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();
    QDomElement docElem = doc.documentElement();

    tree->setColumnCount(1);
    tree->setHeaderLabel(docElem.attribute("name"));

    QDomNode n0 = docElem.firstChild();
    while (!n0.isNull())
    {
        QDomElement e0 = n0.toElement();
        if (!e0.isNull())
        {
            MyProTreeItem *item0 = new MyProTreeItem(tree,QStringList(e0.attribute("name")),e0.attribute("type"));
            QDomNode n1 = e0.firstChild();
            while (!n1.isNull())
            {
                QDomElement e1 = n1.toElement();
                if (!e1.isNull())
                {
                    MyProTreeItem *item1 = new MyProTreeItem(item0,QStringList(e1.attribute("name")),e1.attribute("type"));
                    item0->addChild(item1);
                    QDomNode n2 = e1.firstChild();
                    while (!n2.isNull())
                    {
                        QDomElement e2 = n2.toElement();
                        if (!e2.isNull())
                        {
                            MyProTreeItem *item2 = new MyProTreeItem(item1,QStringList(e2.attribute("name")),e2.attribute("type"));
                            item1->addChild(item2);
                        }
                        n2 = n2.nextSibling();
                    }
                }
                n1 = n1.nextSibling();
            }
        }
        n0 = n0.nextSibling();
    }
    return true;
}
