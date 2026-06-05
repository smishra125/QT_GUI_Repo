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
        ui->label_2->setText("QODBC driver is not installed in this Qt kit");
        return;
    }

    QSqlDatabase db;
    const QString connectionName = "mysql_delete_connection";

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
        QString id = ui->lineEditRow->text().trimmed();

        bool isValidId = false;
        int employeeId = id.toInt(&isValidId);

        if (!isValidId) {
            ui->label_2->setText("Please enter a valid numeric row id");
            return;
        }

        QSqlQuery query(db);
        query.prepare("DELETE FROM employee WHERE id = ?");
        query.addBindValue(employeeId);

        if(query.exec()) {
            if (query.numRowsAffected() > 0) {
                ui->label_2->setText("Data is deleted");
            } else {
                ui->label_2->setText("No employee found with this id");
            }
        }else {
            ui->label_2->setText("Data is not deleted: " + query.lastError().text());
        }

    }else {
        ui->label_2->setText("Database is not connected: " + db.lastError().text());
    }

}
