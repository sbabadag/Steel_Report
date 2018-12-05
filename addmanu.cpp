#include "addmanu.h"
#include "ui_addmanu.h"
#include <mainwindow.h>

Addmanu::Addmanu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addmanu)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Çatım");
    ui->comboBox->addItem("Kaynak");
    ui->comboBox->addItem("Boya");
    //
    ui->comboBox_2->addItem("Ali Kalender     - Formen");
    ui->comboBox_2->addItem("İbrahim Kaya   - Kaynakçı");
    ui->comboBox_2->addItem("Kamil Sönmez  - Çatımcı");
    ui->comboBox_2->addItem("Niyazi Sönmez - Boyacı");
    //
    catimtarih = QDate(1111,1,1);
    kaynaktarih = QDate(1111,1,1);
    boyatarih = QDate(1111,1,1);
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
    catimtarih = QDate(1111,1,1);
    kaynaktarih = QDate(1111,1,1);
    boyatarih = QDate(1111,1,1);

if (ui->comboBox->currentText()         == "Çatım") catimtarih = tarih; else
        if (ui->comboBox->currentText() == "Kaynak") kaynaktarih = tarih; else
        if (ui->comboBox->currentText() == "Boya") boyatarih = tarih;

imalatci = ui->comboBox_2->currentText();
uygunsuzluk = ui->lineEdit_2->text();
adet = (ui->lineEdit->text()).toInt();
tarih = ui->calendarWidget->selectedDate();


 SaveMyProduction();

}


