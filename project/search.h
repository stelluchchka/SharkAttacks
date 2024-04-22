#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QString text, QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~Search();

private slots:
    void on_btnBack_clicked();

private:
    Ui::Search *ui;
    QSqlDatabase dbconn;
};

#endif // SEARCH_H
