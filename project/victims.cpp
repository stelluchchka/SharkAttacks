#include "victims.h"
#include "ui_victims.h"
#include "details_victims.h"

void Victims::SelectAll() {
    QSqlQuery query(dbconn);
    QString sqlstr = "SELECT * FROM victim";
    query.prepare(sqlstr);
    if( !query.exec() )
    {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }
    if (query.isActive())
        ui->tw->setRowCount(query.size());

    int i=0;
    while(query.next())
    {
        ui->tw->setItem(i,0,new QTableWidgetItem(query.value("victim_name").toString()));
        ui->tw->setItem(i,1,new QTableWidgetItem(query.value("activity").toString()));
        i++;
    }

}

Victims::Victims(QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Victims)
{
    ui->setupUi(this);
    this->dbconn = dbconn;

    ui->tw->setColumnCount(2);
    ui->tw->setAutoScroll(true);
    ui->tw->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tw->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw->horizontalHeader()->setStretchLastSection(true);
    ui->tw->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tw->setHorizontalHeaderItem(0,new QTableWidgetItem("name"));
    ui->tw->setHorizontalHeaderItem(1,new QTableWidgetItem("activity"));

    SelectAll();
}


Victims::~Victims()
{
    delete ui;
    if (dbconn.isOpen()) {
        dbconn.close();
    }
}

void Victims::on_btnBack_clicked()
{
    this->close();
    Menu *w = new Menu(dbconn);
    w->setModal(true);
    w->exec();
}

void Victims::on_btnDetails_clicked()
{
    int id = ui->tw->currentIndex().row() + 1;
    if (id != 0) {
        Details_victims *w = new Details_victims(id, dbconn);
        w->setModal(true);
        w->open();
    }
}
