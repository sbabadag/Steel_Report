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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString GetPartFileName();
    QString GetAssemblyFileName();
    void OpenProject();




private slots:
    void UpdateDetail(const QModelIndex &a, const QModelIndex &b);


    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
