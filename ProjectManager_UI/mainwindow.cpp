#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    head = createSchedule();
    head->projectHead = createProject();
    projectHead = head->projectHead;
    projectHead->peopleHead = createPeople();
    peopleHead = projectHead->peopleHead;
    ui->setupUi(this);
    init();
    initDialog();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::refreshUI()
{
    struct schedule *p = head->next;
    struct project *pPro = projectHead->next;
    struct people *pPeo = peopleHead->next;
    switch (status) {
    case 1:
        if (!head)
            return;
        sortSchedule(head);
        deleteData();
        fullScheCollection();
        for (int i = 0; scheCollections[i]; i++)
            refreshSchList(scheCollections[i]);

        while (p) {
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

            p = p->next;
        }
        break;
    case 2:
        if (!projectHead)
            return;
        sortProject(projectHead);
        fullProCollection();
        deleteData();
        for (int i = 0; proCollections[i]; i++)
            refreshProList(proCollections[i]);

        while (pPro) {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(row + 1);
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(QString(QLatin1String(pPro->CNo)));
            ui->tableWidget->setItem(row, 0, item);


            QTableWidgetItem *item1 = new QTableWidgetItem;
            item1->setText(QString::fromLocal8Bit(pPro->proName));
            ui->tableWidget->setItem(row, 1, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem;
            float numberF = (float)pPro->money;
            item2->setText(QString::number(numberF, (float)10));
            ui->tableWidget->setItem(row, 2, item2);



            QTableWidgetItem *item3 = new QTableWidgetItem;
            item3->setText(QString::number(pPro->member, 10));
            ui->tableWidget->setItem(row, 3, item3);

            QTableWidgetItem *item4 = new QTableWidgetItem;
            item4->setText(QString::fromLocal8Bit(pPro->startTime));
            ui->tableWidget->setItem(row, 4, item4);

            QTableWidgetItem *item5 = new QTableWidgetItem;
            item5->setText(QString::fromLocal8Bit(pPro->finishTime));
            ui->tableWidget->setItem(row, 5, item5);


            QTableWidgetItem *item6 = new QTableWidgetItem;
            item6->setText(QString::fromLocal8Bit(pPro->judgement));
            ui->tableWidget->setItem(row, 6, item6);

            QTableWidgetItem *item7 = new QTableWidgetItem;
            item7->setText(QString::fromLocal8Bit(pPro->leadMan));
            ui->tableWidget->setItem(row, 7, item7);

            QTableWidgetItem *item8 = new QTableWidgetItem;
            item8->setText(QString::fromLocal8Bit(pPro->leadPhoneNum));
            ui->tableWidget->setItem(row, 8, item8);

            QTableWidgetItem *item9 = new QTableWidgetItem;
            item9->setText(QString::fromLocal8Bit(pPro->productForm));
            ui->tableWidget->setItem(row, 9, item9);

            QTableWidgetItem *item10 = new QTableWidgetItem;
            item10->setText(QString::fromLocal8Bit(pPro->productName));
            ui->tableWidget->setItem(row, 10, item10);

            QTableWidgetItem *item11 = new QTableWidgetItem;
            if (pPro->isSupported) {
                item11->setText("Yes");
            } else {
                item11->setText("No");
            }
            ui->tableWidget->setItem(row, 11, item11);
            pPro = pPro->next;
        }
        break;
    case 3:
        if (!peopleHead)
            return;
        sortPeople(peopleHead);
        fullPeoCollection();
        deleteData();
        while (pPeo) {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(row + 1);
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(QString(QLatin1String(pPeo->SNo)));
            ui->tableWidget->setItem(row, 0, item);


            QTableWidgetItem *item1 = new QTableWidgetItem;
            item1->setText(QString::fromLocal8Bit(pPeo->name));
            ui->tableWidget->setItem(row, 1, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem;
            int numberI = pPeo->age;
            item2->setText(QString::number(numberI, 10));
            ui->tableWidget->setItem(row, 2, item2);

            QTableWidgetItem *item3 = new QTableWidgetItem;
            item3->setText(QString::fromLocal8Bit(pPeo->grade));
            ui->tableWidget->setItem(row, 3, item3);

            QTableWidgetItem *item4 = new QTableWidgetItem;
            item4->setText(QString::fromLocal8Bit(pPeo->collegeAndMajor));
            ui->tableWidget->setItem(row, 4, item4);

            QTableWidgetItem *item5 = new QTableWidgetItem;
            item5->setText(QString::fromLocal8Bit(pPeo->classes));
            ui->tableWidget->setItem(row, 5, item5);


            QTableWidgetItem *item6 = new QTableWidgetItem;
            item6->setText(QString::fromLocal8Bit(pPeo->speciality));
            ui->tableWidget->setItem(row, 6, item6);

            QTableWidgetItem *item7 = new QTableWidgetItem;
            item7->setText(QString::fromLocal8Bit(pPeo->undertakeTask));
            ui->tableWidget->setItem(row, 7, item7);

            QTableWidgetItem *item8 = new QTableWidgetItem;
            item8->setText(QString::fromLocal8Bit(pPeo->phoneNum));
            ui->tableWidget->setItem(row, 8, item8);

            QTableWidgetItem *item9 = new QTableWidgetItem;
            int numberI2 = pPeo->age;
            item9->setText(QString::number(numberI2, 10));
            ui->tableWidget->setItem(row, 9, item9);
            pPeo = pPeo->next;
        }
        break;

    }
}




void MainWindow::addSchSql(QVariantMap schInfo)
{
    if (m_operateType == Add) {
        QString qCSNo = schInfo.value("CSNo").toString();
        QByteArray bCSNo = qCSNo.toLocal8Bit();
        char *CSNo = bCSNo.data();
        QString qfund = schInfo.value("fund").toString();
        float fund = qfund.toFloat();
        QString qleadMan = schInfo.value("leadMan").toString();
        QByteArray bleadMan = qleadMan.toLocal8Bit();
        char *leadMan = bleadMan.data();
        QString qstartTime = schInfo.value("startTime").toString();
        QByteArray bstartTime = qstartTime.toLocal8Bit();
        char *startTime = bstartTime.data();
        QString qendTime = schInfo.value("endTime").toString();
        QByteArray bendTime = qendTime.toLocal8Bit();
        char *endTime = bendTime.data();
        //qDebug() << QString::number(fund, (float)10) << qendTime;
        addSchedule(head, CSNo, fund, leadMan, startTime, endTime);
        fullScheCollection();
        refreshUI();

    }
}

void MainWindow::editProSql(QStringList schInfo)
{
    if (m_operateType == Edit) {
        int row = schInfo.at(12).toInt();
        if (row >= 0 && proCollections[row]) {
            struct project *p = proCollections[row];
            QByteArray bCNo = schInfo.at(0).toLocal8Bit();
            char *CNo = bCNo.data();
            QByteArray bprojectName = schInfo.at(1).toLocal8Bit();
            char *projectName = bprojectName.data();
            float fund = schInfo.at(2).toFloat();

            int number =  schInfo.at(3).toInt();

            QByteArray bstartTime = schInfo.at(4).toLocal8Bit();
            char *startTime = bstartTime.data();
            QByteArray bendTime = schInfo.at(5).toLocal8Bit();
            char *endTime = bendTime.data();
            QByteArray bjudgement = schInfo.at(6).toLocal8Bit();
            char *judgement = bjudgement.data();
            QByteArray bleadMan = schInfo.at(7).toLocal8Bit();
            char *leadMan = bleadMan.data();
            QByteArray bLeadManPhoneNum = schInfo.at(8).toLocal8Bit();
            char *leadManphoneNum = bLeadManPhoneNum.data();
            QByteArray bForm = schInfo.at(9).toLocal8Bit();
            char *form = bForm.data();
            QByteArray bproductName = schInfo.at(10).toLocal8Bit();
            char *productname = bproductName.data();
            int isSupport;
            if (schInfo.at(11) == "Yes")
                isSupport = 1;
            else
                isSupport = 0;

            /*修改数据库的数据*/
            strcpy(p->CNo, CNo);

            strcpy(p->proName, projectName);

            p->money = fund;

            p->member = number;

            strcpy(p->startTime, startTime);

            strcpy(p->finishTime, endTime);

            strcpy(p->judgement, judgement);

            strcpy(p->leadMan, leadMan);

            strcpy(p->leadPhoneNum, leadManphoneNum);

            strcpy(p->productForm, form);


            strcpy(p->productName, productname);


            p->isSupported = isSupport;

            fullProCollection();

            refreshUI();
        }
    }
}



void MainWindow::initDialog()
{
    connect(m_dialogProAdd, SIGNAL(signalProInfo(QStringList)), this, SLOT(editProSql(QStringList)));
    connect(m_dialogProAdd, SIGNAL(signalProInfo(QStringList)), this, SLOT(addProSql(QStringList)));
    connect(m_dialogSch , SIGNAL(signalSchInfo(QVariantMap)) , this ,SLOT(addSchSql(QVariantMap)));
    connect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogModify, SLOT(setData(QStringList)));
    connect(m_dialogModify, SIGNAL(signalAfterModify(QStringList)), this, SLOT(modifySch(QStringList)));
    connect(m_dialogPeo, SIGNAL(signalPeoInfo(QStringList)), this, SLOT(editPeoSql(QStringList)));
    connect(m_dialogPeo, SIGNAL(signalPeoInfo(QStringList)), this, SLOT(addPeoSql(QStringList)));
    connect(m_dialogTableSelect, SIGNAL(signalTableInfo(QStringList)), this, SLOT(openTable(QStringList)));
    connect(this, SIGNAL(signalDataInfo(Data**)), m_dialogTable, SLOT(Data_set(Data**)));
    connect(this, SIGNAL(signalStuInfo(Stu**)), m_dialogTable, SLOT(Student_set(Stu**)));
    connect(this, SIGNAL(signalCollegeInfo(Coll**)), m_dialogTable, SLOT(College_set(Coll**)));
    connect(m_dialogTable, SIGNAL(clearMenoryOfData()), this, SLOT(clearMoney()));
}

void MainWindow::init()
{
    status = 1;
    m_dialogProAdd = new DialogProAdd;
    m_dialogModify = new DialogSchModify;
    m_dialogSch = new DialogSch;
    m_dialogPeo = new DialogPeo;
    m_dialogTableSelect = new DialogTableSelect;
    m_dialogTable = new DialogTable;
    memset(collection_name, 0, sizeof(char *) * 200);
    memset(collection_college_name, 0, sizeof(char *) * 200);
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit->setPlaceholderText("在此输入年度编号");
    ui->lineEdit_2->setPlaceholderText("不用输入");
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"年度编号" << "投入资金（万元）"<< "负责"<< "申报项目"
                                               <<"实际支持项目" <<"结题项目" <<"计划时间" <<"计划结束时间");
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

void MainWindow::deleteData()
{
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

void MainWindow::fullScheCollection()
{
    int i;
    struct schedule *p1 = head->next;
    for (i = 0; p1; p1 = p1->next, i++) {
        scheCollections[i] = p1;
    }
    scheCollections[i] = NULL;
}

void MainWindow::fullProCollection()
{
    int i;
    struct project *p1 = projectHead->next;
    for (i = 0; p1; p1 = p1->next, i++) {
        proCollections[i] = p1;
    }
    proCollections[i] = NULL;
}

void MainWindow::fullPeoCollection()
{
    int i;
    struct people *p1 = peopleHead->next;
    for (i = 0; p1; p1 = p1->next, i++) {
        peoCollections[i] = p1;
    }
    peoCollections[i] = NULL;

}





void MainWindow::on_comboBox_currentIndexChanged(int index)
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

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
        refreshUI();
    }
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
        refreshUI();
    }
}

