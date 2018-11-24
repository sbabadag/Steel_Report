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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void UpdateDetail(const QModelIndex &a, const QModelIndex &b);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
