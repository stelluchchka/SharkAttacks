#ifndef LOCATION_H
#define LOCATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <adminmenu.h>
#include <qdebug.h>

namespace Ui {
class Location;
}

class Location : public QDialog
{
    Q_OBJECT

public:
    explicit Location(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~Location();
    void SelectAll();
    QVector<int> id;
    int currentIndex = 0;

private slots:

    void on_btnBack_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_btnEdit_clicked();

    void on_btnPrev_clicked();

    void on_btnNext_clicked();

    void on_pushButton_clicked();

private:
    Ui::Location *ui;
    QSqlDatabase dbconn;
};

#endif // LOCATION_H
