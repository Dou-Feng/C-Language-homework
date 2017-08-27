#include "dialogtableselect.h"
#include "ui_dialogtableselect.h"

DialogTableSelect::DialogTableSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTableSelect)
{
    ui->setupUi(this);
    ui->student->hide();
    ui->college->hide();
    ui->startTime->setPlaceholderText("20160101(year/month/day)");
    ui->endTime->setPlaceholderText("20170101(year/month/day)");
}

DialogTableSelect::~DialogTableSelect()
{
    delete ui;
}

void DialogTableSelect::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->student->hide();
        ui->college->hide();
        ui->total->show();
        break;
    case 1:
        ui->college->hide();
        ui->total->hide();
        ui->student->show();
        break;
    case 2:
        ui->total->hide();
        ui->student->hide();
        ui->college->show();
        break;
    }
}

void DialogTableSelect::on_buttonBox_accepted()
{
    QStringList info;
    if (ui->startTime->text().isEmpty())
        ui->startTime->setText("0");
    if (ui->endTime->text().isEmpty())
        ui->endTime->setText("99999999");
    info << QString::number(ui->comboBox->currentIndex(), 10) << ui->startTime->text() << ui->endTime->text()
         << QString::number(ui->total->currentIndex(), 10) << QString::number(ui->student->currentIndex(), 10) <<
            QString::number(ui->college->currentIndex(), 10);
    emit signalTableInfo(info);
    clearData();
    close();
}

void DialogTableSelect::clearData()
{
    ui->comboBox->setCurrentIndex(0);
    ui->startTime->clear();
    ui->endTime->clear();
    ui->total->setCurrentIndex(0);
    ui->student->setCurrentIndex(0);
    ui->college->setCurrentIndex(0);
}

void DialogTableSelect::on_buttonBox_rejected()
{
    clearData();
    close();
}
