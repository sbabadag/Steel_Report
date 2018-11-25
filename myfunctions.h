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
