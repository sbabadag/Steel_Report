#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <addmanu.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlTableModel *projemodel;
    QSqlTableModel *assemblymodel;
    QSqlTableModel *asspartsmodel;
    QSqlTableModel *singlemodel;
    QSqlTableModel *imalatmodel;
    Addmanu *Addmanudialog;
    QString PartFileName;
    QString AssemblyFileName;


    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString GetPartFileName();
    QString GetAssemblyFileName();
    void OpenProject();

public slots:
    void SaveProduction();




private slots:
    void UpdateDetail(const QModelIndex &a, const QModelIndex &b);



    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableView_2_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
