#include "dialogfindsch.h"
#include "ui_dialogfindsch.h"
#include "QDebug"

DialogFindSch::DialogFindSch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFindSch)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("在此输入年度编号");
    ui->lineEdit_2->setPlaceholderText("不用输入");
    init();
}

DialogFindSch::~DialogFindSch()
{
    deleteData();
    delete ui;
}

void DialogFindSch::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
        case 0:
            ui->lineEdit->setPlaceholderText("在此输入年度编号");
            ui->lineEdit_2->setPlaceholderText("不用输入");
            break;
        case 1:
        case 2:
            ui->lineEdit->setPlaceholderText("MIN");
            ui->lineEdit_2->setPlaceholderText("MAX");
            break;
        default:
            break;
    }
}

void DialogFindSch::on_find_clicked(bool checked)
{
    int way = ui->comboBox->currentIndex();
    QString text1 = ui->lineEdit->text();
    float min_f, max_f;
    int min_i, max_i;
    char *temp_CSNo;
    QByteArray bCSNo;
    switch (way) {
    case 0:
        bCSNo = text1.toLocal8Bit();
        temp_CSNo = (char *) malloc(sizeof(char) * 20);
        temp_CSNo = bCSNo.data();
        if (head_local) {
            findSchCollectionByCSNo(scheCollection, head_local, temp_CSNo);
        }
        break;
    case 1:
        min_f = ui->lineEdit->text().toFloat();
        max_f = ui->lineEdit_2->text().toFloat();
        if (head_local) {
            findSchCollectionByFundMax(scheCollection, head_local, max_f, min_f);
        }
        break;
    case 2:
        min_i = ui->lineEdit->text().toInt();
        max_i = ui->lineEdit_2->text().toInt();
        if  (head_local) {
            findSchCollectionBySupMax(scheCollection, head_local, max_i, min_i);
        }
        break;
    }
    refresh();

}

void DialogFindSch::getHeadNode(schedule *head)
{
    head_local = head;
    QString temp = QString(head_local->next->CSNo);
    qDebug() <<temp;
}

void DialogFindSch::on_cancel_clicked()
{

    deleteData();
    close();
}

void DialogFindSch::on_modify_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row >= 0 || ui->tableWidget->rowCount() > 0) {
    QStringList list;
    QString CSNo = ui->tableWidget->item(row, 0)->text();
    QString fund = ui->tableWidget->item(row, 1)->text();
    QString leadMan = ui->tableWidget->item(row, 2)->text();
    QString proNum = ui->tableWidget->item(row, 3)->text();
    QString realPro = ui->tableWidget->item(row, 4)->text();
    QString finishNum = ui->tableWidget->item(row, 5)->text();
    QString startTime = ui->tableWidget->item(row, 6)->text();
    QString endTime = ui->tableWidget->item(row, 7)->text();
    list << CSNo << fund << leadMan << proNum << realPro << finishNum << startTime << endTime;
    connect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogModify, SLOT(setData(QStringList)));
    connect(m_dialogModify, SIGNAL(signalAfterModify(QStringList)), this, SLOT(modifySch(QStringList)));
    emit signalSchInfo(list);
    m_dialogModify->activateWindow();
    m_dialogModify->setWindowTitle(tr("修改: 计划信息"));
    m_dialogModify->exec();

    }
}

void DialogFindSch::modifySch(QStringList info)
{
    QByteArray bCSNo = info.at(0).toLocal8Bit();
    char *CSNo = bCSNo.data();

    float fund = info.at(1).toFloat();

    QByteArray bLeadMan = info.at(2).toLocal8Bit();
    char *leadMan = bLeadMan.data();

    int proNum = info.at(3).toInt();

    int realPro = info.at(4).toInt();

    int finishNum = info.at(5).toInt();

    QByteArray bStartTime = info.at(6).toLocal8Bit();
    char *startTime = bStartTime.data();
    QByteArray bEndTIme = info.at(7).toLocal8Bit();
    char *endTime = bEndTIme.data();
    int row = ui->tableWidget->currentRow();

    struct schedule *p = scheCollection[row];

    strcpy(p->CSNo, CSNo);

    p->fund = fund;
    strcpy(p->leadMan, leadMan);


    p->projectNum = proNum;

    p->realSupProNum = realPro;

    p->finishProNum = finishNum;

    strcpy(p->startTime, startTime);

    strcpy(p->finishTime, endTime);

    refresh();
}

void DialogFindSch::init()
{
    m_dialogModify = new DialogSchModify;
    //memset(scheCollection, 0, sizeof(struct schedule*) * 200);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"年度编号" << "投入资金（万元）"<< "负责"<< "申报项目"
                                               <<"实际支持项目" <<"结题项目" <<"计划结束时间" <<"计划结束时间");
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

void DialogFindSch::refresh()
{
    deleteData();

    for (int i = 0; scheCollection[i]; i++) {
        struct schedule *p = scheCollection[i];
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row + 1);
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QLatin1String(p->CSNo)));
        ui->tableWidget->setItem(row, 0, item);

        QTableWidgetItem *item1 = new QTableWidgetItem;
        float numberF = (float)p->fund;
        item1->setText(QString::number(numberF, (float)10));
        ui->tableWidget->setItem(row, 1, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString::fromLocal8Bit(p->leadMan));
        ui->tableWidget->setItem(row, 2, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setText(QString::number(p->projectNum, 10));
        ui->tableWidget->setItem(row, 3, item3);

        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setText(QString::number(p->realSupProNum, 10));
        ui->tableWidget->setItem(row, 4, item4);

        QTableWidgetItem *item5 = new QTableWidgetItem;
        item5->setText(QString::number(p->finishProNum, 10));
        ui->tableWidget->setItem(row, 5, item5);

        QTableWidgetItem *item6 = new QTableWidgetItem;
        item6->setText(QString(QLatin1String(p->startTime)));
        ui->tableWidget->setItem(row, 6, item6);

        QTableWidgetItem *item7 = new QTableWidgetItem;
        item7->setText(QString(QLatin1String(p->finishTime)));
        ui->tableWidget->setItem(row, 7, item7);
    }
}

void DialogFindSch::deleteData()
{
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}


