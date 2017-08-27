#ifndef DIALOGTABLESELECT_H
#define DIALOGTABLESELECT_H

#include <QDialog>

namespace Ui {
class DialogTableSelect;
}

class DialogTableSelect : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTableSelect(QWidget *parent = 0);
    ~DialogTableSelect();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void signalTableInfo(QStringList info);

private:
    void clearData();

private:
    Ui::DialogTableSelect *ui;
};

#endif // DIALOGTABLESELECT_H