void MainWindow::addProSql(QStringList proInfo)
{
    if (m_operateType == Add) {
        QByteArray bCNo = proInfo.at(0).toLocal8Bit();
        char *CNo = bCNo.data();
        QByteArray bprojectName = proInfo.at(1).toLocal8Bit();
        char *projectName = bprojectName.data();
        float fund = proInfo.at(2).toFloat();
        int number = proInfo.at(3).toInt();
        QByteArray bstartTime = proInfo.at(4).toLocal8Bit();
        char *startTime = bstartTime.data();
        QByteArray bendTime = proInfo.at(5).toLocal8Bit();
        char *endTime = bendTime.data();
        QByteArray bjudgement = proInfo.at(6).toLocal8Bit();
        char *judgement = bjudgement.data();
        QByteArray bleadMan = proInfo.at(7).toLocal8Bit();
        char *leadMan = bleadMan.data();
        QByteArray BleadPhoneNum = proInfo.at(8).toLocal8Bit();
        char *leadPhoneNum = BleadPhoneNum.data();
        QByteArray bproductForm = proInfo.at(9).toLocal8Bit();
        char *productForm = bproductForm.data();
        QByteArray bProductName = proInfo.at(10).toLocal8Bit();
        char *productName = bProductName.data();
        int isSupport;
        if (proInfo.at(11) == "Yes")
            isSupport = 1;
        else
            isSupport = 0;
        addProject(projectHead, CNo, projectName, fund, number, startTime, endTime, judgement, leadMan,
                   leadPhoneNum, productForm, productName, isSupport);
        fullProCollection();
        refreshUI();
        for (int i = 0; scheCollections[i]; i++)
            refreshSchList(scheCollections[i]);
    }
}

