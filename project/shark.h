#ifndef SHARK_H
#define SHARK_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QComboBox>
#include <QSqlError>
#include <adminmenu.h>

namespace Ui {
class Shark;
}

class Shark : public QDialog
{
    Q_OBJECT

public:
    explicit Shark(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~Shark();
    void SelectAll();
    QVector<int> id;
    int currentIndex = 0;

private slots:
    void on_btnBack_clicked();

    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void on_btnDel_clicked();

    void on_btnPrev_clicked();

    void on_btnNext_clicked();

    void on_btnDone_clicked();

private:
    Ui::Shark *ui;
    QSqlDatabase dbconn;
};

#endif // SHARK_H
