# GUIProjects

A collection of Qt GUI projects and database examples.

This repository contains small Qt Widgets applications built while learning Qt GUI development, CMake, and database integration. Each project is kept in its own folder with its own source files and, where needed, project-specific notes.

## Projects

| Project | Description |
| --- | --- |
| [MySQLConnection](./MySQLConnection) | Basic Qt Widgets application that connects to a MySQL database using Qt SQL and the MySQL ODBC driver. |
| [CreateTable](./CreateTable) | Connects to MySQL and creates a `users` table from a Qt button click. |
| [InserMQSQLData](./InserMQSQLData) | Form-based Qt application for inserting first name, last name, and age values into a MySQL `users` table. |
| [DeleteSQLData](./DeleteSQLData) | Deletes a row from the MySQL `employee` table by row ID. |
| [UpdateSQLData](./UpdateSQLData) | Updates employee details in a MySQL `employee` table using values entered in the UI. |

## Repository Structure

```text
GUIProjects/
+-- MySQLConnection/
|   +-- CMakeLists.txt
|   +-- main.cpp
|   +-- widget.cpp
|   +-- widget.h
|   +-- widget.ui
|   +-- README.md
+-- CreateTable/
|   +-- CMakeLists.txt
|   +-- main.cpp
|   +-- widget.cpp
|   +-- widget.h
|   +-- widget.ui
|   +-- README.md
+-- InserMQSQLData/
|   +-- CMakeLists.txt
|   +-- main.cpp
|   +-- widget.cpp
|   +-- widget.h
|   +-- widget.ui
|   +-- README.md
+-- DeleteSQLData/
|   +-- CMakeLists.txt
|   +-- main.cpp
|   +-- widget.cpp
|   +-- widget.h
|   +-- widget.ui
+-- UpdateSQLData/
|   +-- CMakeLists.txt
|   +-- main.cpp
|   +-- widget.cpp
|   +-- widget.h
|   +-- widget.ui
|   +-- README.md
+-- README.md
```

## Requirements

Requirements vary by project, but most projects in this repository use:

- Qt 6, or Qt 5 with the required modules
- Qt Creator
- CMake
- C++17 or newer
- MySQL Server
- MySQL Connector/ODBC for Windows, for projects that use `QODBC`

Some projects may require a specific database name, table name, driver name, username, or password. Check the README inside each project folder for project-specific setup instructions.

## How To Use

1. Clone the repository:

   ```bash
   git clone https://github.com/smishra125/GUIProjects.git
   ```

2. Open the required project folder in Qt Creator.

3. Configure the Qt kit and CMake settings.

4. Build and run the project.

## Database Notes

The database examples use Qt SQL. Some projects connect through `QODBC`, while `DeleteSQLData` currently uses `QMYSQL`.

If your Qt kit does not include the native MySQL driver, use the MySQL ODBC driver and update the project code to use the exact installed driver name, for example:

```text
MySQL ODBC 9.7 Unicode Driver
```

Common values used in these examples include:

```text
Server:   localhost or 127.0.0.1
Port:     3306
Username: root
Password: root or blank, depending on the project
```

Update the connection settings in each project's `widget.cpp` to match your local MySQL setup.

## Adding More Qt Projects

When adding a new Qt project:

1. Create a new folder at the repository root.
2. Keep all files for that project inside its own folder.
3. Add a short project README if setup steps are needed.
4. Add the new project to the Projects table in this README.

Suggested structure:

```text
NewQtProject/
+-- CMakeLists.txt
+-- main.cpp
+-- README.md
+-- source files...
```

## Notes

This repository is mainly for Qt GUI practice, MySQL connectivity examples, reusable references, and small desktop experiments.