void MainWindow::addPeoSql(QStringList peoInfo)
{
    if (m_operateType == Add) {
        QByteArray bSNo = peoInfo.at(0).toLocal8Bit();
        char *SNo = bSNo.data();
        QByteArray bname = peoInfo.at(1).toLocal8Bit();
        char *name = bname.data();
        int age = peoInfo.at(2).toInt();
        QByteArray bgrade = peoInfo.at(3).toLocal8Bit();
        char *grade = bgrade.data();
        QByteArray bcollege = peoInfo.at(4).toLocal8Bit();
        char *college = bcollege.data();
        QByteArray bclasses = peoInfo.at(5).toLocal8Bit();
        char *classes = bclasses.data();
        QByteArray bspecility = peoInfo.at(6).toLocal8Bit();
        char *specility = bspecility.data();
        QByteArray Bundertake = peoInfo.at(7).toLocal8Bit();
        char *undertake = Bundertake.data();
        QByteArray bphone = peoInfo.at(8).toLocal8Bit();
        char *phone = bphone.data();
        int rank = peoInfo.at(9).toInt();
        addPeople(peopleHead, SNo, name, age, grade, college, classes, specility, undertake, phone, rank);
        fullPeoCollection();
        refreshUI();
        for (int i = 0; proCollections[i]; i++)
            refreshProList(proCollections[i]);
    }
}

