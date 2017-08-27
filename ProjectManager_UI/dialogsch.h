#ifndef DIALOGSCH_H
#define DIALOGSCH_H

#include <QDialog>
#include <QVariantMap>


namespace Ui {
class DialogSch;
}

class DialogSch : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSch(QWidget *parent = 0);
    ~DialogSch();

    void setEditData(QStringList rowData);

private:
    void clearData();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void signalSchInfo(QVariantMap schInfo);



private:
    Ui::DialogSch *ui;
};

#endif // DIALOGSCH_H
