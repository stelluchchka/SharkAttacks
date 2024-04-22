#include "shark.h"
#include "ui_shark.h"

void Shark::SelectAll() {
    QSqlQuery query(dbconn);
    // shark
    query.prepare("SELECT DISTINCT shark_name FROM shark where shark_id = :id");
    query.bindValue(":id", id[currentIndex]);
    query.exec();
    ui->leShark->clear();
    while (query.next())
        ui->leShark->setText(query.value(0).toString());
    // country
    query.prepare("select country FROM location join shark on shark.location_id = location.location_id where shark_id = :id");
    query.bindValue(":id", id[currentIndex]);
    query.exec();
    while (query.next())
        ui->leCountry->setText(query.value(0).toString());
    // water_body
    query.prepare("SELECT DISTINCT water_body FROM location where country = :c");
    query.bindValue(":c", ui->leCountry->text());
    query.exec();
    ui->leWaterBody->clear();
    while (query.next())
        ui->leWaterBody->setText(query.value(0).toString());

}

Shark::Shark(QSqlDatabase dbconn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shark)
{
    ui->setupUi(this);
    this->dbconn = dbconn;

    ui->btnDone->hide();
    ui->lblCountry->hide();
    ui->lblShark->hide();
    ui->cbCountry->hide();
    ui->leNewShark->hide();

    currentIndex = 0;
    QSqlQuery query(dbconn);
    query.exec("select shark_id from shark order by shark_id");
    while(query.next()) {
        id.append(query.value(0).toInt());
    }
    SelectAll();
}

Shark::~Shark()
{
    delete ui;
}

void Shark::on_btnBack_clicked()
{
    this->close();
    AdminMenu *w = new AdminMenu(dbconn);
    w->setModal(true);
    w->exec();
}
void Shark::on_btnAdd_clicked()
{
    //show widgets
    ui->btnDone->show();
    ui->lblCountry->show();
    ui->lblShark->show();
    ui->cbCountry->show();
    ui->leNewShark->show();

    //fill cbCountry
    QSqlQuery query(dbconn);
    query.exec("select country FROM location");
    QString country;
    while(query.next()) {
        country = query.value("country").toString();
        ui->cbCountry->addItem(country);
    }
}

void Shark::on_btnDone_clicked()
{
    QSqlQuery query(dbconn);
    //add new shark
    QString location_id = QString::number(ui->cbCountry->currentIndex());
    QString shark = ui->leNewShark->text();
    if (shark == NULL) {
        QMessageBox::critical(this, "error!", "Enter new shark!");
    }
    else {
    query.prepare("INSERT INTO shark(shark_name, location_id) VALUES(:shark, :location_id)");
    query.bindValue(":location_id", location_id);
    query.bindValue(":shark", shark);
    if( !query.exec() )
       {
           QMessageBox::critical(this,"Error",query.lastError().text());
           return;
       }
    else QMessageBox::about(this,"congr", "AddRead 1 row");

    id.clear();
    query.exec("select shark_id from shark order by shark_id");
    while(query.next()) {
        id.append(query.value(0).toInt());
    }
    SelectAll();
    ui->btnDone->hide();
    ui->lblCountry->hide();
    ui->lblShark->hide();
    ui->cbCountry->hide();
    ui->leNewShark->hide();
    }
}

void Shark::on_btnEdit_clicked()
{
    QSqlQuery query(dbconn);
    QString shark = ui->leShark->text();
    int intId = id[currentIndex];
    QString id = QString::number(intId);
    query.prepare("UPDATE shark SET shark_name=:shark where shark_id = :id;");
    query.bindValue(":shark", shark);
    query.bindValue(":id", id);
    if( !query.exec() )
       {
           QMessageBox::critical(this,"Error",query.lastError().text());
           return;
       }
    else QMessageBox::about(this,"congr", "Edit 1 row");
    SelectAll();
}
void Shark::on_btnDel_clicked()
{
    QSqlQuery query(dbconn);
    int intId = id[currentIndex];
    QString id = QString::number(intId);
    query.prepare("delete from shark where shark_id = :id;");
    query.bindValue(":id", id);
    if( !query.exec() )
       {
           QMessageBox::critical(this,"Error",query.lastError().text());
           return;
       }
    else QMessageBox::about(this,"congr", "Del 1 row");
    if (currentIndex > 0)
        currentIndex--;
    id.clear();
    query.exec("select shark_id from shark order by shark_id");
    while(query.next()) {
        id.append(query.value(0).toInt());
    }
    SelectAll();
}

void Shark::on_btnPrev_clicked()
{
    if (currentIndex > 0) {
        currentIndex--;
        SelectAll();
    }
}

void Shark::on_btnNext_clicked()
{
    if (currentIndex < id.size()-1) {
        currentIndex++;
        SelectAll();
    }
}
