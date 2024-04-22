#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>

namespace Ui {
class AdminMenu;
}

class AdminMenu : public QDialog
{
    Q_OBJECT

public:
    explicit AdminMenu(QSqlDatabase dbconn = QSqlDatabase::addDatabase("QPSQL") ,QWidget *parent = nullptr);
    ~AdminMenu();

private slots:
    void on_btnAutorization_clicked();

    void on_btnLocation_clicked();

    void on_btnShark_clicked();

    void on_btnVictim_clicked();

    void on_btnIncident_clicked();

private:
    Ui::AdminMenu *ui;
    QSqlDatabase dbconn;
};

#endif // ADMINMENU_H
