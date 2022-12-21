#include "mainwindow.h"
#include <QApplication>
#include<connection.h>
#include<QMessageBox>
#include<QLineEdit>
#include "affaires_juridiques.h"
#include<QInputDialog>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator T;
    QStringList languages;
          languages <<"English"<<"French";
          const QString lang=QInputDialog::getItem(NULL,"Select language ","Language",languages);
          if (lang=="French")

        {
             T.load(":/new/prefix1/french.qm");
        }
        if (lang !="English")
        {
            a.installTranslator(&T);
        }

    Connection c;
    bool test=c.createconnection();//etablir la connexion
      MainWindow w;
    if (test) // si la connexion est etablie
    {  w.show();
        QMessageBox::information(nullptr,QObject::tr("database is open"),
                QObject::tr("connection successful.\n" "click cancel to exit"),QMessageBox::Cancel);

    }
   else
        //si la connexion a echoué
        QMessageBox::critical(nullptr,QObject::tr("data base is not open"), QObject::tr("connection failed.\n","click cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