void MainWindow::editPeoSql(QStringList peoInfo)
{
    if (m_operateType == Edit) {
        int row = peoInfo.at(10).toInt();
        if (row >=0 && peoCollections[row]) {
            struct people *p = peoCollections[row];
            QByteArray bSNo = peoInfo.at(0).toLocal8Bit();
            char *SNo = bSNo.data();
            QByteArray bname = peoInfo.at(1).toLocal8Bit();
            char *name = bname.data();
            int age = peoInfo.at(2).toInt();
            QByteArray bgrade = peoInfo.at(3).toLocal8Bit();
            char *grade = bgrade.data();
            QByteArray bcollege = peoInfo.at(4).toLocal8Bit();
            char *college = bcollege.data();
            QByteArray bclasses = peoInfo.at(5).toLocal8Bit();
            char *classes = bclasses.data();
            QByteArray bspecility = peoInfo.at(6).toLocal8Bit();
            char *speciality = bspecility.data();
            QByteArray Bundertake = peoInfo.at(7).toLocal8Bit();
            char *undertake = Bundertake.data();
            QByteArray bphone = peoInfo.at(8).toLocal8Bit();
            char *phone = bphone.data();
            int rank = peoInfo.at(9).toInt();


            //修改链表数据
            strcpy(p->SNo, SNo);
            strcpy(p->name, name);
            p->age = age;
            strcpy(p->grade, grade);
            strcpy(p->collegeAndMajor, college);
            strcpy(p->classes, classes);
            strcpy(p->speciality, speciality);
            strcpy(p->undertakeTask, undertake);
            strcpy(p->phoneNum, phone);
            p->rank = rank;
            refreshUI();
        }
    }
}

