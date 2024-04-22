#ifndef INCIDENT2_H
#define INCIDENT2_H

#include <QDialog>
#include <QSizeGrip>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class incident2;
}

class incident2 : public QDialog
{
    Q_OBJECT

public:
    explicit incident2(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~incident2();

private slots:
    void on_btnBack_clicked();

private:
    Ui::incident2 *ui;
    QSqlDatabase dbconn;
    void SelectAll();
};

#endif // INCIDENT2_H
