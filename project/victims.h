#ifndef VICTIMS_H
#define VICTIMS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <qdebug.h>
#include <menu.h>

namespace Ui {
class Victims;
}

class Victims : public QDialog
{
    Q_OBJECT

public:
    explicit Victims(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~Victims();

private slots:
    void on_btnBack_clicked();

    void on_btnDetails_clicked();

private:
    Ui::Victims *ui;
    QSqlDatabase dbconn;
    void SelectAll();
};

#endif // VICTIMS_H