void MainWindow::openTable(QStringList info)
{
    char *startTime, *endTime;
    QByteArray bstartTime;
    QByteArray bendTime;
    QByteArray bstr;
    bstartTime = info.at(1).toLocal8Bit();
    startTime = bstartTime.data();
    bendTime = info.at(2).toLocal8Bit();
    endTime = bendTime.data();
    switch (info.at(0).toInt()) {
    case 0:
        getInTimeSch(schList, head, startTime, endTime);
        fullDataCollection(dataCollection, schList);
        switch (info.at(3).toInt()) {
        case 0:
            sortDataByregisteredProjectNum(dataCollection, schList);
            break;
        case 1:
            sortDataBySupportedNum(dataCollection, schList);
            break;
        case 2:
            sortDataByFund(dataCollection, schList);
            break;
        case 3:
            sortDataBySupportingRate(dataCollection, schList);
            break;
        case 4:
            sortDataByPassingRate(dataCollection, schList);
            break;
        }
        emit signalDataInfo(dataCollection);
        break;
    case 1:
        getAllName(collection_name, head, startTime, endTime);
        getStudentCollection(stuCollection, collection_name, head, startTime, endTime);
        switch(info.at(4).toInt()) {
        case 0:
            sortStudentBySNo(stuCollection);
            break;
        case 1:
            sortStudentByName(stuCollection);
            break;
        case 2:
            sortStudentByProjectNum(stuCollection);
            break;
        case 3:
            sortStudentByPassingRate(stuCollection);
            break;
        }
        emit signalStuInfo(stuCollection);
        break;
    case 2:
        getCollegeName(collection_college_name, head, startTime, endTime);
        getCollegeCollection(collegeCollection, collection_college_name, head, startTime, endTime);
        switch (info.at(5).toInt()) {
        case 0:
            sortCollegedentByProjectNum(collegeCollection);
            break;
        case 1:
            sortCollegeByPassingRate(collegeCollection);
            break;
        case 2:
            sortCollegeByexcellentRate(collegeCollection);
            break;
        case 3:
            sortCollegeByunfinishedRate(collegeCollection);
            break;
        }
        emit signalCollegeInfo(collegeCollection);
        break;
    }

    m_dialogTable->activateWindow();
    m_dialogTable->setWindowTitle(tr("报表打印"));
    m_dialogTable->exec();

}

