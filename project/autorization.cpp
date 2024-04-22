#include "autorization.h"
#include "ui_autorization.h"
#include "menu.h"
#include "adminmenu.h"

#include<QPixmap>
#include <QMessageBox>

Autorization::Autorization(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Autorization)
{
    ui->setupUi(this);
    setWindowTitle("Welcome!!");
    QPixmap pix(":/img/shark2.png");
    int w = ui->img->width();
    int h = ui->img->height();
    ui->img->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

Autorization::~Autorization()
{
    delete ui;
    if (dbconn.isOpen())
        dbconn.close();
}

void Autorization::on_btnAutorization_clicked()
{
    QString login = ui->leLogin->text();
    QString pass = ui->lePassword->text();

    if (dbconn.isOpen())
        dbconn.close();

    dbconn=QSqlDatabase::addDatabase("QPSQL");
    dbconn.setDatabaseName("shark");
    dbconn.setHostName("localhost");
    dbconn.setUserName(login);
    dbconn.setPassword(pass);

    if(!dbconn.open()) {
        QMessageBox::warning(this, "oooops..", "wrong login or password, try again!");
    }
    else {
        //QMessageBox::about(this, "congr!", "eee");
        this->close();
        if (login == "postgres") {
            AdminMenu *w = new AdminMenu(dbconn);
            w->setModal(true);
            w->exec();
        } else {
            Menu *w = new Menu(dbconn);
            w->setModal(true);
            w->exec();
        }
    }
}
