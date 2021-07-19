#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("/usr/local/lib/C++Project/database/database2.sqlite");

    if (database.open())
    {
        qDebug() << "Successful";
    }
    else
    {
        QMessageBox::information(this,"Failed","Connection Failed");
    }

    QString query = " CREATE TABLE IF NOT EXISTS AutoDbTable ("
                        "ID integer,"
                        "FirstName VARCHAR(20),"
                        "LastName VARCHAR(20),"
                        "Birthdate DATETIME,"
                        "weight double);";

//    QString query = " CREATE TABLE IF NOT EXISTS AutoDbTable ("
//                        "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
//                        " picture INTEGER NOT NULL,"
//                        " video INTEGER NOT NULL,"
//                        " program VARCHAR(50) NOT NULL,"
//                        " position FLOAT NOT NULL,"
//                        " height FLOAT NOT NULL,"
//                        " angle FLOAT NOT NULL")"

    QSqlQuery qry1;
    if (!qry1.exec(query))
    {
        qDebug() << "Query Create Failled";
    }

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("AutoDbTable");
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
//    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
//    model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0); // don't show the ID
//    ui->tableView->show();

    addValues(1,"Bob","Bobby","01-04-1943",102.4);
    addValues(2,"John","Johnson","07-24-2019",95.8);
}

void Dialog::addValues(int id, QString first, QString last, QString bd, double weight)
{
     QSqlQuery qry2;

     qry2.prepare("INSERT INTO AutoDbTable ("
                "ID,"
                "FirstName,"
                "LastName,"
                "Birthdate,"
                "Weight)"
                "VALUES (?,?,?,?,?);");

     qry2.addBindValue(id);
     qry2.addBindValue(first);
     qry2.addBindValue(last);
     qry2.addBindValue(QDateTime::fromString(bd,"mm-dd-yyyy"));
     qry2.addBindValue(weight);

     if (!qry2.exec())
     {
         qDebug() << "Query Add Failled";
     }

     qDebug() << "Done";
}

Dialog::~Dialog()
{
    delete ui;
    database.close();
}


