#include "addscheduledialog.h"
#include "ui_addscheduledialog.h"

AddScheduleDialog::AddScheduleDialog(QWidget *parent) : QDialog(parent), ui(new Ui::addScheduleDialog)
{
    ui->setupUi(this);
}

AddScheduleDialog::~AddScheduleDialog()
{
    delete ui;
}

void AddScheduleDialog::setEditData(QStringList rowData)
{
    ui->CSNo->setText(rowData.at(0));
    ui->Fund->setValue(rowData.at(1).toInt());
    ui->StartTime->setText(rowData.at(2));
    ui->EndTime->setText(rowData.at(3));
    ui->leadMan->setText(rowData.at(4));

}

void AddScheduleDialog::clearData()
{
    ui->CSNo->clear();
    ui->Fund->clear();
    ui->StartTime->clear();
    ui->EndTime->clear();
    ui->leadMan->clear();
}

void AddScheduleDialog::on_confirm_clicked(bool checked)
{
    QVariantMap scheInfo;

    QString CSNo = ui->CSNo->text();
    QString fund = ui->Fund->text();
    QString startTime = ui->StartTime->text();
    QString endTime = ui->EndTime->text();
    QString leadMan = ui->leadMan->text();

    scheInfo.insert("CSNo", CSNo);
    scheInfo.insert("Fund", fund);
    scheInfo.insert("StartTime", startTime);
    scheInfo.insert("EndTime", endTime);
    scheInfo.insert("leadMan", leadMan);

    emit signalScheInfo(scheInfo);

    clearData();
}

void AddScheduleDialog::on_cancel_clicked(bool checked)
{
    close();
}
