#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void addValues(int id, QString first, QString last, QString bd, double weight);

private:
    Ui::Dialog *ui;

    QSqlDatabase database;
    QSqlQueryModel *querymodel;

};
#endif // DIALOG_H
