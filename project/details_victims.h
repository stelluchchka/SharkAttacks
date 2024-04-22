#ifndef DETAILS_VICTIMS_H
#define DETAILS_VICTIMS_H


#include <victims.h>

namespace Ui {
class Details_victims;
}

class Details_victims : public QDialog
{
    Q_OBJECT

public:
    explicit Details_victims(int Id, QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~Details_victims();
    int id;

private slots:
    void on_btnEdit_clicked();

    void on_btnDel_clicked();

private:
    Ui::Details_victims *ui;
    QSqlDatabase dbconn;

};

#endif // DETAILS_VICTIMS_H
