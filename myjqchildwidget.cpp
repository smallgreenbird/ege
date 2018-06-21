#include "myjqchildwidget.h"
#include "ui_myjqchildwidget.h"

MyJqChildWidget::MyJqChildWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyJqChildWidget)
{
    ui->setupUi(this);

    setTableWidget();
}

MyJqChildWidget::~MyJqChildWidget()
{
    delete ui;
}

void MyJqChildWidget::setTableWidget()
{
    QTableWidget *table = ui->tableWidget;
    table->setRowCount(100);
    table->setColumnCount(7);
    QFont font = table->horizontalHeader()->font();
    font.setBold(true);
    table->horizontalHeader()->setFont(font);

    QStringList header;
    header<<tr("序号")<<tr("机器名")<<tr("1号网段IP")<<tr("2号网段IP")<<tr("机器类型")<<tr("是否本地")<<tr("描述信息");
    table->setHorizontalHeaderLabels(header);

    table->setAlternatingRowColors(true);
    table->setStyleSheet("selection-background-color:rgb(98,140,178);selection-color:rgb(255,255,255);");
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(false);
    table->setColumnWidth(0,60);
    table->setColumnWidth(1,185);
    table->setColumnWidth(2,185);
    table->setColumnWidth(3,185);
    table->setColumnWidth(4,185);
    table->setColumnWidth(5,185);

//    table->horizontalHeaderItem(0)->setIcon(QIcon(QPixmap(":/png/用户ID.png").scaled(QSize(20,20))));
//    table->horizontalHeaderItem(1)->setIcon(QIcon(QPixmap(":/png/用户姓名.png").scaled(QSize(20,20))));
//    table->horizontalHeaderItem(2)->setIcon(QIcon(QPixmap(":/png/角色.png").scaled(QSize(20,20))));
//    table->horizontalHeaderItem(3)->setIcon(QIcon(QPixmap(":/png/密码.png").scaled(QSize(20,20))));
//    table->horizontalHeaderItem(4)->setIcon(QIcon(QPixmap(":/png/用户组.png").scaled(QSize(20,20))));

    for(int i = 0;i < 100;i++)
    {
        table->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        table->setItem(i,1,new QTableWidgetItem());
        table->setItem(i,2,new QTableWidgetItem());
        table->setItem(i,3,new QTableWidgetItem());
        table->setItem(i,4,new QTableWidgetItem());
        table->setItem(i,5,new QTableWidgetItem());
        table->setItem(i,6,new QTableWidgetItem());
    }

    QObject::connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(cellClicked(int,int)));

    QObject::connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(cellClicked(int)));
    QObject::connect(ui->name,SIGNAL(textChanged(QString)),this,SLOT(textChange()));
    QObject::connect(ui->ip1,SIGNAL(textChanged(QString)),this,SLOT(textChange()));
    QObject::connect(ui->ip2,SIGNAL(textChanged(QString)),this,SLOT(textChange()));
    QObject::connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(textChange()));
    QObject::connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(textChange()));
    QObject::connect(ui->checkBox_3,SIGNAL(stateChanged(int)),this,SLOT(textChange()));
    QObject::connect(ui->info,SIGNAL(textChanged()),this,SLOT(textChange()));

}

void MyJqChildWidget::cellClicked(int row)
{
    cellClicked(row,1);
}

void MyJqChildWidget::cellClicked(int row,int column)
{
    int index = ui->tableWidget->item(row,0)->text().toInt();
    QString name = ui->tableWidget->item(row,1)->text();
    QString ip1 = ui->tableWidget->item(row,2)->text();
    QString ip2 = ui->tableWidget->item(row,3)->text();
    QString type = ui->tableWidget->item(row,4)->text();
    QString local = ui->tableWidget->item(row,5)->text();
    QString info = ui->tableWidget->item(row,6)->text();

    ui->spinBox->setValue(index);
    ui->name->setText(name);
    ui->ip1->setText(ip1);
    ui->ip2->setText(ip2);
    ui->info->setText(info);
    type.contains("服务器") ? ui->checkBox->setChecked(true) : ui->checkBox->setChecked(false);
    type.contains("前置机") ? ui->checkBox_2->setChecked(true) : ui->checkBox_2->setChecked(false);
    type.contains("工作站") ? ui->checkBox_3->setChecked(true) : ui->checkBox_3->setChecked(false);
}

void MyJqChildWidget::textChange()
{
    int index = ui->spinBox->value();
    QString name = ui->name->text();
    QString ip1 = ui->ip1->text();
    QString ip2 = ui->ip2->text();
    QString type = QString();
    ui->checkBox->isChecked() ? type += "服务器" : type;
    ui->checkBox_2->isChecked() ? type += " 前置机" : type;
    ui->checkBox_3->isChecked() ? type += " 工作站" : type;
    QString local = "否";
    QString info = ui->info->toPlainText();

    ui->tableWidget->item(index,1)->setText(name);
    ui->tableWidget->item(index,2)->setText(ip1);
    ui->tableWidget->item(index,3)->setText(ip2);
    ui->tableWidget->item(index,4)->setText(type);
    //ui->tableWidget->item(index,5)->setText(local);
    ui->tableWidget->item(index,6)->setText(info);
}
