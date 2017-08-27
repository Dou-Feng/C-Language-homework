#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogsch.h"
#include "dialogschmodify.h"
#include "dialogproadd.h"
#include "dialogpeo.h"
#include "dialogtableselect.h"
#include "dialogtable.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum OperateType
    {
        Add ,
        Edit
    };


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void refreshUI();


private slots:

    void addSchSql(QVariantMap schInfo);
    void modifySch(QStringList info);
    void editProSql(QStringList proInfo);
    void addProSql(QStringList proInfo);

    void addPeoSql(QStringList peoInfo);
    void editPeoSql(QStringList peoInfo);

    void openTable(QStringList info);

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_modify_clicked();

    void on_delete01_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_find_clicked();

    void on_add_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_tableData_clicked();

    void clearMoney();

signals:
    void signalSchInfo(QStringList info);
    void signalDataInfo(Data **info);
    void signalStuInfo(Stu **info);
    void signalCollegeInfo(Coll **info);

private:
    void initDialog();
    void init();
    void deleteData();
    void fullScheCollection();
    void fullProCollection();
    void fullPeoCollection();

private:
    Ui::MainWindow *ui;
    DialogSch *m_dialogSch;
    DialogProAdd *m_dialogProAdd;
    OperateType m_operateType;
    DialogPeo *m_dialogPeo;
    DialogTableSelect *m_dialogTableSelect;
    DialogTable *m_dialogTable;
    int status;
    struct schedule *head;
    struct project *projectHead;
    struct people *peopleHead;
    struct student *stuCollection[200];
    struct college *collegeCollection[200];
    struct data *dataCollection[200];
    struct schedule *scheCollections[200];
    struct project *proCollections[200];
    struct people *peoCollections[200];
    struct schedule *schList[200];
    char *collection_name[200];
    char *collection_college_name[200];
    DialogSchModify *m_dialogModify;

};

#endif // MAINWINDOW_H
