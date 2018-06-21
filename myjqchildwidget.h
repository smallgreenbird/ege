#ifndef MYJQCHILDWIDGET_H
#define MYJQCHILDWIDGET_H

#include <QWidget>

namespace Ui {
class MyJqChildWidget;
}

class MyJqChildWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyJqChildWidget(QWidget *parent = 0);
    ~MyJqChildWidget();

private:
    Ui::MyJqChildWidget *ui;

private:
    void setTableWidget();

public slots:
    void cellClicked(int row,int column);
    void cellClicked(int row);
    void textChange();
};

#endif // MYJQCHILDWIDGET_H
