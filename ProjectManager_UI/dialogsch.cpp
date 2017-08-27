#include "dialogsch.h"
#include "ui_dialogsch.h"

DialogSch::DialogSch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSch)
{
    ui->setupUi(this);
}

DialogSch::~DialogSch()
{
    delete ui;
}

void DialogSch::setEditData(QStringList rowData)
{
    ui->CSNo->setText(rowData.at(0));
    ui->fund->setText(rowData.at(1));
    ui->leadMan->setText(rowData.at(2));
    ui->startTime->setText(rowData.at(3));
    ui->endTime->setText(rowData.at(4));

    ui->CSNo->setEnabled(false);
}

void DialogSch::clearData()
{
    ui->CSNo->clear();
    ui->fund->clear();
    ui->leadMan->clear();
    ui->startTime->clear();
    ui->endTime->clear();
}

void DialogSch::on_buttonBox_accepted()
{
    QVariantMap schInfo;

    QString leadMan = ui->leadMan->text();
    QString CSNo = ui->CSNo->text();
    QString fund = ui->fund->text();
    QString startTime = ui->startTime->text();
    QString endTime = ui->endTime->text();

    schInfo.insert("CSNo", CSNo);
    schInfo.insert("fund", fund);
    schInfo.insert("leadMan", leadMan);
    schInfo.insert("startTime", startTime);
    schInfo.insert("endTime", endTime);

    emit signalSchInfo(schInfo);

    clearData(); //清除编辑的数据
    ui->CSNo->setEnabled(true);

}

void DialogSch::on_buttonBox_rejected()
{
    clearData();
    close();
    ui->CSNo->setEnabled(true);
}
