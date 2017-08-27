#include "dialogproadd.h"
#include "ui_dialogproadd.h"

DialogProAdd::DialogProAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProAdd)
{
    ui->setupUi(this);
}

DialogProAdd::~DialogProAdd()
{
    delete ui;
}

void DialogProAdd::on_buttonBox_accepted()
{
    QStringList list;
    list << ui->CNo->text() << ui->projectName->text() << ui->fund->text() << ui->peopleNum->text() <<
            ui->startTime->text() << ui->endTime->text() << ui->judgement->currentText() <<
            ui->leadMan->text() << ui->leadPhoneNum->text() << ui->productForm->currentText()
         << ui->productName->text() << ui->isSupport->currentText() << ui->number->text();
    emit signalProInfo(list);
    clearData();
    close();
}

void DialogProAdd::clearData()
{
    ui->CNo->clear();
    ui->projectName->clear();
    ui->fund->clear();
    ui->peopleNum->clear();
    ui->startTime->clear();
    ui->endTime->clear();
    ui->judgement->setCurrentIndex(0);
    ui->leadMan->clear();
    ui->leadPhoneNum->clear();
    ui->productForm->setCurrentIndex(0);
    ui->productName->clear();
    ui->isSupport->setCurrentIndex(0);
    ui->number->setText("待定");
}

void DialogProAdd::on_buttonBox_rejected()
{
    clearData();
    close();
}

void DialogProAdd::setData(QStringList info)
{
    ui->CNo->setText(info.at(0));
    ui->projectName->setText(info.at(1));
    ui->fund->setText(info.at(2));
    ui->peopleNum->setText((info.at(3)));
    ui->startTime->setText(info.at(4));
    ui->endTime->setText(info.at(5));
    for (int i = 1; i < 5; i++) {
    if (ui->judgement->currentText() == info.at(6)) {
        break;
    } else {
        ui->judgement->setCurrentIndex(i);
    }
    }
    ui->leadMan->setText(info.at(7));
    ui->leadPhoneNum->setText(info.at(8));
    for (int i = 1; i < 4; i++) {
    if (ui->productForm->currentText() == info.at(9)) {
        break;
    } else {
        ui->productForm->setCurrentIndex(i);
    }
    }
    ui->productName->setText(info.at(10));
    if (info.at(11) == "Yes")
        ui->isSupport->setCurrentIndex(0);
    else
        ui->isSupport->setCurrentIndex(1);
    ui->number->setText(info.at(12));
}
