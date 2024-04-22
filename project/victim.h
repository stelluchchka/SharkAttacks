#ifndef VICTIM_H
#define VICTIM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <adminmenu.h>

namespace Ui {
class Victim;
}

class Victim : public QDialog
{
    Q_OBJECT

public:
    explicit Victim(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~Victim();
    void SelectAll();

private slots:
    void on_btnBack_clicked();

    void on_btnDetails_clicked();

private:
    Ui::Victim *ui;
    QSqlDatabase dbconn;
};

#endif // VICTIM_H
