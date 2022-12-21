#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{bool test=false;
 db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test_bd");
db.setUserName("eya_bkz");//inserer nom de l'utilisateur
db.setPassword("333");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection ::closeconnection() {db.close();}
