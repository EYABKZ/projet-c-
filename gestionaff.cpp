#include "gestionaff.h"
#include "ui_gestionaff.h"
#include "affaires_juridiques.h"
#include<QMessageBox>
#include<QIntValidator>
#include<QLineEdit>
#include<QTextStream>
#include<QTextDocument>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include<QDialog>
#include<QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include<QFontDialog>
#include<QPieSeries>
gestionaff::gestionaff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionaff)
{

        ui->setupUi(this);
        int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
        ui->tableView->setModel(aff.afficher());

}

gestionaff::~gestionaff()
{
    delete ui;
}



void gestionaff::on_pushButton_groupBox_clicked()
{

}

void gestionaff::on_pushButton_supprimer_clicked()
{
     QString etat1=ui->Line_Edit_supp->text();
     int etat=etat1.toInt();
       bool test = aff.supprimer(etat);
       if (test)
       {    // ui->tableView->setModel(aff.afficher());
//A.write_to_arduino("1");
           QMessageBox::information(nullptr,QObject::tr("OK"),
            QObject::tr("suppression effectuée.\n" "click cancel to exit"),QMessageBox::Cancel);

       }
      else{
           //si la suppression a echoué
           QMessageBox::critical(nullptr,QObject::tr("NOT OK"), QObject::tr("suppression non effectuée.\n","click cancel to exit."),QMessageBox::Cancel);

      ui->tableView->setModel(aff.afficher());
     // A.write_to_arduino("2");}

}}

void gestionaff::on_pushButton_ajouter_clicked()
{
  int num_affaires=ui->lineEdit_affaires->text().toInt();
  QString type=ui->lineEdit_type->text();
  QString date_creation=ui->lineEdit_date1->text();
  QString date_traitement=ui->lineEdit_date2->text();
  QString etat=ui->lineEdit_etat->text();


  affaires_juridiques aff(num_affaires,type,date_creation,date_traitement,etat);
   bool test=aff.ajouter();
   if(test)
   {
       QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tableView->setModel(aff.afficher());


   }
   else{
       QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                             QObject::tr("Ajout non effectué.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
  // A.write_to_arduino("4");
   }

}

//void MainWindow::on_Line_Edit_supp_cursorPositionChanged(int arg1, int arg2)
//{

//}

void gestionaff::on_pushButton_afficher_clicked()
{


    QSqlQueryModel * modal = new QSqlQueryModel();
    modal->setQuery("select * from AFFAIRES ");
    ui->tableView->setModel(modal);
}


void gestionaff::on_pushButton_modifier_clicked()
{
      int num_affaires=ui->lineEdit_modif->text().toInt();
      QString type=ui->lineEdit_jdid->text();

        affaires_juridiques aff (num_affaires,type);
         bool test=aff.modifier(type,num_affaires);
            if(test)
            {
                ui->tableView->setModel(aff.afficher());
                QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Modification avec succes.\n" "Click Close to exit."), QMessageBox::Close);
               // A.write_to_arduino("5");
                ui->tabWidget->setCurrentIndex(1);
;

            }
            else{
                QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("Modification echoue.\n" "Click Close to exit."), QMessageBox::Close);
          //  A.write_to_arduino("6");}

}}


void gestionaff::on_pushButton_tri_clicked()
{
   affaires_juridiques aff;

//   ui->tableView->setModel(aff.afficher());
   bool test=aff.triernum_affaires();

       if(test)
       {
          // ui->tableView->setModel(aff.afficher());
            ui->tableView->setModel(aff.triernum_affaires());
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("le tri est effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
      else
           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("tri non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

}



void gestionaff::on_calendarWidget_selectionChanged()
{
    QString x=ui->calendarWidget->selectedDate().toString();
    ui->lineEdit_calendar->setText(x);
    ui->tableView_3->setModel(aff.afficher_calendar(x));

}
void gestionaff::on_pushButton_imprimer_clicked()
{ QString strStream;
    QTextStream out(&strStream);
    QImage pic (":/pic/Log1");
    QImage pic2 (":/pic/Logo");

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;
    QPainter painter;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}


void gestionaff::on_lineEdit_chercher_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit_chercher->text();

    if(text.isEmpty())
    {
        aff.afficher();

    }
    else
    {
        qry->prepare("select * from AFFAIRES where ( num_affaires LIKE'%"+text+"%' OR type LIKE'%"+text+"%' OR date_creation LIKE'%"+text+"%'OR date_traitement LIKE'%"+text+"%' ) ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
    }
}


void gestionaff::on_on_pushButton_stat_clicked()
{   // stat=new stat_combo();
      //  stat->choix_pie();
       // stat->show();

}

void gestionaff::on_pushButton_submit_clicked()
{
    QMessageBox::information (NULL,tr("Message"),tr ("USER %1 submitted a message with the title %2. The message is %3")
                              .arg(ui->lineEdit_affaires->text())
                              .arg(ui->lineEdit_type->text())
                              .arg(ui->lineEdit_date1->text())
                              .arg(ui->lineEdit_date2->text())
                              .arg(ui->lineEdit_etat->text()));


}

void gestionaff::on_pushButton_font_clicked()
{
    bool ok;
      QFont font = QFontDialog::getFont(
                      &ok, QFont("Helvetica [Cronyx]", 10), this);
      if (ok) {
          // the user clicked OK and font is set to the font the user selected
      } else {
          // the user canceled the dialog; font is set to the initial
          // value, in this case Helvetica [Cronyx], 10
      }


}


void gestionaff::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString response;
    response = ui->tableView->model()->index(index.row(),4).data().toString();
    if ( response == "en cours")
        A.write_to_arduino("1");
    else
        A.write_to_arduino("2");
}



