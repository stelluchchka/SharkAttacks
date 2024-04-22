#include "victim.h"
#include "ui_victim.h"
#include "details_victims.h"

void Victim::SelectAll() {
    QSqlQuery query(dbconn);
    QString sqlstr = "SELECT victim_name, gender, age, activity FROM victim ";
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
        ui->tw->setItem(i,1,new QTableWidgetItem(query.value("gender").toString()));
        ui->tw->setItem(i,2,new QTableWidgetItem(query.value("age").toString()));
        ui->tw->setItem(i,3,new QTableWidgetItem(query.value("activity").toString()));
        i++;
    }
}

Victim::Victim(QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Victim)
{
    ui->setupUi(this);
    this->dbconn = dbconn;

    ui->tw->setColumnCount(4);
    ui->tw->setAutoScroll(true);
    ui->tw->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tw->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw->horizontalHeader()->setStretchLastSection(true);
    ui->tw->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tw->setHorizontalHeaderItem(0,new QTableWidgetItem("name"));
    ui->tw->setHorizontalHeaderItem(1,new QTableWidgetItem("gender"));
    ui->tw->setHorizontalHeaderItem(2,new QTableWidgetItem("age"));
    ui->tw->setHorizontalHeaderItem(3,new QTableWidgetItem("activity"));

    SelectAll();
}

Victim::~Victim()
{
    delete ui;
    if (dbconn.isOpen()) {
        dbconn.close();
    }
}

void Victim::on_btnBack_clicked()
{
    this->close();
    AdminMenu *w = new AdminMenu(dbconn);
    w->setModal(true);
    w->exec();
}

void Victim::on_btnDetails_clicked()
{
    int Id = ui->tw->currentIndex().row();
    QString name = ui->tw->item(Id,0)->text();
    QSqlQuery query(dbconn);
    query.prepare("select victim_id from victim where victim_name = :n");
    query.bindValue(":n", name);
    if (!query.exec()) {
        QMessageBox::warning(this, "error", query.lastError().text());
    }
    int id;
    while (query.next())
        id = query.value(0).toInt();
    Details_victims *w = new Details_victims(id, dbconn);
    w->setModal(true);
    w->open();
    SelectAll();
}
