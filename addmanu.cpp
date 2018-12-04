#include "addmanu.h"
#include "ui_addmanu.h"
#include <mainwindow.h>

Addmanu::Addmanu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addmanu)
{
    ui->setupUi(this);
}

Addmanu::~Addmanu()
{
    delete ui;
}

void Addmanu::on_buttonBox_accepted()
{

}

void Addmanu::on_buttonBox_rejected()
{
}

void Addmanu::on_Addmanu_finished(int result)
{
 catimadet = ui->lineEdit->text().toInt();
 kaynakadet = ui->lineEdit_2->text().toInt();
 boyaadet = ui->lineEdit_3->text().toInt();
 SaveMyProduction();
}


