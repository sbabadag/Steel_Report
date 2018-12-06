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
#include <QFileDialog>

struct TeklaPart {
    QString PartPos;
    QString Profile;
    int Quantity;
    int mQuantity;
    QString Material;
    long Length;
    double Area;
    double Weight;
    unsigned int owner;
};

struct TeklaAssembly {
     int ID;
    QString Assemblypos;
    QString Profile;
     int Quantity;
     int mQuantity;
    double Weight;
    std::vector<TeklaPart*> *Part_list;
};


std::vector<TeklaPart*> ReadPartListFile(QString f)
{
QFile file(f);
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
        APart->PartPos           = fields[0];
        APart->Profile              = fields[1];
        APart->Quantity         = fields[2].toInt();
        APart->Material         = fields[3];
        APart->Length            = fields[4].toInt();
        APart->Area                = fields[5].toDouble();
        APart->Weight            = fields[6].toDouble();
        Part_list.push_back(APart);
    }
}

file.close();
 return Part_list;
}

std::vector<TeklaAssembly*> ReadAssemlyPartListFile(QString f)
{
QFile file(f);
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
            AAss->Profile      = fields[2];
            AAss->Weight        = fields[3].toDouble();
            Part_list           = new std::vector<TeklaPart*>;
            AAss->Part_list     = Part_list;
            Assembly_Part_list.push_back(AAss);
            Assembly_Count++;
        }

        if (fields.size() == 6)
        {

            APart                           = new TeklaPart;
            APart->PartPos          = fields[0];
            APart->Profile           = fields[2];
            APart->Quantity          = fields[1].toInt();
            APart->Material         = fields[3];
            APart->Length           = fields[4].toInt();
            APart->Weight           = fields[5].toDouble();
            APart->owner            = Assembly_Count-1;
            Part_list->push_back(APart);
    }
}
}

file.close();
 return Assembly_Part_list;
}

std::vector<TeklaPart*> profileList(QString f)
{
    QString Profile;
    std::vector<TeklaPart*> P,Pr;
    std::vector<QString> ExL;
    long Length = 0;
    double boyaalani1=0;
    double agirlik1=0;

    P = ReadPartListFile(f);
      for (unsigned int i=0;i<P.size();i++)
      {
          Profile = P[i]->Profile;
          {
              std::vector<QString>::iterator findIter = std::find(ExL.begin(),ExL.end(), Profile) ;
              if (findIter == ExL.end())
              {
                  for (unsigned int j=0;j<P.size();j++)
                  {
                      if (Profile == P[j]->Profile)
                      {
                          Length          += P[j]->Length*P[j]->Quantity;
                          boyaalani1     += P[j]->Area;
                          agirlik1           += P[j]->Weight*P[j]->Quantity;
                      }
                  }
                  ExL.push_back(Profile);
                  TeklaPart *T = new TeklaPart;
                  T->Profile = Profile;
                  T->Length= Length;
                  T->Area=boyaalani1;
                  T->Weight=agirlik1;
                  Pr.push_back(T);
                  Length = 0;
                 boyaalani1=0;
                  agirlik1 =0;
          }

     }
      }
      return Pr;
}




