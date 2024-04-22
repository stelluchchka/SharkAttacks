#include "details_victims.h"
#include "ui_details_victims.h"
#include "victim.h"

Details_victims::Details_victims(int Id, QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Details_victims)
{
    ui->setupUi(this);
    this->dbconn = dbconn;
    id = Id;

    ui->tw->setRowCount(7);
    ui->tw->setAutoScroll(true);
    ui->tw->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tw->setSelectionBehavior(QAbstractItemView::SelectColumns);
    ui->tw->verticalHeader()->setStretchLastSection(true);
    ui->tw->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tw->setVerticalHeaderItem(0,new QTableWidgetItem("name"));
    ui->tw->setVerticalHeaderItem(1,new QTableWidgetItem("gender"));
    ui->tw->setVerticalHeaderItem(2,new QTableWidgetItem("age"));
    ui->tw->setVerticalHeaderItem(3,new QTableWidgetItem("activity"));
    ui->tw->setVerticalHeaderItem(4,new QTableWidgetItem("shark"));
    ui->tw->setVerticalHeaderItem(5,new QTableWidgetItem("witness name"));
    ui->tw->setVerticalHeaderItem(6,new QTableWidgetItem("info"));

    QSqlQuery query(dbconn);
    QString sqlstr = "SELECT victim_name, gender, age, activity, shark_name, witness_name, witness_info FROM victim join shark on shark.shark_id = victim.shark_id join incident on incident.incident_id = victim.incident_id join witness on incident.incident_id = witness.incident_id where victim_id = :id order by victim_id;";
    query.prepare(sqlstr);
    query.bindValue(":id", id);
    if( !query.exec() )
    {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }
    if (query.isActive()) {
        ui->tw->setColumnCount(query.size());
        ui->tw->setHorizontalHeaderItem(0,new QTableWidgetItem("details"));
    }
    if (query.next()) {
        ui->tw->setItem(0,0,new QTableWidgetItem(query.value("victim_name").toString()));
        ui->tw->setItem(1,0,new QTableWidgetItem(query.value("gender").toString()));
        ui->tw->setItem(2,0,new QTableWidgetItem(query.value("age").toString()));
        ui->tw->setItem(3,0,new QTableWidgetItem(query.value("activity").toString()));
        ui->tw->setItem(4,0,new QTableWidgetItem(query.value("shark_name").toString()));
        ui->tw->setItem(5,0,new QTableWidgetItem(query.value("witness_name").toString()));
        ui->tw->setItem(6,0,new QTableWidgetItem(query.value("witness_info").toString()));
    }
}

Details_victims::~Details_victims()
{
    delete ui;
    if (dbconn.isOpen())
        dbconn.close();
}

void Details_victims::on_btnEdit_clicked()
{
    QSqlQuery query(dbconn);
    if (!ui->leName->text().isEmpty()) {
        QString name = ui->leName->text();
        query.prepare("update victim set victim_name = :name where victim_id = :id");
        query.bindValue(":name", name);
        query.bindValue(":id", id);
        if(!query.exec()) {
            QMessageBox::warning(this, "error", query.lastError().text());
        }
    }
    if (!ui->leGender->text().isEmpty()) {
        QString gender = ui->leGender->text();
        query.prepare("update victim set gender = :g where victim_id = :id");
        query.bindValue(":g", gender);
        query.bindValue(":id", id);
        if(!query.exec()) {
            QMessageBox::warning(this, "error", query.lastError().text());
        }
    }
    if (!ui->leAge->text().isEmpty()) {
        QString age = ui->leAge->text();
        query.prepare("update victim set age = :age where victim_id = :id");
        query.bindValue(":age", age);
        query.bindValue(":id", id);
        if(!query.exec()) {
            QMessageBox::warning(this, "error", query.lastError().text());
        }
    }
    if (!ui->leActivity->text().isEmpty()) {
        QString activity = ui->leActivity->text();
        query.prepare("update victim set activity = :a where victim_id = :id");
        query.bindValue(":a", activity);
        query.bindValue(":id", id);
        if(!query.exec()) {
            QMessageBox::warning(this, "error", query.lastError().text());
        }
    }
}

void Details_victims::on_btnDel_clicked()
{
    QSqlQuery query(dbconn);
    query.prepare("delete from victim where victim_id = :id;");
    query.bindValue(":id", id);
    if( !query.exec() )
       {
           QMessageBox::critical(this,"Error",query.lastError().text());
           return;
       }
    else QMessageBox::about(this,"congr", "Del 1 row");
    this->close();
}
