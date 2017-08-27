#ifndef DIALOGPEO_H
#define DIALOGPEO_H

#include <QDialog>

namespace Ui {
class DialogPeo;
}

class DialogPeo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPeo(QWidget *parent = 0);
    ~DialogPeo();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void setData(QStringList info);

signals:
    void signalPeoInfo(QStringList info);

private:
    void clearData();

private:
    Ui::DialogPeo *ui;
};

#endif // DIALOGPEO_H
