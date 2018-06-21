#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "myprodockwidget.h"
#include "mysetdockwidget.h"
#include "myinfodockwidget.h"

class ToolBar;
QT_FORWARD_DECLARE_CLASS(QMenu)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR,Qt::WindowFlags flags = 0);

public slots:
    void saveLayout();              //保存布局
    void loadLayout();              //载入布局
    void setDockOptions();          //设置停靠窗口菜单项

    void subWindowActivated(QMdiSubWindow *widget);     //活跃子窗口变化
    void addSubWidget(QString name, QString type);      //添加子窗口

private:
    void setupToolBar();            //设置工具栏
    void setupMenuBar();            //设置菜单栏
    void setupDockWidgets();        //设置悬停窗
    QMdiSubWindow* widgetHasOpen(QString name,QString type);    //检测子窗口是否已经开启

    QMenu *dockWidgetMenu;
    QMdiArea *mdiArea;
    MyDockWidget *pro_dock;
    MyDockWidget *set_dock;
    MyDockWidget *info_dock;

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
