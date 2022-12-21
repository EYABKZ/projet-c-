#include "affaires_juridiques.h"
#include <QString>
#include <QSqlQuery>
#include<QSqlError>
#include <QDebug>
#include <QObject>
#include<QMessageBox>
#include<QSqlError>
#include<QObject>
#include<QLineEdit>



affaires_juridiques::affaires_juridiques()
{
   num_affaires=0;
   date_creation=" "; date_traitement=" "; type=" "; etat=" ";

}
affaires_juridiques::affaires_juridiques(int num_affaires,QString type)
{
 this-> num_affaires=num_affaires;
 this->type=type;
}

 affaires_juridiques::affaires_juridiques(int num_affaires,QString type,QString date_creation,QString date_traitement,QString etat)
{ this->num_affaires=num_affaires;this->type=type;this->date_creation=date_creation;this->date_traitement=date_traitement;this->etat=etat;}
    int affaires_juridiques:: getnum_affaires() {return num_affaires;}
    QString affaires_juridiques::gettype() {return type;}
    QString affaires_juridiques::getdate_creation() {return date_creation;}
    QString affaires_juridiques:: getdate_traitement(){return date_traitement;}
    QString affaires_juridiques:: getetat(){return etat;}

    void affaires_juridiques:: setnum_affaires(int num_affaires){this->num_affaires=num_affaires;}
    void affaires_juridiques:: settype(QString type) {this->type=type;}
    void affaires_juridiques::setdate_creation(QString date_creation){this->date_creation=date_creation;}
    void affaires_juridiques::setdate_traitement(QString date_traitement) {this->date_traitement=date_traitement;}
    void affaires_juridiques::setetat(QString etat){this->etat=etat;}


    bool affaires_juridiques::ajouter()
    {
        QSqlQuery query;
        QString num_affaires_String=QString::number(num_affaires);

        query.prepare("INSERT INTO AFFAIRES(NUM_AFFAIRES, TYPE, DATE_CREATION,DATE_TRAITEMENT,ETAT) "
                      "VALUES ('"+num_affaires_String+"',:type,:date_creation,:date_traitement,:etat )");
        query.bindValue(":type", type);
        query.bindValue(":date_creation", date_creation);
         query.bindValue(":date_traitement",date_traitement);
         query.bindValue(":etat",etat);


    return query.exec();
    }


   bool affaires_juridiques::modifier(QString type,int num_affaires)
    {
        QSqlQuery query;
        query.prepare("UPDATE AFFAIRES SET NUM_AFFAIRES = :num_affaires ,TYPE=:type WHERE NUM_AFFAIRES = :num_affaires");
        query.bindValue(":num_affaires", num_affaires);
        query.bindValue(":type",type);

        return query.exec();
    }
   bool affaires_juridiques::supprimer(int num_affaires)
    {   QSqlQuery query;
        QString cin_citoyen_String=QString::number(num_affaires);
        query.prepare("DELETE FROM AFFAIRES WHERE NUM_AFFAIRES= :num_affaires");
        query.bindValue(0,num_affaires);
        return query.exec();
  }

    QSqlQueryModel * affaires_juridiques::afficher()

   {  QSqlQueryModel * model=new QSqlQueryModel ();

    model->setQuery("SELECT * FROM AFFAIRES");

  return model;

    }

    //Trie Par num_affaires
    QSqlQueryModel * affaires_juridiques::triernum_affaires()
    {          QSqlQuery * q = new  QSqlQuery ();
               QSqlQueryModel * model = new  QSqlQueryModel ();
               q->prepare("SELECT * FROM AFFAIRES order by NUM_AFFAIRES");
               q->exec();
               model->setQuery(*q);
               return model;
    }

    QSqlQueryModel * affaires_juridiques::afficher_calendar(QString x)
     {
         QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from AFFAIRES where DATE_TRAITEMENT like '%"+x+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_AFFAIRES"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_CREATION"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_TRAITEMENT"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
      return model;
     }


