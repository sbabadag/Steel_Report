#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>
#include "connection.h"
#include <QSqlRecord>
#include <QItemSelectionModel>

QString MainWindow::GetPartFileName()
{
    QString Part_filename = QFileDialog::getOpenFileName(this,
                                                         tr("Part File dosyası aç..."), "",
                                                         tr("Tekla part files (*.xsr);;All Files (*)"));
    return Part_filename;
}

QString MainWindow::GetAssemblyFileName()
{
    QString Ass_filename = QFileDialog::getOpenFileName(this,
                                                         tr("Assemly-Part list dosyası aç..."), "",
                                                         tr("Tekla Ass-Part files  (*.xsr);;All Files (*)"));
    return Ass_filename;
}


void initializeProjeModel(QSqlTableModel *projemodel)
{
    projemodel->setTable("proje");
    projemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    projemodel->select();

    projemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    projemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Proje Adı"));
    projemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("Başlangıç Tarihi"));
    projemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("Bitiş Tarihi"));
    projemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("Dosyalar"));


}

void initializeAssemblyModel(QSqlTableModel *assemblymodel)
{
    assemblymodel->setTable("assembly");
    assemblymodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    assemblymodel->select();

    assemblymodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Proje ID"));
    assemblymodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Assembly ID"));
    assemblymodel->setHeaderData(2, Qt::Horizontal, QObject::tr("Assembly POZU"));
    assemblymodel->setHeaderData(3, Qt::Horizontal, QObject::tr("Profil"));
    assemblymodel->setHeaderData(4, Qt::Horizontal, QObject::tr("Adet"));
    assemblymodel->setHeaderData(5, Qt::Horizontal, QObject::tr("Üretilen Adet"));
    assemblymodel->setHeaderData(6, Qt::Horizontal, QObject::tr("Ağırlık"));
    assemblymodel->setHeaderData(7, Qt::Horizontal, QObject::tr("Çatım Tarihi"));
    assemblymodel->setHeaderData(8, Qt::Horizontal, QObject::tr("Kaynak Tarihi"));
    assemblymodel->setHeaderData(9, Qt::Horizontal, QObject::tr("Boya Tarihi"));
    assemblymodel->setHeaderData(10, Qt::Horizontal, QObject::tr("İmalatçı"));
    assemblymodel->setHeaderData(11, Qt::Horizontal, QObject::tr("Uygunsuzluk"));


}

void initializeAsspartsModel(QSqlTableModel *asspartsmodel)
{
    asspartsmodel->setTable("ass_parts");
    asspartsmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    asspartsmodel->select();

    asspartsmodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Proje ID"));
    asspartsmodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Ass-Part ID"));
    asspartsmodel->setHeaderData(2, Qt::Horizontal, QObject::tr("Part ID"));
    asspartsmodel->setHeaderData(3, Qt::Horizontal, QObject::tr("Part Pozu"));
    asspartsmodel->setHeaderData(4, Qt::Horizontal, QObject::tr("Profil"));
    asspartsmodel->setHeaderData(5, Qt::Horizontal, QObject::tr("Adet"));
    asspartsmodel->setHeaderData(6, Qt::Horizontal, QObject::tr("Üretilen Adet"));
    asspartsmodel->setHeaderData(7, Qt::Horizontal, QObject::tr("Ağırlık"));
    asspartsmodel->setHeaderData(8, Qt::Horizontal, QObject::tr("Boya Alanı"));
    asspartsmodel->setHeaderData(9, Qt::Horizontal, QObject::tr("Kesim Tarihi"));

}

