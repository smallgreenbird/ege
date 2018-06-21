#include "mainwindow.h"

#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QSignalMapper>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QToolBar>
#include <QMdiArea>
#include "mysubwidget.h"
#include "mydbeditwidget.h"
#include "mytyeditwidget.h"
#include "myjqeditwidget.h"


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      pro_dock(NULL),
      set_dock(NULL),
      info_dock(NULL)
{
    setObjectName("MainWindow");
    setWindowTitle("工程生成环境");

    mdiArea = new QMdiArea(this);
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QObject::connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow *)),this,SLOT(subWindowActivated(QMdiSubWindow *)));
    setCentralWidget(mdiArea);

    setupToolBar();
    setupMenuBar();
    setupDockWidgets();

    statusBar()->showMessage(tr("就绪"));

    loadLayout();
}


void MainWindow::setupToolBar()
{
    QToolBar *tb = new QToolBar("工具栏",this);

    tb->addAction(QIcon(QPixmap(":/png/新建工程.png").scaled(QSize(20,20))),"新建工程(W)");
    tb->addAction(QIcon(QPixmap(":/png/新建.png").scaled(QSize(20,20))),"新建(N)");
    tb->addAction(QIcon(QPixmap(":/png/保存.png").scaled(QSize(20,20))),"保存(S)");
    tb->addAction(QIcon(QPixmap(":/png/保存全部.png").scaled(QSize(20,20))),"保存全部(L)");
    tb->addSeparator();
    tb->addAction(QIcon(QPixmap(":/png/运行中.png").scaled(QSize(20,20))),"运行(R)");
    tb->addAction(QIcon(QPixmap(":/png/停止.png").scaled(QSize(20,20))),"停止(S)");
    tb->addAction(QIcon(QPixmap(":/png/钥匙.png").scaled(QSize(20,20))),"权限登录(U)");
    tb->addSeparator();
    tb->addAction(QIcon(QPixmap(":/png/工程.png").scaled(QSize(20,20))),"工程资源管理器");
    tb->addAction(QIcon(QPixmap(":/png/编辑属性.png").scaled(QSize(20,20))),"属性设置框");
    tb->addAction(QIcon(QPixmap(":/png/信息.png").scaled(QSize(20,20))),"信息框");
    this->addToolBar(tb);
}

void MainWindow::setupMenuBar()
{
    QMenu *menu = menuBar()->addMenu(tr("文件(&F)"));

    menu->addAction(tr("新建工程(&W)..."));
    menu->addAction(tr("打开工程(&J)..."));
    menu->addAction(tr("关闭工程(&K)..."));
    menu->addAction(tr("发布工程(&D)..."));
    menu->addAction(tr("工程备份(&Y)..."));
    menu->addAction(tr("工作空间(&E)..."));
    menu->addAction(tr("创建桌面图标"));
    menu->addSeparator();
    menu->addAction(tr("新建(&N)..."));
    menu->addAction(tr("关闭(&C)"));
    menu->addAction(tr("保存(&S)"));
    menu->addAction(tr("保存所有(&L)"));
    menu->addAction(tr("另存为(&A)..."));
    menu->addSeparator();
    menu->addAction(tr("打印(&P)"));
    menu->addAction(tr("打印设置(&R)..."));
    menu->addAction(tr("退出(&X)"),this, &QWidget::close);

    dockWidgetMenu = menuBar()->addMenu(tr("视图(&V)"));
}

void MainWindow::setDockOptions()
{
    DockOptions opts;
    opts |= AnimatedDocks;
    opts |= AllowNestedDocks;
    opts |= AllowTabbedDocks;
    opts |= ForceTabbedDocks;
    opts |= GroupedDragging;
    QMainWindow::setDockOptions(opts);
}

void MainWindow::subWindowActivated(QMdiSubWindow *widget)
{
    if(widget == NULL)
        return;
    QWidget *temp = widget->widget();
    MySubWidget *sub_widget = dynamic_cast<MySubWidget *>(temp);
    if(sub_widget == NULL)
        return;
    bool bpro = false,bset = false,binfo = false;
    QWidget *set_widget = NULL;
    sub_widget->getDefaultState(bpro,bset,binfo,set_widget);
    bpro ? pro_dock->show() : pro_dock->hide();
    bset ? set_dock->show() : set_dock->hide();
    binfo? info_dock->show(): info_dock->hide();
    if(set_widget != NULL)
    {
        set_dock->setWidget(set_widget);
    }
}

