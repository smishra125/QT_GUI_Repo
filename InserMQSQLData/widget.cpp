#include "widget.h"
#include "./ui_widget.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include <QSqlError>

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
    QSqlDatabase db;

    const QString connectionName = "mysql_connection";

    if (QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
    } else {
        db = QSqlDatabase::addDatabase("QODBC", connectionName);

        db.setDatabaseName(
            "DRIVER={MySQL ODBC 9.7 Unicode Driver};"
            "SERVER=127.0.0.1;"
            "PORT=3306;"
            "DATABASE=testdb;"
        );

        db.setUserName("root");
        db.setPassword("root");
    }

    if (!db.open()) {
        QMessageBox::information(
            this,
            "Database error",
            "Database is not connected: " + db.lastError().text()
        );
    } else {
        QString firstname = ui->lineEditFirst->text();
        QString lastname = ui->lineEditLast->text();
        QString age = ui->lineEditAge->text();

        QSqlQuery query(db);
        query.prepare("INSERT INTO users (firstname, lastname, age) VALUES (?, ?, ?)");
        query.addBindValue(firstname);
        query.addBindValue(lastname);
        query.addBindValue(age.toInt());

        if (!query.exec()) {
            QMessageBox::information(
                this,
                "Insert error",
                "Data was not added: " + query.lastError().text()
            );
            return;
        }

        QMessageBox::information(this, "Database added", "Data added to database");

        ui->lineEditFirst->clear();
        ui->lineEditLast->clear();
        ui->lineEditAge->clear();
    }

}

