#ifndef ADDMANU_H
#define ADDMANU_H

#include <QDialog>

namespace Ui {
class Addmanu;
}

class Addmanu : public QDialog
{
    Q_OBJECT

public:
    explicit Addmanu(QWidget *parent = nullptr);
    ~Addmanu();
    int kaynakadet;
    int catimadet;
    int boyaadet;
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

