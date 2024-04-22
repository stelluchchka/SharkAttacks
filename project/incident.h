#ifndef INCIDENT_H
#define INCIDENT_H

#include <QDialog>
#include <QSizeGrip>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Incident;
}

class Incident : public QDialog
{
    Q_OBJECT

public:
    explicit Incident(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~Incident();

private slots:
    void on_btnBack_clicked();

    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void on_btnDel_clicked();

private:
    Ui::Incident *ui;
    QSqlDatabase dbconn;
    void SelectAll();

};

#endif // INCIDENT_H
