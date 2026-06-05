#include "widget.h"
#include "./ui_widget.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QTableWidgetItem>
#include<QMessageBox>
#include <QDebug>
#include <QSqlError>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    hasInit = false;

    if (!QSqlDatabase::drivers().contains("QODBC")) {
        QMessageBox::critical(this, "Driver missing", "QODBC driver is not installed in this Qt kit");
        return;
    }

    const QString connectionName = "mysql_connection";
    QSqlDatabase db;
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

    ui->tableWidget->setColumnHidden(0, true);

    if (!db.open()) {
        QMessageBox::critical(this, "Database connection failed", "Database is not connected: " + db.lastError().text());
        return;
    }

    QMessageBox::information(this, "Database connected", "Database is connected");

    QSqlQuery query(db);
    if (query.exec("SELECT * FROM employee")) {
        while (query.next()) {
            QString id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString age = query.value(2).toString();
            QString email = query.value(3).toString();

            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

            QTableWidgetItem *idItem = new QTableWidgetItem(id);
            QTableWidgetItem *nameItem = new QTableWidgetItem(name);
            QTableWidgetItem *ageItem = new QTableWidgetItem(age);
            QTableWidgetItem *emailItem = new QTableWidgetItem(email);

            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, idItem);
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, nameItem);
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, ageItem);
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, emailItem);
        }
        hasInit = true;
    } else {
        QMessageBox::critical(this, "Error", "Cannot select data: " + query.lastError().text());
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    QSqlQuery query;
    if(hasInit) {
        QString id = ui->tableWidget->item(item->row() ,0)->data(0).toString();
        QString name = ui->tableWidget->item(item->row(), 1)->data(0).toString();
        QString age = QString::number(ui->tableWidget->item(item->row(), 2)->data(0).toInt());
        ui->tableWidget->item(item->row(), 2)->setData(0,age);

        QString email = ui->tableWidget->item(item->row(), 3)->data(0).toString();

        if(query.exec("UPDATE employee SET name = '" + name + "', age = '" + age + "', email = '" + email + "' WHERE id = " + id)) {
            QMessageBox::information(this, "Updated data", "Data is updated");

        }else {
            QMessageBox::information(this, "not updated", "Data is not updated");
        }
    } else {

    }
}

