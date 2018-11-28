#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#endif // MYFUNCTIONS_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>
#include <QItemSelectionModel>
#include <qfile.h>
#include <QTextStream>
#include <QStringListModel>

struct TeklaPart {
    QString PartPos;
    QString Profile;
    int Quantity;
    QString Material;
    int Length;
    double Area;
    double Weight;
    int owner;
};

struct TeklaAssembly {
    int ID;
    QString Assemblypos;
    int Quantity;
    QString Mainpart;
    double Weight;
    std::vector<TeklaPart*> *Part_list;
};


std::vector<TeklaPart*> ReadPartListFile()
{
QFile file("C:/Users/sbaba/Documents/build-STEEL_REPORT-Desktop_Qt_5_11_1_MinGW_32bit-Debug/debug/Part_List.xsr");
if(!file.open(QIODevice::ReadOnly)) {
    QMessageBox::information(0, "error", file.errorString());
}

QTextStream in(&file);
QStringList fields;
std::vector<TeklaPart*> Part_list;
TeklaPart *APart;

QString tstr = "--------------------------------------------------------------------------";
QString QStr;


while(!in.atEnd()) {
    QString line = in.readLine();
    fields = line.split(" " , QString::SkipEmptyParts);
    QStr = fields.at(0);
    if ((QStr[0] != '-')) if
       (QStr  != "PartPos") if
       (QStr  != "TEKLA") if
       (QStr  != "CONTRACT:") if
       (QStr  != "Total")

    {
        APart = new TeklaPart;
        APart->PartPos   = fields[0];
        APart->Profile   = fields[1];
        APart->Quantity  = fields[2].toInt();
        APart->Material  = fields[3];
        APart->Length    = fields[4].toInt();
        APart->Area      = fields[5].toDouble();
        APart->Weight    = fields[6].toDouble();
        Part_list.push_back(APart);
    }
}

file.close();
 return Part_list;
}

std::vector<TeklaAssembly*> ReadAssemlyPartListFile()
{
QFile file("C:/Users/sbaba/Documents/build-STEEL_REPORT-Desktop_Qt_5_11_1_MinGW_32bit-Debug/debug/Assembly_Part_List.xsr");
if(!file.open(QIODevice::ReadOnly)) {
    QMessageBox::information(0, "error", file.errorString());
}

QTextStream in(&file);
QStringList fields;
std::vector<TeklaAssembly*> Assembly_Part_list;
std::vector<TeklaPart*> *Part_list;


TeklaPart *APart;
TeklaAssembly *AAss;
QString QStr;
int Assembly_Count  = 0;
Part_list           = new std::vector<TeklaPart*>;


while(!in.atEnd()) {
    QString line = in.readLine();
    fields = line.split(" " , QString::SkipEmptyParts);
    QStr = fields.at(0);
    if ((QStr[0] != '-')) if
       (QStr  != "PartPos") if
       (QStr  != "TEKLA") if
       (QStr  != "TITLE:") if
       (QStr  != "Assembly")
    {

        if (fields.size() == 4)
        {
            AAss                = new TeklaAssembly;
            AAss->ID            = Assembly_Count;
            AAss->Assemblypos   = fields[0];
            AAss->Quantity      = fields[1].toInt();
            AAss->Mainpart      = fields[2];
            AAss->Weight        = fields[3].toDouble();
            Part_list           = new std::vector<TeklaPart*>;
            AAss->Part_list     = Part_list;
            Assembly_Part_list.push_back(AAss);
            Assembly_Count++;
        }

        if (fields.size() == 6)
        {

        APart            = new TeklaPart;
        APart->PartPos   = fields[0];
        APart->Profile   = fields[2];
        APart->Quantity  = fields[1].toInt();
        APart->Material  = fields[3];
        APart->Length    = fields[4].toInt();
        APart->Weight    = fields[5].toDouble();
        APart->owner     = Assembly_Count-1;
        Part_list->push_back(APart);
    }
}
}

file.close();
 return Assembly_Part_list;
}
