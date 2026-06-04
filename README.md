# QT_GUI_Repo

A collection of Qt GUI projects and examples.

This repository is intended to hold multiple Qt-based desktop applications, UI experiments, database connection examples, and other Qt learning projects. Each project is kept in its own folder with its own source files and project-specific notes.

## Projects

| Project | Description |
| --- | --- |
| [MySQLConnection](./MySQLConnection) | Qt Widgets application that connects to a MySQL database using Qt SQL and the MySQL ODBC driver. |

## Repository Structure

```text
QT_GUI_Repo/
+-- MySQLConnection/
|   +-- CMakeLists.txt
|   +-- main.cpp
|   +-- widget.cpp
|   +-- widget.h
|   +-- widget.ui
|   +-- README.md
+-- README.md
```

## Requirements

General requirements may vary by project, but most projects in this repository will use:

- Qt 5 or Qt 6
- Qt Creator
- CMake
- C++17 or newer

Some projects may require additional tools, drivers, or database setup. Check the README inside each project folder for project-specific instructions.

## How To Use

1. Clone the repository:

   ```bash
   git clone https://github.com/shubham7946/QT_GUI_Repo.git
   ```

2. Open the required project folder in Qt Creator.

3. Configure the Qt kit and CMake settings.

4. Build and run the project.

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

This repository is mainly for Qt GUI practice, reusable examples, and project references.
