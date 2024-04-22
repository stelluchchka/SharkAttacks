#include "search.h"
#include "ui_search.h"
#include <location.h>
#include "menu.h"

Search::Search(QString text, QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    this->dbconn = dbconn;
    qDebug()<<text;


    ui->twLocation->setColumnCount(2);
    ui->twLocation->setAutoScroll(true);
    ui->twLocation->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twLocation->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twLocation->horizontalHeader()->setStretchLastSection(true);
    ui->twLocation->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->twLocation->setHorizontalHeaderItem(0,new QTableWidgetItem("country"));
    ui->twLocation->setHorizontalHeaderItem(1,new QTableWidgetItem("water body"));

    QSqlQuery query(dbconn);
    QString sqlstr = "select * from location where country Like :text";
    query.prepare(sqlstr);
    query.bindValue(":text", text);
    if( !query.exec() )
    {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }
    if (query.isActive())
        ui->twLocation->setRowCount(query.size());

    int i=0;
    while(query.next())
    {
        ui->twLocation->setItem(i,0,new QTableWidgetItem(query.value("country").toString()));
        ui->twLocation->setItem(i,1,new QTableWidgetItem(query.value("water_body").toString()));
        i++;
    }
}

Search::~Search()
{
    delete ui;
    if (dbconn.isOpen())
        dbconn.close();
}

void Search::on_btnBack_clicked()
{
    this->close();
    if (dbconn.userName() == "postgres") {
        Location *w = new Location(dbconn);
        w->setModal(true);
        w->exec();
    } else {
        Menu *w = new Menu(dbconn);
        w->setModal(true);
        w->exec();
    }
}
