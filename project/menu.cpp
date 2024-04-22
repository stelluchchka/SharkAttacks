#include "menu.h"
#include "ui_menu.h"
#include "search.h"
#include"victims.h"
#include "autorization.h"
#include "incident2.h"

Menu::Menu(QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->dbconn = dbconn;
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_btnLocation_clicked()
{
    QString text = "%";
    close();
    Search *w = new Search(text, dbconn);
    w->exec();
    w->setModal(true);
}

void Menu::on_btnChangeUser_clicked()
{
    this->close();
    Autorization *w = new Autorization();
    w->show();
}

void Menu::on_btnVictims_clicked()
{
    close();
    Victims *w = new Victims(dbconn);
    w->exec();
    w->setModal(true);
}

void Menu::on_pushButton_5_clicked() //incident
{
    close();
    incident2 *w = new incident2(dbconn);
    w->exec();
    w->setModal(true);
}
