#include "incident2.h"
#include "ui_incident2.h"
#include "menu.h"

void incident2::SelectAll() {

    QSqlQuery query(dbconn);
    QString sqlstr = "SELECT date, fatalities, country, water_body, news_name, excerpt FROM incident inner join location on location.location_id = incident.location_id join news on news.incident_id = incident.incident_id";
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
        ui->tw->setItem(i,0,new QTableWidgetItem(query.value("date").toString()));
        ui->tw->setItem(i,1,new QTableWidgetItem(query.value("fatalities").toString()));
        ui->tw->setItem(i,2,new QTableWidgetItem(query.value("country").toString()));
        ui->tw->setItem(i,3,new QTableWidgetItem(query.value("water_body").toString()));
        ui->tw->setItem(i,4,new QTableWidgetItem(query.value("news_name").toString()));
        ui->tw->setItem(i,5,new QTableWidgetItem(query.value("excerpt").toString()));
        i++;
    }
}

incident2::incident2(QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::incident2)
{
    ui->setupUi(this);
    this->dbconn = dbconn;

    ui->tw->setColumnCount(6);
    ui->tw->setAutoScroll(true);
    ui->tw->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tw->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw->horizontalHeader()->setStretchLastSection(true);
    ui->tw->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tw->setHorizontalHeaderItem(0,new QTableWidgetItem("date"));
    ui->tw->setHorizontalHeaderItem(1,new QTableWidgetItem("fatalities"));
    ui->tw->setHorizontalHeaderItem(2,new QTableWidgetItem("country"));
    ui->tw->setHorizontalHeaderItem(3,new QTableWidgetItem("location"));
    ui->tw->setHorizontalHeaderItem(4,new QTableWidgetItem("news name"));
    ui->tw->setHorizontalHeaderItem(5,new QTableWidgetItem("excerpt"));

    SelectAll();
}

incident2::~incident2()
{
    delete ui;
    if (dbconn.isOpen())
        dbconn.close();
}

void incident2::on_btnBack_clicked()
{
    this->close();
    Menu *w = new Menu(dbconn);
    w->setModal(true);
    w->exec();
}
