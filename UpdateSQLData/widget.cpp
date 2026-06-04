#include "widget.h"
#include "./ui_widget.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    if (!QSqlDatabase::drivers().contains("QODBC")) {
        ui->labelResult->setText("QODBC driver is not installed in this Qt kit");
        return;
    }

    QSqlDatabase db;
    const QString connectionName = "mysql_update_connection";

    if (QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
    } else {
        db = QSqlDatabase::addDatabase("QODBC", connectionName);
    }

    db.setDatabaseName(
        "DRIVER={MySQL ODBC 9.7 Unicode Driver};"
        "SERVER=127.0.0.1;"
        "PORT=3306;"
        "DATABASE=testdb;"
    );
    db.setUserName("root");
    db.setPassword("root");

    if(db.open()) {
        QString id = ui->lineEditId->text().trimmed();
        QString name = ui->lineEditName->text().trimmed();
        QString age = ui->lineEditAge->text().trimmed();
        QString email = ui->lineEditEmail->text().trimmed();

        QSqlQuery query(db);
        query.prepare("UPDATE employee "
                      "SET name = :name, age = :age, email = :email "
                      "WHERE id = :id");
        query.bindValue(":name", name);
        query.bindValue(":age", age);
        query.bindValue(":email", email);
        query.bindValue(":id", id);

        if(query.exec()){
            ui->labelResult->setText("Data is updated");
        } else {
            ui->labelResult->setText("Data is not updated: " + query.lastError().text());
        }

    } else {
        ui->labelResult->setText("Database is not connected: " + db.lastError().text());
    }

}

