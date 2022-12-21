#ifndef AFFAIRES_JURIDIQUES_H
#define AFFAIRES_JURIDIQUES_H
#include<QSqlQuery>
#include<QString>
#include <QSqlQueryModel>
//#include"mainwindow.h"
#include<QLabel>
#include<QLineEdit>

class affaires_juridiques
{
public:
    affaires_juridiques();
    affaires_juridiques(int,QString);
    affaires_juridiques(int,QString,QString,QString,QString) ;
    int getnum_affaires();
    QString gettype();
    QString getdate_creation();
    QString getdate_traitement();
    QString getetat();

    void setnum_affaires(int);
    void settype(QString);
    void setdate_creation(QString);
    void setdate_traitement(QString);
    void setetat(QString);

    bool ajouter();
    bool supprimer(int);
    bool modifier(QString,int);
    QSqlQueryModel*afficher();
     QSqlQueryModel*chercher(QString);

     QSqlQueryModel * triernum_affaires();
    QSqlQueryModel * afficher_calendar(QString x);


private:
    int num_affaires;
    QString type;
    QString date_creation;
    QString date_traitement;
    QString etat;


};



#endif // AFFAIRES_JURIDIQUES_H
