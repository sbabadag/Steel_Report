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
                                     "poz varchar(40), "
                                     "adet int,"
                                     "agirlik real,"
                                     "boya_alani real)");


    query.exec("create table ass_parts (pid int,"
                                    "aid int,"
                                    "selfid int,"
                                     "poz varchar(40),"
                                     "adet int,"
                                     "agirlik real,"
                                     "boya_alani real)");

    auto P = ReadPartListFile();
    auto A = ReadAssemlyPartListFile();

    for (unsigned int i=0; i<P.size();i++)
    {
       QString str = QString("insert into single values(0,%1,'%2','%3',%4,%5,%6,'%7',%8)").arg(i).arg(P[i]->PartPos).arg(P[i]->Profile).arg(P[i]->Quantity).arg(P[i]->Weight).arg(P[i]->Length).arg(P[i]->Material).arg(P[i]->Area);
       query.exec(str);
    }

    //

    for (unsigned int i=0; i<A.size();i++)
    {
       QString str = QString("insert into assembly values(0,%1,'%2',%3,%4,%5)").arg(A[i]->ID).arg(A[i]->Assemblypos).arg(A[i]->Quantity).arg(A[i]->Weight).arg(A[i]->Weight);
       query.exec(str);
       //
        auto PP = A[i]->Part_list;
        for (unsigned int j=0; j<PP->size();j++)
        {
            QString str = QString("insert into ass_parts values(0,%1,'%2',%3,%4,%5,%6)").arg(PP->at(j)->owner).arg(j).arg(PP->at(j)->PartPos).arg(PP->at(j)->Quantity).arg(PP->at(j)->Weight).arg(PP->at(j)->Weight);
            query.exec(str);

        }

    }




 //  query.exec("SELECT * FROM ass_parts WHERE (ass_parts.aid=assembly.selfid)");





    return true;
}
//! [0]

#endif
