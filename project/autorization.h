#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QMainWindow>

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>


QT_BEGIN_NAMESPACE
namespace Ui { class Autorization; }
QT_END_NAMESPACE

class Autorization : public QMainWindow
{
    Q_OBJECT

public:
    Autorization(QWidget *parent = nullptr);
    ~Autorization();
    void dbconnect();

private slots:
    void on_btnAutorization_clicked();

private:
    Ui::Autorization *ui;
    QSqlDatabase dbconn;
};
#endif // AUTORIZATION_H
