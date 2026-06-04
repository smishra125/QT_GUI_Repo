#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QSqlDatabase>
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
    qDebug() << QSqlDatabase::drivers();

    if (!QSqlDatabase::drivers().contains("QODBC")) {
        ui->label->setText("QODBC driver is not installed in this Qt kit");
        return;
    }

    QSqlDatabase mysqldb;
    const QString connectionName = "mysql_connection";

    if (QSqlDatabase::contains(connectionName)) {
        mysqldb = QSqlDatabase::database(connectionName);
    } else {
        mysqldb = QSqlDatabase::addDatabase("QODBC", connectionName);
    }

    mysqldb.setDatabaseName(
        "DRIVER={MySQL ODBC 9.7 Unicode Driver};"
        "SERVER=127.0.0.1;"
        "PORT=3306;"
        "DATABASE=engineeringhub_db;"
    );
    mysqldb.setUserName("root");
    mysqldb.setPassword("root");

    if (!mysqldb.open()) {
        ui->label->setText("Database is not connected: " + mysqldb.lastError().text());
    } else {
        ui->label->setText("Database is connected");
    }
}

