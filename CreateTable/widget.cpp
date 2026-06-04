#include "widget.h"
#include "./ui_widget.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include <QDebug>
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName(
        "DRIVER={MySQL ODBC 9.7 Unicode Driver};"
        "SERVER=localhost;"
        "PORT=3306;"
        "DATABASE=testdb;"
        "USER=root;"
        "PASSWORD=root;"
        "OPTION=3;"
    );

    if (!db.open()) {
        ui->label->setText("Database is not connected: " + db.lastError().text());
    } else {
        QSqlQuery query;

        if (query.exec("CREATE TABLE users ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "firstname VARCHAR(20), "
                    "lastname VARCHAR(30), "
                    "age INT)")) {
            ui->label->setText("Table is created");
        } else {
            ui->label->setText("Query failed: " + query.lastError().text());
        }
    }

}

