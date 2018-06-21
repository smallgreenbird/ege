#include "myinfodockwidget.h"
#include <QTextEdit>

MyInfoDockWidget::MyInfoDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
    :MyDockWidget(title,parent,flags)
{
    QTextEdit *edit = new QTextEdit(this);
    this->setWidget(edit);
}
