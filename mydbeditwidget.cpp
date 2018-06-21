#include "mydbeditwidget.h"
#include <QTextEdit>
#include <QLayout>
#include <QToolBar>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>

MyDBEditWidget::MyDBEditWidget(QWidget *parent)
    : MySubWidget("1",parent)
{
    setTableWidget();
    setupToolBar();
}

void MyDBEditWidget::setupToolBar()
{
    QToolBar *tb = new QToolBar("工具栏",this);
    tb->addWidget(new QLabel(tr(" 类型： "),this));
    tb->addWidget(new QComboBox(this));
    tb->addSeparator();
    tb->addWidget(new QLabel(tr(" 排序一： "),this));
    tb->addWidget(new QComboBox(this));
    tb->addSeparator();
    tb->addWidget(new QLabel(tr(" 排序二： "),this));
    tb->addWidget(new QComboBox(this));
    tb->addSeparator();
    tb->addAction(QIcon(QPixmap(":/png/搜索.png").scaled(QSize(20,20))),"新建工程(W)");
    this->addToolBar(tb);
}

void MyDBEditWidget::setTableWidget()
{
    QTableWidget *table = new QTableWidget(5,5,this);
    QFont font = table->horizontalHeader()->font();
    font.setBold(true);
    table->horizontalHeader()->setFont(font);

    QStringList header;
    header<<tr("用户ID")<<tr("用户名称")<<tr("用户角色")<<tr("密码")<<tr("所属用户组");
    table->setHorizontalHeaderLabels(header);

    table->setAlternatingRowColors(true);
    table->setStyleSheet("selection-background-color:rgb(98,140,178);");
    table->horizontalHeaderItem(0)->setIcon(QIcon(QPixmap(":/png/用户ID.png").scaled(QSize(20,20))));
    table->horizontalHeaderItem(1)->setIcon(QIcon(QPixmap(":/png/用户姓名.png").scaled(QSize(20,20))));
    table->horizontalHeaderItem(2)->setIcon(QIcon(QPixmap(":/png/角色.png").scaled(QSize(20,20))));
    table->horizontalHeaderItem(3)->setIcon(QIcon(QPixmap(":/png/密码.png").scaled(QSize(20,20))));
    table->horizontalHeaderItem(4)->setIcon(QIcon(QPixmap(":/png/用户组.png").scaled(QSize(20,20))));

    for(int i = 0;i < 5;i++)
    {
        table->setItem(i,0,new QTableWidgetItem("admin" + QString::number(i)));
        table->setItem(i,1,new QTableWidgetItem("用户" + QString::number(i)));
        table->setItem(i,2,new QTableWidgetItem("管理员"));
        table->setItem(i,3,new QTableWidgetItem("******"));
        table->setItem(i,4,new QTableWidgetItem("工程编辑组"));
    }
    this->setCentralWidget(table);
}

void MyDBEditWidget::getDefaultState(bool &pro,bool &set,bool &info,QWidget *widget)
{
    pro = true;
    set = false;
    info = true;
    widget = m_setWidget;
}