void MainWindow::on_modify_clicked()
{
    m_operateType = Edit;
    int row = ui->tableWidget->currentRow();
    QStringList list;
    QString CSNo;
    QString fund;
    QString leadMan;
    QString proNum;
    QString realPro;
    QString finishNum;
    QString startTime;
    QString endTime;
    QString rowS;
    QString CNo;
    QString projectName;
    QString member;
    QString judgement;
    QString leadManPhoneNum;
    QString form;
    QString productName;
    QString isSupport;
    if (row >= 0 && ui->tableWidget->rowCount() > 0) {
        switch (status) {
        case 1:
            CSNo = ui->tableWidget->item(row, 0)->text();
            fund = ui->tableWidget->item(row, 1)->text();
            leadMan = ui->tableWidget->item(row, 2)->text();
            proNum = ui->tableWidget->item(row, 3)->text();
            realPro = ui->tableWidget->item(row, 4)->text();
            finishNum = ui->tableWidget->item(row, 5)->text();
            startTime = ui->tableWidget->item(row, 6)->text();
            endTime = ui->tableWidget->item(row, 7)->text();
            rowS = QString::number(ui->tableWidget->currentRow(), 10);
            list << CSNo << fund << leadMan << proNum << realPro << finishNum<< startTime << endTime << rowS;

            emit signalSchInfo(list);
            m_dialogModify->activateWindow();
            m_dialogModify->setWindowTitle(tr("修改: 计划信息"));
            m_dialogModify->exec();
            break;
        case 2:
            CNo = ui->tableWidget->item(row, 0)->text();
            projectName = ui->tableWidget->item(row, 1)->text();
            fund = ui->tableWidget->item(row, 2)->text();
            member = ui->tableWidget->item(row, 3)->text();
            startTime = ui->tableWidget->item(row, 4)->text();
            endTime = ui->tableWidget->item(row, 5)->text();
            judgement = ui->tableWidget->item(row, 6)->text();
            leadMan = ui->tableWidget->item(row, 7)->text();
            leadManPhoneNum = ui->tableWidget->item(row, 8)->text();
            form = ui->tableWidget->item(row, 9)->text();
            productName = ui->tableWidget->item(row, 10)->text();
            isSupport = ui->tableWidget->item(row, 11)->text();
            rowS = QString::number(ui->tableWidget->currentRow(), 10);
            list << CNo << projectName << fund << member << startTime << endTime <<
                    judgement << leadMan << leadManPhoneNum << form << productName <<
                    isSupport << rowS;
            qDebug() << row;

            emit signalSchInfo(list);
            m_dialogProAdd->activateWindow();
            m_dialogProAdd->setWindowTitle("修改: 项目信息");
            m_dialogProAdd->exec();
            break;
        case 3:
            CNo = ui->tableWidget->item(row, 0)->text();
            projectName = ui->tableWidget->item(row, 1)->text();
            fund = ui->tableWidget->item(row, 2)->text();
            member = ui->tableWidget->item(row, 3)->text();
            startTime = ui->tableWidget->item(row, 4)->text();
            endTime = ui->tableWidget->item(row, 5)->text();
            judgement = ui->tableWidget->item(row, 6)->text();
            leadMan = ui->tableWidget->item(row, 7)->text();
            leadManPhoneNum = ui->tableWidget->item(row, 8)->text();
            form = ui->tableWidget->item(row, 9)->text();
            rowS = QString::number(ui->tableWidget->currentRow(), 10);
            m_dialogPeo->activateWindow();
            list << CNo << projectName << fund << member << startTime << endTime <<
                    judgement << leadMan << leadManPhoneNum << form << rowS;
            qDebug() << row;
            emit signalSchInfo(list);
            m_dialogPeo->activateWindow();
            m_dialogPeo->setWindowTitle("修改: 成员信息");
            m_dialogPeo->exec();
            break;
        }

    } else {
        return ;
    }
}

void MainWindow::modifySch(QStringList info)
{
    QByteArray bCSNo = info.at(0).toLocal8Bit();
    char *CSNo = bCSNo.data();

    float fund = info.at(1).toFloat();

    QByteArray bLeadMan = info.at(2).toLocal8Bit();
    char *leadMan = bLeadMan.data();

    int proNum = info.at(3).toInt();

    int realPro = info.at(4).toInt();

    long finishNum = info.at(5).toLong();

    QByteArray bStartTime = info.at(6).toLocal8Bit();
    char *startTime = bStartTime.data();
    QByteArray bEndTIme = info.at(7).toLocal8Bit();
    char *endTime = bEndTIme.data();

    int row = info.at(8).toInt();
    fullScheCollection();
    if (scheCollections[row]) {
        struct schedule *p = scheCollections[row];

        strcpy(p->CSNo, CSNo);

        p->fund = fund;
        strcpy(p->leadMan, leadMan);


        p->projectNum = proNum;

        p->realSupProNum = realPro;

        p->finishProNum = finishNum;

        strcpy(p->startTime, startTime);

        strcpy(p->finishTime, endTime);
    }

    refreshUI();
}


void MainWindow::on_delete01_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row >= 0) {
        switch (status) {
        case 1:
            deleteSchedule(head, row);
            fullScheCollection();
            break;
        case 2:
            deleteProject(projectHead, row);
            fullPeoCollection();
            break;
        case 3:
            deletePeople(peopleHead, row);
            break;
        }
        refreshUI();
    }

}


void MainWindow::on_pushButton_clicked()
{
    refreshUI();
}