void MainWindow::saveLayout()
{
    QString fileName = "layout";
        //= QFileDialog::getSaveFileName(this, tr("Save layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    QByteArray geo_data = saveGeometry();
    QByteArray layout_data = saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) {
        QString msg = tr("Error writing to %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

void MainWindow::loadLayout()
{
    QString fileName = "layout";
        //= QFileDialog::getOpenFileName(this, tr("Load layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok) {
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok) {
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok)
        ok = restoreGeometry(geo_data);
    if (ok)
        ok = restoreState(layout_data);

    if (!ok) {
        QString msg = tr("Error reading %1").arg(QDir::toNativeSeparators(fileName));
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

class DockWidgetAreaCornerFunctor {
public:
    explicit DockWidgetAreaCornerFunctor(QMainWindow *mw, Qt::Corner c, Qt::DockWidgetArea a)
        : m_mainWindow(mw), m_area(a), m_corner(c) {}

    void operator()() const { m_mainWindow->setCorner(m_corner, m_area); }

private:
    QMainWindow *m_mainWindow;
    Qt::DockWidgetArea m_area;
    Qt::Corner m_corner;
};

static QAction *addCornerAction(const QString &text, QMainWindow *mw, QMenu *menu, QActionGroup *group,
                                Qt::Corner c, Qt::DockWidgetArea a)
{
    QAction *result = menu->addAction(text, mw, DockWidgetAreaCornerFunctor(mw, c, a));
    result->setCheckable(true);
    group->addAction(result);
    return result;
}

void MainWindow::setupDockWidgets()
{
    QMenu *cornerMenu = dockWidgetMenu->addMenu(tr("左上角"));
    QActionGroup *group = new QActionGroup(this);
    group->setExclusive(true);
    QAction *cornerAction = addCornerAction(tr("靠上"), this, cornerMenu, group, Qt::TopLeftCorner, Qt::TopDockWidgetArea);
    cornerAction->setChecked(true);
    addCornerAction(tr("靠左"), this, cornerMenu, group, Qt::TopLeftCorner, Qt::LeftDockWidgetArea);

    cornerMenu = dockWidgetMenu->addMenu(tr("右上角"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    cornerAction = addCornerAction(tr("靠上"), this, cornerMenu, group, Qt::TopRightCorner, Qt::TopDockWidgetArea);
    cornerAction->setChecked(true);
    addCornerAction(tr("靠右"), this, cornerMenu, group, Qt::TopRightCorner, Qt::RightDockWidgetArea);

    cornerMenu = dockWidgetMenu->addMenu(tr("左下角"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    cornerAction = addCornerAction(tr("靠下"), this, cornerMenu, group, Qt::BottomLeftCorner, Qt::BottomDockWidgetArea);
    cornerAction->setChecked(true);
    addCornerAction(tr("靠左"), this, cornerMenu, group, Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

    cornerMenu = dockWidgetMenu->addMenu(tr("右下角"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    cornerAction = addCornerAction(tr("靠下"), this, cornerMenu, group, Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
    cornerAction->setChecked(true);
    addCornerAction(tr("靠右"), this, cornerMenu, group, Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    dockWidgetMenu->addSeparator();

    pro_dock = new MyProDockWidget(tr("工程资源管理器"),this,0);
    addDockWidget(Qt::LeftDockWidgetArea,pro_dock);
    dockWidgetMenu->addAction(pro_dock->toggleViewAction());

    set_dock = new MySetDockWidget(tr("属性设置框"),this,0);
    addDockWidget(Qt::LeftDockWidgetArea,set_dock);
    dockWidgetMenu->addAction(set_dock->toggleViewAction());

    info_dock = new MyInfoDockWidget(tr("信息框"),this,0);
    addDockWidget(Qt::BottomDockWidgetArea,info_dock);
    dockWidgetMenu->addAction(info_dock->toggleViewAction());

    connect(pro_dock,SIGNAL(addSubWidget(QString,QString)),this,SLOT(addSubWidget(QString,QString)));

    pro_dock->show();
    set_dock->hide();
    info_dock->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveLayout();
    event->accept();
}

QMdiSubWindow* MainWindow::widgetHasOpen(QString name,QString type)
{
    QList<QMdiSubWindow *> windowlist = mdiArea->subWindowList();
    for(int i = 0;i < windowlist.count();i++)
    {
        QMdiSubWindow *subwindow = windowlist.at(i);
        MySubWidget *widget = dynamic_cast<MySubWidget *>(subwindow->widget());
        if(widget == NULL)
            continue;
        QString window_title = widget->windowTitle();
        QString window_type = widget->getType();
        if(window_title == name && window_type == type)
            return subwindow;
    }
    return NULL;
}

void MainWindow::addSubWidget(QString name,QString type)
{
    MySubWidget *widget = NULL;
    QMdiSubWindow *tempwindow = widgetHasOpen(name,type);
    if(tempwindow != NULL)
    {
        mdiArea->setActiveSubWindow(tempwindow);
        return;
    }

    if(type == "1")     //数据库管理，数据表界面
    {
        widget = new MyDBEditWidget(this);
    }
    else if(type == "2")    //图元管理，图元编辑界面
    {
        widget = new MyTyEditWidget(this);

    }
    else if(type == "3")    //图形管理，图形编辑界面
    {

    }
    else if(type == "4")    //装置管理，装置配置界面
    {

    }
    else if(type == "5")    //报表管理，报表模板制作界面
    {

    }
    else if(type == "6")    //告警管理，告警配置界面
    {

    }
    else if(type == "7")    //机器节点
    {
        widget = new MyJqEditWidget(this);
    }

    if(widget != NULL)
    {
        widget->setWindowTitle(name);
        mdiArea->addSubWindow(widget);
        widget->showMaximized();
    }
}


