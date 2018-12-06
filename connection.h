#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <myfunctions.h>


//! [0]
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tsteel");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    query.exec("create table proje (pid int primary key,"
                                     "proje_adi varchar(40),"
                                     "bas_tarihi date,"
                                    "bit_tarihi date,"
                                    "buton int)");

    query.exec("create table platinalar (pid int ,"
                                   "selfid int,"
                                     "poz varchar(40),"
                                     "profil varchar(40),"
                                     "t int,"
                                     "agirlik int,"
                                     "m_sinifi varchar(40),"
                                     "boya_alani int)");

    query.exec("create table single (pid int,"
                                     "selfid int,"
                                     "poz varchar(40),"
                                     "profil varchar(40),"
                                     "adet int,"
                                     "uadet int,"
                                     "agirlik real,"
                                     "uzunluk int,"
                                     "m_sinifi varchar(40),"
                                     "boya_alani real)");

    query.exec("create table assembly (pid int,"
                                    "selfid int,"
                                     "poz varchar(40), "
                                     "profil varchar(40), "
                                     "adet int,"
                                     "uadet int,"
                                     "agirlik real)");

    query.exec("create table imalat (pid int,"
                                    "selfid int,"
                                    "adet int,"
                                    "poz varchar(40), "
                                     "tarih date,"
                                     "imalattipi varchar(40),"
                                     "imalatci varchar(50),"
                                     "uygunsuzluk varchar(255) )");



    query.exec("create table ass_parts (pid int,"
                                    "aid int,"
                                    "selfid int,"
                                    "poz varchar(40),"
                                    "profil varchar(40),"
                                     "adet int,"
                                     "uadet int,"
                                     "boya_alani real,"
                                     "agirlik real,"
                                     "kesim_tarihi date)");

    QString str = QString("insert into proje values(0,'ENGIE V1','2018-11-30','2018-12-30',0)");
    query.exec(str);

    QString str1 = QString("insert into imalat values(0,1,2,'poz','2018-11-30','2018-11-30','2018-12-30','ali','8/8')");
    query.exec(str1);

db.close();
    return true;
}
//! [0]

#endif
