#ifndef GESTIONAFF_H
#define GESTIONAFF_H
#include "arduino.h"
#include <QMainWindow>
#include "affaires_juridiques.h"
#include<QLineEdit>
#include <QDialog>

namespace Ui {
class gestionaff;
}

class gestionaff : public QDialog
{
    Q_OBJECT

public:
    explicit gestionaff(QWidget *parent = nullptr);
    ~gestionaff();

private slots:


    void on_pushButton_groupBox_clicked();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_Line_Edit_supp_cursorPositionChanged(int arg1, int arg2);

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_afficher_clicked();

    void on_pushButton_tri_clicked();

    void on_pushButton_imprimer_clicked();


    void on_pushButton_tri_2_clicked();

    void on_lineEdit_chercher_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_chercher_clicked();

    void on_lineEdit_chercher_textChanged(const QString &arg1);

    void on_on_pushButton_stat_clicked();

    void on_pushButton_submit_clicked();

    void on_pushButton_font_clicked();

    void on_calendarWidget_selectionChanged();

    void on_pushButton_stat_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_calendarWidget_activated(const QDate &date);

    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);



private:
 Arduino A;
 QByteArray data;
 Ui::gestionaff *ui;
   affaires_juridiques aff;
};



#endif // GESTIONAFF_H