void MainWindow::on_pushButton_2_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0)
        return;
    switch (status) {
    qDebug() << row;
    case 1:
        status++;
        ui->comboBox->hide();
        ui->comboBox_3->hide();
        ui->comboBox_2->show();
        fullScheCollection();
        row = ui->tableWidget->currentRow();
        projectHead = scheCollections[row]->projectHead;
        ui->tableWidget->setColumnCount(12);
        ui->tableWidget->setRowCount(0);
        disconnect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogPeo, SLOT(setData(QStringList)));
        disconnect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogModify, SLOT(setData(QStringList)));
        connect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogProAdd, SLOT(setData(QStringList)));
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "项目编号" << "项目名称"<< "经费"
                                                   << "成员" << "立项时间" <<"结题时间" <<"完成评价" <<"负责"
                                                   <<"责任电话"
                                                   << "成果形式" << "成果名称" << "是否支持");
        ui->comboBox_2->setCurrentIndex(0);
        ui->lineEdit->setPlaceholderText("输入项目名称");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        refreshUI();
        break;
    case 2:
        status++;
        ui->comboBox->hide();
        ui->comboBox_2->hide();
        ui->comboBox_3->show();
        fullProCollection();
        row = ui->tableWidget->currentRow();
        peopleHead = proCollections[row]->peopleHead;
        ui->tableWidget->setColumnCount(10);
        ui->tableWidget->setRowCount(0);
        connect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogPeo, SLOT(setData(QStringList)));
        disconnect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogModify, SLOT(setData(QStringList)));
        disconnect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogProAdd, SLOT(setData(QStringList)));
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名"<< "年龄"
                                                   << "类别" << "学院" <<"班级" <<"特长" <<"承担任务"
                                                   <<"联系电话" << "项目成员排名" );
        ui->comboBox_3->setCurrentIndex(0);
        ui->lineEdit->setPlaceholderText("在此输入学生姓名");
        ui->lineEdit_2->setPlaceholderText("不用输入");

        refreshUI();
        break;
    default:
        break;

    }
    qDebug() << QString::number(row, 10);
    if (status >= 3)
        status = 3;
}

void MainWindow::on_pushButton_3_clicked()
{
    switch (status) {
    case 2:
        status--;
        ui->comboBox_2->hide();
        ui->comboBox_3->hide();
        ui->comboBox->show();
        ui->tableWidget->setColumnCount(8);
        ui->tableWidget->setRowCount(0);
        connect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogModify, SLOT(setData(QStringList)));
        disconnect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogProAdd, SLOT(setData(QStringList)));
        disconnect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogPeo, SLOT(setData(QStringList)));
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"年度编号" << "投入资金（万元）"<< "负责"<< "申报项目"
                                                   <<"实际支持项目" <<"结题项目" <<"计划时间" <<"计划结束时间");
        ui->comboBox->setCurrentIndex(0);
        ui->lineEdit->setPlaceholderText("在此输入年度编号");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        refreshUI();
        break;
    case 3:
        status--;
        ui->comboBox->hide();
        ui->comboBox_3->hide();
        ui->comboBox_2->show();
        ui->tableWidget->setColumnCount(12);
        ui->tableWidget->setRowCount(0);
        disconnect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogModify, SLOT(setData(QStringList)));
        connect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogProAdd, SLOT(setData(QStringList)));
        disconnect(this, SIGNAL(signalSchInfo(QStringList)), m_dialogPeo, SLOT(setData(QStringList)));
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "项目编号" << "项目名称"<< "经费"
                                                   << "成员" << "立项时间" <<"结题时间" <<"完成评价" <<"负责"
                                                   <<"责任电话"
                                                   << "成果形式" << "成果名称" << "是否支持");
        ui->comboBox_2->setCurrentIndex(0);
        ui->lineEdit->setPlaceholderText("输入项目名称");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        refreshUI();
        break;
    default:
        break;

    }
    if (status <= 1)
        status = 1;
}



