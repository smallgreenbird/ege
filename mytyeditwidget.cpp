#include "mytyeditwidget.h"
#include <QTextEdit>
#include <QToolBar>

MyTyEditWidget::MyTyEditWidget(QWidget *parent)
    : MySubWidget("2",parent)
{
    QTextEdit *edit = new QTextEdit(this);
    this->setCentralWidget(edit);

    setupToolBar();
    setupDockWidgets();
}

void MyTyEditWidget::setupToolBar()
{
    QToolBar *gn = new QToolBar("功能",this);
    gn->addAction(QIcon(QPixmap(":/draw/剪切.png").scaled(QSize(20,20))),"剪切");
    gn->addAction(QIcon(QPixmap(":/draw/复制.png").scaled(QSize(20,20))),"复制");
    gn->addAction(QIcon(QPixmap(":/draw/粘贴.png").scaled(QSize(20,20))),"粘贴");
    gn->addAction(QIcon(QPixmap(":/draw/删除.png").scaled(QSize(20,20))),"删除");
    gn->addAction(QIcon(QPixmap(":/draw/放大镜.png").scaled(QSize(20,20))),"缩放");
    gn->addSeparator();
    gn->addAction(QIcon(QPixmap(":/draw/撤销.png").scaled(QSize(20,20))),"撤销");
    gn->addAction(QIcon(QPixmap(":/draw/重做.png").scaled(QSize(20,20))),"重做");

    QToolBar *tb = new QToolBar("制图",this);
    tb->addAction(QIcon(QPixmap(":/draw/移动.png").scaled(QSize(20,20))),"选择");
    tb->addAction(QIcon(QPixmap(":/draw/直线.png").scaled(QSize(20,20))),"直线");
    tb->addAction(QIcon(QPixmap(":/draw/pen.png").scaled(QSize(20,20))),"画笔");
    tb->addAction(QIcon(QPixmap(":/draw/刷子.png").scaled(QSize(20,20))),"画刷");
    tb->addAction(QIcon(QPixmap(":/draw/矩形.png").scaled(QSize(20,20))),"矩形");
    tb->addAction(QIcon(QPixmap(":/draw/圆角矩形.png").scaled(QSize(20,20))),"圆角矩形");
    tb->addAction(QIcon(QPixmap(":/draw/五边形.png").scaled(QSize(20,20))),"多边形");
    tb->addAction(QIcon(QPixmap(":/draw/圆形.png").scaled(QSize(20,20))),"圆形");

    this->addToolBar(gn);
    this->addToolBar(tb);
}

void MyTyEditWidget::setupDockWidgets()
{

}

void MyTyEditWidget::getDefaultState(bool &pro,bool &set,bool &info,QWidget *widget)
{
    pro = true;
    set = true;
    info = false;
    widget = m_setWidget;
}
