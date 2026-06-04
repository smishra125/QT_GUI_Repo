# Qt MySQL Insert Data Project

This Qt Widgets project connects to a MySQL database and inserts user data into a `users` table. The form collects first name, last name, and age, then saves the record to MySQL using Qt SQL and the Windows MySQL ODBC driver.

## Screenshot

![Insert data success](assets/insert-data-success.png)

## Requirements

- Qt 6 with the `Sql` module
- MySQL Server running
- MySQL Workbench or another MySQL client
- MySQL Connector/ODBC 64-bit for Windows
- A MySQL database named `engineeringhub_db`
- A table named `users`

This project uses `QODBC` because this Qt kit does not include the native `QMYSQL` driver.

## Database Setup

Create or select the database in MySQL Workbench:

```sql
CREATE DATABASE IF NOT EXISTS engineeringhub_db;
USE engineeringhub_db;
```

Create the `users` table:

```sql
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    firstname VARCHAR(100) NOT NULL,
    lastname VARCHAR(100) NOT NULL,
    age INT NOT NULL
);
```

You can verify the table with:

```sql
SELECT * FROM users;
```

## Install MySQL ODBC Driver

Install MySQL Connector/ODBC 64-bit from:

```text
https://dev.mysql.com/downloads/connector/odbc/
```

Check the installed ODBC driver name from Command Prompt:

```cmd
powershell -Command "Get-ItemProperty -Path 'HKLM:\SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers'"
```

This project uses:

```text
MySQL ODBC 9.7 Unicode Driver
```

The driver name in the Qt connection string must match exactly.

## CMake Setup

`CMakeLists.txt` must find the Qt SQL module:

```cmake
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)
```

The target must link `Qt::Sql`:

```cmake
target_link_libraries(1-SqliteConnection PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)
```

## Required Includes

Use these headers in `widget.cpp`:

```cpp
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
```

## Insert Data Code

Use `QODBC` and the MySQL ODBC connection string:

```cpp
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
        "DATABASE=engineeringhub_db;"
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
```

## How It Works

1. The app checks or creates a named database connection called `mysql_connection`.
2. Qt connects through `QODBC`.
3. The ODBC connection string points to the local MySQL server.
4. The form values are read from `lineEditFirst`, `lineEditLast`, and `lineEditAge`.
5. A prepared `INSERT` query saves the data into the `users` table.
6. The input fields are cleared after a successful insert.

## Common Errors

### QMYSQL Driver Not Installed

Error:

```text
QSqlDatabase: can not load requested driver 'QMYSQL'
```

Fix:

Use `QODBC`, or install/build the native Qt MySQL plugin `qsqlmysql.dll`.

### Data Source Name Not Found

Error:

```text
Data source name not found and no default driver specified
```

Fix:

Install MySQL Connector/ODBC and make sure the driver name matches exactly:

```cpp
"DRIVER={MySQL ODBC 9.7 Unicode Driver};"
```

### Unknown Database

Error:

```text
Unknown database 'database_name'
```

Fix:

Check the database name in MySQL Workbench:

```sql
SHOW DATABASES;
```

Then update the connection string:

```cpp
"DATABASE=engineeringhub_db;"
```

### Table Does Not Exist

Error:

```text
Table 'engineeringhub_db.users' doesn't exist
```

Fix:

Create the `users` table using the SQL in the Database Setup section.

## Note

MySQL Workbench is only a client application. The Qt app connects to the MySQL Server using the same server, port, database, username, and password.
