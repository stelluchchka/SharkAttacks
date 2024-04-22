#include "autorization.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Autorization w;
    w.show();
    return a.exec();

//    void dbconnect() {
//        if(! dbconn.isOpen())
//        {
//            dbconn=QSqlDatabase::addDatabase("QPSQL");

//            dbconn.setDatabaseName("shark");
//            dbconn.setHostName("localhost");
//            dbconn.setUserName("postgres");
//            dbconn.setPassword("1234");

//            if(!dbconn.open())
//                QMessageBox::about(this, "Error of connect!", dbconn.lastError().text());
//        }
//    }
}
