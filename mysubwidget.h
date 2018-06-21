#ifndef MYSUBWIDGET_H
#define MYSUBWIDGET_H

#include <QMainWindow>

class MySubWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit MySubWidget(QString type,QWidget *parent = 0);
    QString getType(){return m_type;}

    //获取停靠窗消隐状态，
    virtual void getDefaultState(bool &pro,bool &set,bool &info,QWidget *widget);

    QWidget *m_setWidget;
signals:

public slots:

private:
    QString m_type;
};

#endif // MYSUBWIDGET_H
