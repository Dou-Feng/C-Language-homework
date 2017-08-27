#include "dialogpeo.h"
#include "ui_dialogpeo.h"

DialogPeo::DialogPeo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPeo)
{
    ui->setupUi(this);
    ui->number->setText("待定");
}

DialogPeo::~DialogPeo()
{
    delete ui;
}

void DialogPeo::on_buttonBox_accepted()
{
    QStringList list;
    list << ui->SNo->text() <<ui->name->text()<<ui->age->text()<<ui->grade->text()<<ui->college->text()
         <<ui->classes->text()<<ui->specility->text()
         << ui->undertake->text() << ui->phone->text() << ui->rank->text() <<ui->number->text();
    emit signalPeoInfo(list);
    clearData();
    close();
}

void DialogPeo::on_buttonBox_rejected()
{
    clearData();
    close();
}

void DialogPeo::setData(QStringList info)
{
    ui->SNo->setText(info.at(0));
    ui->name->setText(info.at(1));
    ui->age->setText(info.at(2));
    ui->grade->setText(info.at(3));
    ui->college->setText(info.at(4));
    ui->classes->setText(info.at(5));
    ui->specility->setText(info.at(6));
    ui->undertake->setText(info.at(7));
    ui->phone->setText(info.at(8));
    ui->rank->setText(info.at(9));
    ui->number->setText(info.at(10));
}

void DialogPeo::clearData()
{
    ui->SNo->clear();
    ui->name->clear();
    ui->age->clear();
    ui->grade->clear();
    ui->college->clear();
    ui->classes->clear();
    ui->specility->clear();
    ui->undertake->clear();
    ui->phone->clear();
    ui->rank->clear();
    ui->number->setText("待定");
}
