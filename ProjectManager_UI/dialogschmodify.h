#ifndef DIALOGSCHMODIFY_H
#define DIALOGSCHMODIFY_H

#include <QDialog>
#include <QVariantMap>

namespace Ui {
class DialogSchModify;
}

class DialogSchModify : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSchModify(QWidget *parent = 0);
    ~DialogSchModify();

private slots:
    void on_buttonBox_accepted();

    void setData(QStringList info);

    void on_buttonBox_rejected();

signals:
    void signalAfterModify(QStringList info);


private:
    Ui::DialogSchModify *ui;
};

#endif // DIALOGSCHMODIFY_H
