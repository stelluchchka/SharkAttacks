#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_btnLocation_clicked();

    void on_btnChangeUser_clicked();

    void on_btnVictims_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Menu *ui;
    QSqlDatabase dbconn;
};

#endif // MENU_H
