#include "dialogschmodify.h"
#include "ui_dialogschmodify.h"

DialogSchModify::DialogSchModify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSchModify)
{
    ui->setupUi(this);

}

DialogSchModify::~DialogSchModify()
{
    delete ui;
}

void DialogSchModify::on_buttonBox_accepted()
{
    QStringList info;
    QString CSNo = ui->CSNo->text();
    QString fund = ui->fund->text();
    QString leadMan = ui->leadMan->text();
    QString proNum = ui->proNum->text();
    QString realPro = ui->realPro->text();
    QString finishNum = ui->finishNum->text();
    QString startTime = ui->startTime->text();
    QString endTime = ui->endTime->text();
    QString row = ui->number->text();
    info << CSNo << fund << leadMan << proNum << realPro << finishNum << startTime << endTime << row;

    emit signalAfterModify(info);
    ui->CSNo->clear();
    ui->fund->clear();
    ui->leadMan->clear();
    ui->proNum->clear();
    ui->realPro->clear();
    ui->finishNum->clear();
    ui->startTime->clear();
    ui->endTime->clear();
    close();

}

void DialogSchModify::setData(QStringList info)
{
    ui->CSNo->setText(info.at(0));
    ui->fund->setText(info.at(1));
    ui->leadMan->setText(info.at(2));
    ui->proNum->setText(info.at(3));
    ui->realPro->setText(info.at(4));
    ui->finishNum->setText(info.at(5));
    ui->startTime->setText(info.at(6));
    ui->endTime->setText(info.at(7));
    ui->number->setText(info.at(8));
}

void DialogSchModify::on_buttonBox_rejected()
{
    ui->CSNo->clear();
    ui->fund->clear();
    ui->leadMan->clear();
    ui->proNum->clear();
    ui->realPro->clear();
    ui->finishNum->clear();
    ui->startTime->clear();
    ui->endTime->clear();
    close();
}
