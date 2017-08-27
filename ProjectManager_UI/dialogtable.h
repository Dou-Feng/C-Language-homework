#ifndef DIALOGTABLE_H
#define DIALOGTABLE_H

#include <QDialog>
#include "studentTable.h"

namespace Ui {
class DialogTable;
}

class DialogTable : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTable(QWidget *parent = 0);
    ~DialogTable();

private slots:
    void Data_set(Data **data);
    void Student_set(Stu **stu);
    void College_set(Coll **col);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void closeTable();
    void clearMenoryOfData();


private:
    void deleteData();

private:
    Ui::DialogTable *ui;
};

#endif // DIALOGTABLE_H
