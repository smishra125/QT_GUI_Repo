# CreateTable

A small Qt Widgets application that connects to a MySQL database through Qt SQL/ODBC and creates a `users` table when the button is clicked.

## Features

- Qt Widgets desktop UI
- CMake-based Qt project
- Uses `Qt::Sql`
- Connects to MySQL using the `QODBC` driver
- Creates a `users` table with `id`, `firstname`, `lastname`, and `age` columns

## Requirements

- Qt 6 or Qt 5 with the Widgets and SQL modules
- CMake 3.5 or newer
- A C++17 compiler
- MySQL Server
- MySQL Workbench, optional but useful for managing the database
- MySQL ODBC Connector installed on Windows

## Database Setup

Create a database/schema in MySQL before running the app. The current code expects:

```sql
CREATE DATABASE testdb;
```

The app currently connects using these values in `widget.cpp`:

```cpp
SERVER=localhost;
PORT=3306;
DATABASE=testdb;
USER=root;
PASSWORD=root;
```

Change these values if your MySQL username, password, port, or database name is different.

## ODBC Driver Setup

This project uses Qt's `QODBC` driver because the installed Qt kit does not include the `QMYSQL` driver.

Make sure the MySQL ODBC Connector is installed and that the driver name in `widget.cpp` matches the exact driver name on your system:

```cpp
DRIVER={MySQL ODBC 9.7 Unicode Driver};
```

To check the installed driver name on Windows:

1. Open **ODBC Data Sources (64-bit)**.
2. Go to the **Drivers** tab.
3. Find the MySQL Unicode driver name.
4. Copy that exact name into the `DRIVER={...}` part of the connection string.

Common driver names include:

```text
MySQL ODBC 8.0 Unicode Driver
MySQL ODBC 9.3 Unicode Driver
MySQL ODBC 9.7 Unicode Driver
```

## Build and Run

Open the project in Qt Creator and select a desktop Qt kit, then build and run.

Or build from the command line:

```bash
cmake -S . -B build
cmake --build build
```

The executable will be created inside the build directory.

## How It Works

When the **Create Table** button is clicked, the app:

1. Creates a Qt SQL connection using `QODBC`.
2. Connects to the MySQL database.
3. Runs this SQL command:

```sql
CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    firstname VARCHAR(20),
    lastname VARCHAR(30),
    age INT
);
```

4. Shows the result in the UI label.

## Troubleshooting

### `Data source name not found and no default driver specified`

The ODBC driver name is wrong or the MySQL ODBC Connector is not installed. Check the exact driver name in **ODBC Data Sources (64-bit)**.

### `QMYSQL driver not loaded`

The Qt kit does not include the MySQL plugin. Use `QODBC`, as this project does, or build/install Qt's `QMYSQL` plugin for your exact Qt version and compiler.

### Table Already Exists

If the `users` table already exists, MySQL will return an error. You can change the query to:

```sql
CREATE TABLE IF NOT EXISTS users (...)
```

if you want repeated button clicks to succeed without an error.