void MainWindow::on_find_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        return ;
    }

    int rowCount = ui->tableWidget->rowCount();

    for (int row = 0; row < rowCount; row++) {
        const QString text1 = ui->lineEdit->text();
        const QString text2 = ui->lineEdit_2->text();
        float min_f;
        float max_f;
        float now_f;
        int min_i;
        int max_i;
        int now_i;
        QString CSNo;
        QByteArray bCSNo;
        QString projectStr;
        char *temp_CSNO;
        switch (status) {
        case 1:
            switch (ui->comboBox->currentIndex()) {
            case 0:
                CSNo = ui->tableWidget->item(row, 0)->text();
                if (CSNo.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                bCSNo = CSNo.toLocal8Bit();
                temp_CSNO = bCSNo.data();
                break;
            case 1:
                min_f = text1.toFloat();
                max_f = text2.toFloat();
                now_f = ui->tableWidget->item(row, 1)->text().toFloat();
                if (now_f >= min_f && now_f <= max_f) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            case 2:
                min_i = text1.toInt();
                max_i = text2.toInt();
                now_i = ui->tableWidget->item(row, 4)->text().toInt();
                if (now_i >= min_i && now_i <= max_i) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            default:
                break;
            }
            break;
        case 2:
            switch (ui->comboBox_2->currentIndex()) {
            case 0:
                projectStr = ui->tableWidget->item(row, 1)->text();
                if (projectStr.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            case 1:
                min_f = text1.toFloat();
                max_f = text2.toFloat();
                now_f = ui->tableWidget->item(row, 2)->text().toFloat();
                if (now_f >= min_f && now_f <= max_f) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            case 2:
                projectStr = ui->tableWidget->item(row, 6)->text();
                if (projectStr.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            case 3:
                projectStr = ui->tableWidget->item(row, 9)->text();
                if (projectStr.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            case 4:
                projectStr = ui->tableWidget->item(row, 10)->text();
                if (projectStr.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            }
            break;
        case 3:
            switch (ui->comboBox_3->currentIndex()) {
            case 0:
                projectStr = ui->tableWidget->item(row, 1)->text();
                if (projectStr.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            case 1:
                projectStr = ui->tableWidget->item(row, 4)->text();
                if (projectStr.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            case 2:
                projectStr = ui->tableWidget->item(row, 6)->text();
                if (projectStr.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            case 3:
                projectStr = ui->tableWidget->item(row, 7)->text();
                if (projectStr.contains(text1)) {
                    ui->tableWidget->showRow(row);
                } else {
                    ui->tableWidget->hideRow(row);
                }
                break;
            }
            break;
        }

    }
}

void MainWindow::on_add_clicked()
{
    m_operateType = Add;
    switch (status) {
    case 1:
        m_dialogSch->activateWindow();
        m_dialogSch->setWindowTitle(tr("添加: 计划信息"));
        m_dialogSch->exec();
        break;
    case 2:
        m_dialogProAdd->activateWindow();
        m_dialogProAdd->setWindowTitle("添加: project");
        m_dialogProAdd->exec();
        break;
    case 3:
        m_dialogPeo->activateWindow();
        m_dialogPeo->setWindowTitle("添加: people");
        m_dialogPeo->exec();
        break;
    default:
        break;
    }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->lineEdit->setPlaceholderText("在此输入年度编号");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        break;
    case 1:
        ui->lineEdit->setPlaceholderText("MIN");
        ui->lineEdit_2->setPlaceholderText("MAX");
        break;
    case 2:
        ui->lineEdit->setPlaceholderText("输入评价");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        break;
    case 3:
        ui->lineEdit->setPlaceholderText("软件,论文,作品,其他");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        break;
    case 4:
        ui->lineEdit->setPlaceholderText("在此输入成果名称");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        break;
    }
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->lineEdit->setPlaceholderText("在此输入学生姓名");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        break;
    case 1:
        ui->lineEdit->setPlaceholderText("在此输入院系专业");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        break;
    case 2:
        ui->lineEdit->setPlaceholderText("在此输入特长");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        break;
    case 3:
        ui->lineEdit->setPlaceholderText("在此输入承担任务");
        ui->lineEdit_2->setPlaceholderText("不用输入");
        break;

    }
}

void MainWindow::on_tableData_clicked()
{

    m_dialogTableSelect->activateWindow();
    m_dialogTableSelect->setWindowTitle(tr("报表查询"));
    m_dialogTableSelect->exec();
}

void MainWindow::clearMoney()
{

}

