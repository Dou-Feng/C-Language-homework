#ifndef DIALOGPROADD_H
#define DIALOGPROADD_H

#include <QDialog>

namespace Ui {
class DialogProAdd;
}

class DialogProAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProAdd(QWidget *parent = 0);
    ~DialogProAdd();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();
    void setData(QStringList info);

signals:
    void signalProInfo(QStringList info);

private:
    void clearData();

private:
    Ui::DialogProAdd *ui;
};


#endif // DIALOGPROADD_H
