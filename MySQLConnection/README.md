# Qt MySQL Connection Using ODBC

This project connects a Qt Widgets application to a MySQL database using Qt's SQL module and the Windows MySQL ODBC driver.

## Requirements

- MySQL Server running locally or on a reachable host
- MySQL Workbench or another MySQL client to verify the database
- Qt 6 kit with the `Sql` module enabled
- MySQL Connector/ODBC 64-bit installed on Windows

This project uses `QODBC` because the installed Qt kit does not include the native `QMYSQL` driver.

## 1. Verify Qt SQL Drivers

In `widget.cpp`, this line prints the SQL drivers available in the current Qt kit:

```cpp
qDebug() << QSqlDatabase::drivers();
```

For this project, Qt reported:

```text
QIBASE QSQLITE QMIMER QOCI QODBC QPSQL
```

Because `QMYSQL` was not listed, the project uses:

```cpp
QSqlDatabase::addDatabase("QODBC");
```

## 2. Install MySQL ODBC Driver

Install the 64-bit MySQL Connector/ODBC driver from:

```text
https://dev.mysql.com/downloads/connector/odbc/
```

After installation, check the exact driver name from Command Prompt:

```cmd
powershell -Command "Get-ItemProperty -Path 'HKLM:\SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers'"
```

This project found:

```text
MySQL ODBC 9.7 Unicode Driver : Installed
```

The driver name must match exactly in the Qt connection string.

## 3. Link Qt SQL In CMake

`CMakeLists.txt` must include the Qt SQL module:

```cmake
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)
```

And the target must link against `Qt::Sql`:

```cmake
target_link_libraries(1-SqliteConnection PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)
```

## 4. Include Required Qt Headers

`widget.cpp` needs:

```cpp
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
```

`QSqlError` is required when using:

```cpp
mysqldb.lastError().text()
```

## 5. Connect To MySQL

The working connection code is:

```cpp
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
```

Update these values for your own MySQL setup:

```text
SERVER=127.0.0.1
PORT=3306
DATABASE=engineeringhub_db
UserName=root
Password=root
```

## 6. Verify The Database Name

In MySQL Workbench, run:

```sql
SHOW DATABASES;
```

Use the exact database/schema name in the Qt connection string:

```cpp
"DATABASE=engineeringhub_db;"
```

## Common Errors

### QMYSQL driver is not installed

Error:

```text
QSqlDatabase: can not load requested driver 'QMYSQL'
```

Fix:

Use `QODBC`, or install/build Qt's native MySQL plugin `qsqlmysql.dll`.

### Data source name not found

Error:

```text
Data source name not found and no default driver specified
```

Fix:

Install MySQL Connector/ODBC and make sure the `DRIVER={...}` name matches the installed driver exactly.

Example:

```cpp
"DRIVER={MySQL ODBC 9.7 Unicode Driver};"
```

### Unknown database

Error:

```text
Unknown database 'database_name'
```

Fix:

Check the database name in MySQL Workbench:

```sql
SHOW DATABASES;
```

Then update:

```cpp
"DATABASE=correct_database_name;"
```

### Duplicate connection name

Error:

```text
duplicate connection name 'qt_sql_default_connection'
```

Fix:

Use a named connection and reuse it:

```cpp
const QString connectionName = "mysql_connection";

if (QSqlDatabase::contains(connectionName)) {
    mysqldb = QSqlDatabase::database(connectionName);
} else {
    mysqldb = QSqlDatabase::addDatabase("QODBC", connectionName);
}
```

## Notes

MySQL Workbench is only a client application. The Qt app does not connect to Workbench directly. Both Workbench and Qt connect to the MySQL Server using the same host, port, database, username, and password.
