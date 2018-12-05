#ifndef ADDMANU_H
#define ADDMANU_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class Addmanu;
}

class Addmanu : public QDialog
{
    Q_OBJECT

public:
    explicit Addmanu(QWidget *parent = nullptr);
    ~Addmanu();
    int adet;
    QString imalatci;
    QString uygunsuzluk;
    QDate tarih;
    QDate catimtarih;
    QDate kaynaktarih;
    QDate boyatarih;

    bool cr;
   const QModelIndex *mindex;

   signals:
   void SaveMyProduction();


private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_Addmanu_finished(int result);




private:
    Ui::Addmanu *ui;
};

#endif // ADDMANU_H

