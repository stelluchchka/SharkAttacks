#include "location.h"
#include "ui_location.h"
#include "search.h"

void Location::SelectAll() {
    QSqlQuery query(dbconn);
    // country
    query.prepare("SELECT DISTINCT country FROM location where location_id = :location_id");
    query.bindValue(":location_id", id[currentIndex]);
    query.exec();
    ui->leCountry->clear();
    while (query.next())
        ui->leCountry->setText(query.value(0).toString());
    // water_body
    query.prepare("SELECT DISTINCT water_body FROM location where location_id = :location_id");
    query.bindValue(":location_id", id[currentIndex]);
    query.exec();
    ui->leWaterBody->clear();
    while (query.next())
        ui->leWaterBody->setText(query.value(0).toString());

    QString sqlstr = "SELECT date FROM incident INNER JOIN location ON location.location_id = incident.location_id WHERE location.location_id = :location_id";
    query.prepare(sqlstr);
    query.bindValue(":location_id", id[currentIndex]);
    if( !query.exec() )
    {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }
    if (query.isActive())
        ui->twIncidents->setRowCount(query.size());

    int i = 0;
    while(query.next()) {
        ui->twIncidents->setItem(0,i,new QTableWidgetItem(query.value("date").toString()));
        ++i;
    }
}

Location::Location(QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Location)
{
    ui->setupUi(this);
    this->dbconn = dbconn;

    ui->twIncidents->setColumnCount(1);
    ui->twIncidents->setAutoScroll(true);
    ui->twIncidents->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twIncidents->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twIncidents->horizontalHeader()->setStretchLastSection(true);
    ui->twIncidents->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->twIncidents->setHorizontalHeaderItem(0,new QTableWidgetItem("date"));

    currentIndex = 0;
    QSqlQuery query(dbconn);
    query.exec("select location_id from location order by location.location_id");
    while(query.next()) {
        id.append(query.value(0).toInt());
    }
    SelectAll();
}

Location::~Location()
{
    delete ui;
    ui->twIncidents->clearContents();
    if (dbconn.isOpen())
        dbconn.close();
}

void Location::on_btnBack_clicked()
{
    this->close();
    AdminMenu *w = new AdminMenu(dbconn);
    w->setModal(true);
    w->exec();
}

void Location::on_btnAdd_clicked()
{
    QString country = ui->leCountry->text();
    QString water_body = ui->leWaterBody->text();
    if (country == NULL || water_body == NULL) {
        QMessageBox::critical(this, "error!", "Enter new location!");
    }
    QSqlQuery query(dbconn);
    query.prepare("INSERT INTO location(country, water_body) VALUES(:country, :water_body)");
    //query.bindValue(":location_id", location_id);
    query.bindValue(":country", country);
    query.bindValue(":water_body", water_body);
    if( !query.exec() )
       {
           QMessageBox::critical(this,"Error",query.lastError().text());
           return;
       }
    QMessageBox::about(this,"congr", "AddRead 1 row");
    SelectAll();
}

void Location::on_btnDel_clicked()
{
    QString country = ui->leCountry->text();
    QSqlQuery query(dbconn);
    QString sqlstr = "delete from location where country = :country";
    query.prepare(sqlstr);
    query.bindValue(":country", country);
    if( !query.exec() )
       {
           QMessageBox::critical(this,"Error",query.lastError().text());
           return;
       }

    if (currentIndex > 0)
        currentIndex--;
    id.clear();
    query.exec("select location_id from location order by location.location_id");
    while(query.next()) {
        id.append(query.value(0).toInt());
    }
    SelectAll();
}

void Location::on_btnEdit_clicked()
{
    QSqlQuery query(dbconn);
    QString country = ui->leCountry->text();
    QString water_body = ui->leWaterBody->text();
    int intId = id[currentIndex];
    QString id = QString::number(intId);
    query.prepare("UPDATE location SET country=:country, water_body=:water_body where location_id = :id;");
    query.bindValue(":country", country);
    query.bindValue(":water_body", water_body);
    query.bindValue(":id", id);
    if( !query.exec() )
       {
           QMessageBox::critical(this,"Error",query.lastError().text());
           return;
       }
    SelectAll();
}

void Location::on_btnPrev_clicked()
{
    if (currentIndex > 0) {
        currentIndex--;
        SelectAll();
    }
}

void Location::on_btnNext_clicked()
{
    if (currentIndex < id.size()-1) {
        currentIndex++;
        SelectAll();
    }
}

void Location::on_pushButton_clicked()
{
    QString text = ui->leSearch->text();
    text.append("%");
    close();
    Search *w = new Search(text, dbconn);
    w->exec();
    w->setModal(true);
}
