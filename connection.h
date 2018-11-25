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



//



    query.exec("create table proje (pid int primary key,"
                                     "proje_adi varchar(40),"
                                     "bas_tarihi date,"
                                     "bit_tarihi date");

    query.exec("create table platinalar (pid int ,"
                                   "selfid int,"
                                     "poz varchar(40),"
                                     "t int,"
                                     "agirlik int,"
                                     "m_sinifi varchar(40),"
                                     "boya_alani int)");

    query.exec("create table single (pid int,"
                                     "selfid int,"
                                     "poz varchar(40),"
                                     "profil varchar(40),"
                                     "adet int,"
                                     "agirlik real,"
                                     "uzunluk int,"
                                     "m_sinifi varchar(40),"
                                     "boya_alani real)");

    query.exec("create table assembly (pid int,"
                                    "selfid int,"
                                    "assid varchar(40),"
                                     "poz varchar(40), "
                                     "adet int,"
                                     "agirlik int,"
                                     "boya_alani int)");


    query.exec("create table ass_parts (pid int,"
                                    "aid int,"
                                    "selfid int,"
                                     "poz varchar(40),"
                                     "adet int,"
                                     "agirlik int,"
                                     "boya_alani int)");

    auto P = ReadPartListFile();

    for (unsigned int i=0; i<P.size();i++)
    {
       QString str = QString("insert into single values(0,%1,'%2','%3',%4,%5,%6,'%7',%8)").arg(i).arg(P[i]->PartPos).arg(P[i]->Profile).arg(P[i]->Quantity).arg(P[i]->Weight).arg(P[i]->Length).arg(P[i]->Material).arg(P[i]->Area);
       query.exec(str);
    }


    query.exec("insert into proje values(0, 'Sektör Kimya', '2018-06-06','2018-06-08')");
    query.exec("insert into assembly values(0,1,1, 'P/101', 5,100,5)");
    query.exec("insert into assembly values(0,2,1, 'P/101', 5,100,5)");

//

    query.exec("insert into ass_parts values(0,1,4, 's/1', 1,20,6)");
    query.exec("insert into ass_parts values(0,1,5, 's/2', 3,22,7)");
    query.exec("insert into ass_parts values(0,1,6, 's/3', 5,2,1)");
    //
    query.exec("insert into ass_parts values(0,2,1, 's/4', 1,20,6)");
    query.exec("insert into ass_parts values(0,2,2, 's/5', 3,22,7)");
    query.exec("insert into ass_parts values(0,2,3, 's/6', 5,2,1)");
    //
 //   query.exec("insert into single values(0,1019,'PL20*220','22',125,1,2,'e',2)");




 //  query.exec("SELECT * FROM ass_parts WHERE (ass_parts.aid=assembly.selfid)");





    return true;
}
//! [0]

#endif
