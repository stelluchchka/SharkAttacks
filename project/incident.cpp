#include "incident.h"
#include "ui_incident.h"
#include "adminmenu.h"

void Incident::SelectAll() {
    ui->tw->clearContents();
    ui->leCountry->clear();
    ui->leDate->clear();
    ui->leFatalities->clear();
    ui->leWaterBody->clear();
    ui->teExcerpt->clear();

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

Incident::Incident(QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Incident)
{
    ui->setupUi(this);
    this->dbconn = dbconn;
//    QSizeGrip *sizeGrip = new QSizeGrip(ui->tw);
//    sizeGrip->setFixedSize(16, 16);
//    sizeGrip->move(ui->tw->viewport()->width() - sizeGrip->width(), ui->tw->viewport()->height() - sizeGrip->height());

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

Incident::~Incident()
{
    delete ui;
    if (dbconn.isOpen())
        dbconn.close();
}

void Incident::on_btnBack_clicked()
{
    this->close();
    AdminMenu *w = new AdminMenu(dbconn);
    w->setModal(true);
    w->exec();
}

void Incident::on_btnAdd_clicked()
{
    QString date = ui->leDate->text();
    QString country = ui->leCountry->text();
    QString water_body = ui->leWaterBody->text();
    QString fatalities = ui->leFatalities->text();
    QString news = ui->leNewsName->text();
    QString excerpt = ui->teExcerpt->toPlainText();

    if (date.isEmpty() || fatalities.isEmpty() || country.isEmpty() || water_body.isEmpty() || news.isEmpty() || excerpt.isEmpty()) {
        QMessageBox::critical(this, "Error!", "Enter all the required fields!");
        return;
    }
    QSqlQuery query(dbconn);
    if (!country.isEmpty() && !water_body.isEmpty()) {
        QMessageBox::critical(this, "Error!", "Enter all the required fields!");
        query.prepare("INSERT INTO location(country, water_body) VALUES (:country, :water_body)");
        query.bindValue(":country", country);
        query.bindValue(":water_body", water_body);

        if (!query.exec()) {
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (!date.isEmpty() && !fatalities.isEmpty() && !country.isEmpty() && !water_body.isEmpty()) {
        query.prepare("INSERT INTO incident(date, fatalities, location_id) VALUES (:date, :fatalities, (select location_id from location where country = :country and water_body = :water_body limit 1))");
        query.bindValue(":date", date);
        query.bindValue(":fatalities", fatalities);
        query.bindValue(":country", country);
        query.bindValue(":water_body", water_body);

        if (!query.exec()) {
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (!date.isEmpty() && !fatalities.isEmpty() && !news.isEmpty() && !excerpt.isEmpty()) {
        query.prepare("INSERT INTO news(news_name, excerpt, incident_id) VALUES (:news, :excerpt, (select incident_id from incident where date = :date and fatalities = :f  limit 1))");
        query.bindValue(":news", news);
        query.bindValue(":excerpt", excerpt);
        query.bindValue(":date", date);
        query.bindValue(":f", fatalities);

        if (!query.exec()) {
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    QMessageBox::about(this,"congr", "add 1 row");
    SelectAll();
}

void Incident::on_btnEdit_clicked()
{
    int currentIndex = ui->tw->currentIndex().row();
    if (currentIndex < 0)
    {
        QMessageBox::critical(this,"Error","Not selected row!");
        return;
    }
    QSqlQuery query(dbconn);
    query.prepare("select incident_id from incident where date = :date");
    query.bindValue(":date", ui->tw->item(currentIndex, 0)->text());
    query.exec();
    int id;
    if (query.next())
        id = query.value("incident_id").toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "edit", "sure?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if (!ui->leDate->text().isEmpty() && !ui->leFatalities->text().isEmpty()) {
            query.prepare("UPDATE incident SET date = :date, fatalities = :f, location_id = (SELECT location_id FROM location WHERE country = :country AND incident_id = :incident_id");
            query.bindValue(":date", ui->leDate->text());
            query.bindValue(":f", ui->leFatalities->text().toInt());
            query.bindValue("id", id);
            query.bindValue(":country", ui->tw->item(currentIndex, 2)->text());
            if (!query.exec()) {
                QMessageBox::about(this, "Error updating incident table:", query.lastError().text());
                return;
            }
        }
        if (!ui->leNewsName->text().isEmpty() && !ui->teExcerpt->toPlainText().isEmpty()) {
            query.prepare("UPDATE news SET news_name = :news_name, excerpt = :excerpt WHERE incident_id = :incident_id");
            query.bindValue(":news_name", ui->leNewsName->text());
            query.bindValue(":excerpt", ui->teExcerpt->toPlainText());
            query.bindValue(":incident_id", id);
            if (!query.exec()) {
                QMessageBox::about(this, "Error updating news table:", query.lastError().text());
                return;
            }
        }
        if (!ui->leCountry->text().isEmpty() && !ui->leWaterBody->text().isEmpty()) {
            query.prepare("UPDATE location SET country = :new_country, water_body = :new_water_body WHERE location_id = (SELECT location_id FROM location WHERE country = :country AND incident_id = :incident_id");
            query.bindValue(":new_country", ui->leCountry->text());
            query.bindValue(":new_water_body", ui->leWaterBody->text());
            query.bindValue(":country", ui->tw->item(currentIndex, 2)->text());
            query.bindValue(":incident_id", id);
            if (!query.exec()) {
                QMessageBox::about(this, "Error updating news table:", query.lastError().text());
                return;
            }
        }
    }

    SelectAll();
}

void Incident::on_btnDel_clicked()
{
    QSqlQuery query(dbconn);
    int currentIndex = ui->tw->currentIndex().row();
    if (currentIndex < 0)
    {
        QMessageBox::critical(this,"Error","Not selected row!");
        return;
    }
    query.prepare("select incident_id from incident where date = :date");
    query.bindValue(":date", ui->tw->item(currentIndex, 0)->text());
    query.exec();
    int id;
    if (query.next())
        id = query.value("incident_id").toInt();
    query.prepare("delete from incident where incident_id = :id;");
    query.bindValue(":id", id);
    if( !query.exec() )
       {
           QMessageBox::critical(this,"Error",query.lastError().text());
           return;
       }
    else QMessageBox::about(this,"congr", "Del 1 row");
}
