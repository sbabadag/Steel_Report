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

void initializeProjeModel(QSqlTableModel *projemodel)
{
    projemodel->setTable("proje");
    projemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    projemodel->select();

    projemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    projemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Proje Adı"));
    projemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("Başlangıç Tarihi"));
    projemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("Bitiş Tarihi"));
}

void initializeAssemblyModel(QSqlTableModel *assemblymodel)
{
    assemblymodel->setTable("assembly");
    assemblymodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    assemblymodel->select();

    assemblymodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Proje ID"));
    assemblymodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Assembly ID"));
    assemblymodel->setHeaderData(2, Qt::Horizontal, QObject::tr("Assembly Class"));
    assemblymodel->setHeaderData(3, Qt::Horizontal, QObject::tr("POZ"));
    assemblymodel->setHeaderData(4, Qt::Horizontal, QObject::tr("Adet"));
    assemblymodel->setHeaderData(5, Qt::Horizontal, QObject::tr("Ağırlık"));
    assemblymodel->setHeaderData(6, Qt::Horizontal, QObject::tr("Boya Alanı"));

}

void initializeAsspartsModel(QSqlTableModel *asspartsmodel)
{
    asspartsmodel->setTable("ass_parts");
    asspartsmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    asspartsmodel->select();

    asspartsmodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Proje ID"));
    asspartsmodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Part ID"));
    asspartsmodel->setHeaderData(2, Qt::Horizontal, QObject::tr("ID"));
    asspartsmodel->setHeaderData(3, Qt::Horizontal, QObject::tr("POZ"));
    asspartsmodel->setHeaderData(4, Qt::Horizontal, QObject::tr("Adet"));
    asspartsmodel->setHeaderData(5, Qt::Horizontal, QObject::tr("Ağırlık"));
    asspartsmodel->setHeaderData(6, Qt::Horizontal, QObject::tr("Boya Alanı"));

}

void initializeSingleModel(QSqlTableModel *singlemodel)
{
    singlemodel->setTable("single");
    singlemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    singlemodel->select();

    singlemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Proje ID"));
    singlemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
    singlemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("POZ"));
    singlemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("Profil"));
    singlemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("Adet"));
    singlemodel->setHeaderData(5, Qt::Horizontal, QObject::tr("Ağırlık"));
    singlemodel->setHeaderData(6, Qt::Horizontal, QObject::tr("Uzunluk"));
    singlemodel->setHeaderData(7, Qt::Horizontal, QObject::tr("Malzeme sınıfı"));
    singlemodel->setHeaderData(8, Qt::Horizontal, QObject::tr("Boya Alanı"));


}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    createConnection();

    projemodel    = new QSqlTableModel();
    assemblymodel = new  QSqlTableModel() ;
    asspartsmodel = new  QSqlTableModel() ;
    singlemodel   = new  QSqlTableModel() ;

    initializeProjeModel(projemodel);
    initializeAssemblyModel(assemblymodel);
    initializeAsspartsModel(asspartsmodel);
    initializeSingleModel(singlemodel);

  ui->tableView->setModel(projemodel);
  ui->tableView_2->setModel(assemblymodel);
  ui->tableView_3->setModel(asspartsmodel);
  ui->tableView_4->setModel(singlemodel);

  QObject::connect(ui->tableView_2->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
        this,SLOT(UpdateDetail(const QModelIndex &, const QModelIndex &)));

  //
  auto record = assemblymodel->record(0);
  int id = record.value("selfid").toInt();
  asspartsmodel->setFilter(QString("aid=%1").arg(id));
  ui->tableView_2->update();
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
            ui->tableView_2->update();



}
