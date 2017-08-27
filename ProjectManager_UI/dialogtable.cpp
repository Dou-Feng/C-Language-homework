#include "dialogtable.h"
#include "ui_dialogtable.h"
#include "QDebug"

DialogTable::DialogTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTable)
{
    ui->setupUi(this);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->title->setText("");
}

DialogTable::~DialogTable()
{
    delete ui;
}

void DialogTable::Data_set(struct data **data)
{
    ui->title->setText(QString::fromLocal8Bit("计划报表"));
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("项目编号")<< QString::fromLocal8Bit("申报项目数") << QString::fromLocal8Bit("支持的项目数")
                                               << QString::fromLocal8Bit("资金")
                                               << QString::fromLocal8Bit("项目的支持率") <<
                                               QString::fromLocal8Bit("验收通过率") <<
                                               QString::fromLocal8Bit("优良率") <<
                                               QString::fromLocal8Bit("合格率")
                                                << QString::fromLocal8Bit("未结题率")
                                               << QString::fromLocal8Bit("参与学生数量"));
    deleteData();
    for (int i = 0; data[i]; i++) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row + 1);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString::fromLocal8Bit(data[i]->scheduleNo));
        ui->tableWidget->setItem(row, 0, item);

        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setText(QString::number(data[i]->registeredProjectNum, 10));
        ui->tableWidget->setItem(row, 1, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString::number(data[i]->supportedProjectNum, 10));
        ui->tableWidget->setItem(row, 2, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setText(QString::number(data[i]->fund, (float)10));
        ui->tableWidget->setItem(row, 3, item3);

        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setText(QString::number(data[i]->supportingRate, (float)10));
        ui->tableWidget->setItem(row, 4, item4);

        QTableWidgetItem *item5 = new QTableWidgetItem;
        item5->setText(QString::number(data[i]->supportingRate, (float)10));
        ui->tableWidget->setItem(row, 5, item5);

        QTableWidgetItem *item6 = new QTableWidgetItem;
        item6->setText(QString::number(data[i]->excellentRate, (float)10));
        ui->tableWidget->setItem(row, 6, item6);

        QTableWidgetItem *item7 = new QTableWidgetItem;
        item7->setText(QString::number(data[i]->qualifiedRate, (float)10));
        ui->tableWidget->setItem(row, 7, item7);

        QTableWidgetItem *item8 = new QTableWidgetItem;
        item8->setText(QString::number(data[i]->unfinishedRate, (float)10));
        ui->tableWidget->setItem(row, 8, item8);

        QTableWidgetItem *item9 = new QTableWidgetItem;
        item9->setText(QString::number(data[i]->studentNum, 10));
        ui->tableWidget->setItem(row, 9, item9);
    }
}

void DialogTable::Student_set(struct student **stu)
{
    ui->title->setText(QString::fromLocal8Bit("计划报表"));
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<
                                               QString::fromLocal8Bit("学号")<<
                                               QString::fromLocal8Bit("姓名") <<
                                               QString::fromLocal8Bit("项目数量")<<
                                               QString::fromLocal8Bit("验收通过率")<<
                                               QString::fromLocal8Bit("验收优良率") <<
                                               QString::fromLocal8Bit("未结题率"));
    deleteData();
    for (int i = 0; stu[i]; i++) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row + 1);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString::fromLocal8Bit(stu[i]->SNo));
        ui->tableWidget->setItem(row, 0, item);

        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setText(QString::fromLocal8Bit(stu[i]->name));
        ui->tableWidget->setItem(row, 1, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString::number(stu[i]->project_number, 10));
        ui->tableWidget->setItem(row, 2, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setText(QString::number(stu[i]->passingRate, (float)10));
        ui->tableWidget->setItem(row, 3, item3);

        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setText(QString::number(stu[i]->excellentAndGoodRate, (float)10));
        ui->tableWidget->setItem(row, 4, item4);

        QTableWidgetItem *item5 = new QTableWidgetItem;
        item5->setText(QString::number(stu[i]->unfinishedRate, (float)10));
        ui->tableWidget->setItem(row, 5, item5);
    }
}

void DialogTable::College_set(struct college **col)
{
    ui->title->setText(QString::fromLocal8Bit("计划报表"));
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<
                                               QString::fromLocal8Bit("学院名称")<<
                                               QString::fromLocal8Bit("项目数量") <<
                                               QString::fromLocal8Bit("验收通过率")<<
                                               QString::fromLocal8Bit("验收优良率")<<
                                               QString::fromLocal8Bit("未结题率"));
    deleteData();
    for (int i = 0; col[i]; i++) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row + 1);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString::fromLocal8Bit(col[i]->collegeName));
        ui->tableWidget->setItem(row, 0, item);

        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setText(QString::number(col[i]->projectNum, 10));
        ui->tableWidget->setItem(row, 1, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString::number(col[i]->passingRate, (float)10));
        ui->tableWidget->setItem(row, 2, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setText(QString::number(col[i]->excellentAndGoodRate, (float)10));
        ui->tableWidget->setItem(row, 3, item3);

        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setText(QString::number(col[i]->unfinishedRate, (float)10));
        ui->tableWidget->setItem(row, 4, item4);
    }
}

void DialogTable::deleteData() {
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

void DialogTable::on_buttonBox_accepted()
{
    deleteData();
    emit clearMenoryOfData();
    close();
}

void DialogTable::on_buttonBox_rejected()
{
    deleteData();
    emit clearMenoryOfData();
    close();
}
