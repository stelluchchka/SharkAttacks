#include "adminmenu.h"
#include "ui_adminmenu.h"
#include "location.h"
#include "incident.h"
#include "shark.h"
#include "victim.h"
#include "autorization.h"

AdminMenu::AdminMenu(QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminMenu)
{
    ui->setupUi(this);
    this->dbconn = dbconn;
}

AdminMenu::~AdminMenu()
{
    delete ui;
    if (dbconn.isOpen())
        dbconn.close();
}

void AdminMenu::on_btnAutorization_clicked()
{
    this->close();
    Autorization *w = new Autorization();
    w->show();
}

void AdminMenu::on_btnLocation_clicked()
{
    this->close();
    Location *w = new Location(dbconn);
    w->setModal(true);
    w->exec();
}

void AdminMenu::on_btnShark_clicked()
{
    this->close();
    Shark *w = new Shark(dbconn);
    w->setModal(true);
    w->exec();
}

void AdminMenu::on_btnVictim_clicked()
{
    this->close();
    Victim *w = new Victim(dbconn);
    w->setModal(true);
    w->exec();
}

void AdminMenu::on_btnIncident_clicked()
{
    this->close();
    Incident *w = new Incident(dbconn);
    w->setModal(true);
    w->exec();
}
