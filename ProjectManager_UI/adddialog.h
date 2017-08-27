#define ADDDIALOG_H

#include <QDialog>
#include <QVariantMap>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

    void setEditData(QStringList rowData);

private:
    void clearData();

    void closeEvent(QCloseEvent *event);

private slots:


signals:

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