void initializeSingleModel(QSqlTableModel *singlemodel)
{
    singlemodel->setTable("single");
    singlemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    singlemodel->select();

    singlemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Proje ID"));
    singlemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Part ID"));
    singlemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("POZ"));
    singlemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("Profil"));
    singlemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("Adet"));
    singlemodel->setHeaderData(5, Qt::Horizontal, QObject::tr("Üretilen Adet"));
    singlemodel->setHeaderData(6, Qt::Horizontal, QObject::tr("Ağırlık"));
    singlemodel->setHeaderData(7, Qt::Horizontal, QObject::tr("Uzunluk"));
    singlemodel->setHeaderData(8, Qt::Horizontal, QObject::tr("Malzeme sınıfı"));
    singlemodel->setHeaderData(9, Qt::Horizontal, QObject::tr("Boya Alanı"));
}
void initializeImalatModel(QSqlTableModel *imalatmodel)
{
    imalatmodel->setTable("imalat");
    imalatmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    imalatmodel->select();

    imalatmodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Proje ID"));
    imalatmodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Ass. ID"));
    imalatmodel->setHeaderData(2, Qt::Horizontal, QObject::tr("Adet"));
    imalatmodel->setHeaderData(3, Qt::Horizontal, QObject::tr(" ASSEMBLY POZ"));
    imalatmodel->setHeaderData(4, Qt::Horizontal, QObject::tr("Çatım tarih"));
    imalatmodel->setHeaderData(5, Qt::Horizontal, QObject::tr("Kaynak tarihi"));
    imalatmodel->setHeaderData(6, Qt::Horizontal, QObject::tr("Boya tarihi"));
    imalatmodel->setHeaderData(7, Qt::Horizontal, QObject::tr("Uygunsuzluk"));
    imalatmodel->setHeaderData(8, Qt::Horizontal, QObject::tr("İmalatı yapan"));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    Addmanudialog = new Addmanu();
    createConnection();

    projemodel    = new QSqlTableModel();
    initializeProjeModel(projemodel);
    ui->tableView->setModel(projemodel);
    ui->tableView->setIndexWidget(projemodel->index(0,4), ui->pushButton);

  //
//  auto record = assemblymodel->record(0);
//  int id = record.value("selfid").toInt();
//  asspartsmodel->setFilter(QString("aid=%1").arg(id));
}

void  MainWindow::OpenProject()
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
    }
    QSqlQuery query;



auto P = ReadPartListFile(GetPartFileName());
auto A = ReadAssemlyPartListFile(GetAssemblyFileName());

for (unsigned int i=0; i<P.size();i++)
{
    QString str = QString("insert into single values(0,%1,'%2','%3',%4,0,%5,%6,'%7',%8)").arg(i).arg(P[i]->PartPos).arg(P[i]->Profile).arg(P[i]->Quantity).arg(P[i]->Weight).arg(P[i]->Length).arg(P[i]->Material).arg(P[i]->Area);
   query.exec(str);
}

//

for (unsigned int i=0; i<A.size();i++)
{
    QString str = QString("insert into assembly values(0,%1,'%2','%3',%4,0,%5,'01-01-2000','01-01-2000','01-01-2000',' ',' ')").arg(A[i]->ID).arg(A[i]->Assemblypos).arg(A[i]->Profile).arg(A[i]->Quantity).arg(A[i]->Weight);
   query.exec(str);
   //
    auto PP = A[i]->Part_list;
    for (unsigned int j=0; j<PP->size();j++)
    {
        QString str = QString("insert into ass_parts values(0,%1,%2,'%3','%4',%5,0,%6,%7,'01-01-2000')").arg(PP->at(j)->owner).arg(j).arg(PP->at(j)->PartPos).arg(PP->at(j)->Profile).arg(PP->at(j)->Quantity).arg(PP->at(j)->Weight).arg(PP->at(j)->Weight);
        query.exec(str);

    }
}
assemblymodel = new  QSqlTableModel() ;
asspartsmodel = new  QSqlTableModel() ;
singlemodel   = new  QSqlTableModel() ;
imalatmodel = new  QSqlTableModel() ;

initializeAssemblyModel(assemblymodel);
initializeAsspartsModel(asspartsmodel);
initializeSingleModel(singlemodel);
initializeImalatModel(imalatmodel);

ui->tableView_2->setModel(assemblymodel);
ui->tableView_3->setModel(asspartsmodel);
ui->tableView_4->setModel(singlemodel);
ui->tableView_5->setModel(imalatmodel);

//
ui->tableView_2->hideColumn(0);
ui->tableView_2->hideColumn(1);
ui->tableView_3->hideColumn(0);
ui->tableView_3->hideColumn(1);
ui->tableView_3->hideColumn(2);
ui->tableView->hideColumn(0);


QObject::connect(ui->tableView_2->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
      this,SLOT(UpdateDetail(const QModelIndex &, const QModelIndex &)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateDetail(const QModelIndex &a, const QModelIndex &b)
{
            auto record = assemblymodel->record(a.row());
            int id = record.value("selfid").toInt();
            asspartsmodel->setFilter(QString("aid=%1").arg(id));
            //
            imalatmodel->setFilter(QString("selfid=%1").arg(id));
}

void MainWindow::on_pushButton_clicked()
{
    OpenProject();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    assemblymodel->setFilter(QString("poz like '%%1%'").arg(arg1));
}

void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    Addmanudialog->show();
    if (Addmanudialog->cr)
    {
    QSqlRecord *r = new QSqlRecord();
    QSqlRecord a = assemblymodel->record(index.row());


    r->setValue("adet", Addmanudialog->boyaadet);
    r->setValue("selfid", a.fieldName(1));

    imalatmodel->insertRecord(imalatmodel->rowCount(),*r);
    ui->tableView_2->update();
    Addmanudialog->cr = false;
    }
}
