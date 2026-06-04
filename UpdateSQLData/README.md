# UpdateSQLData

Qt Widgets application for updating employee data in a MySQL database.

This project uses Qt SQL with the MySQL ODBC driver. It updates records in the `employee` table using values entered in the UI fields.

## Requirements

- Windows
- Qt 6 MinGW kit
- Qt Creator
- CMake
- MySQL Server
- MySQL Connector/ODBC 64-bit

This project was tested with:

```text
Qt 6.10.2 MinGW 64-bit
MySQL ODBC 9.7 Unicode Driver
```

## Database Connection

The project uses `QODBC`, not `QMYSQL`.

Current connection values in `widget.cpp`:

```text
Driver:   MySQL ODBC 9.7 Unicode Driver
Server:   127.0.0.1
Port:     3306
Database: engineeringhub_db
Username: root
Password: root
```

Update these values in `widget.cpp` if your MySQL setup is different.

The application updates this table:

```sql
UPDATE employee
SET name = ?, age = ?, email = ?
WHERE id = ?;
```

Make sure your database has an `employee` table with matching columns.

## Build The Project

1. Open Qt Creator.
2. Open this file:

   ```text
   CMakeLists.txt
   ```

3. Select the Qt MinGW kit.
4. Build the project.

The generated executable will be inside a build folder similar to:

```text
build/Desktop_Qt_6_10_2_MinGW_64_bit-Debug/UpdateSQLData.exe
```

## Deploy Qt Runtime Files

Before running the executable directly, deploy the required Qt DLLs and plugins:

```powershell
C:\Qt\6.10.2\mingw_64\bin\windeployqt.exe D:\Projects\GUIProjects\UpdateSQLData\build\Desktop_Qt_6_10_2_MinGW_64_bit-Debug\UpdateSQLData.exe
```

This copies required files such as:

```text
Qt6Core.dll
Qt6Widgets.dll
Qt6Sql.dll
platforms/qwindows.dll
sqldrivers/qsqlodbc.dll
```

If your Qt version or build folder is different, update the paths in the command.

## Run The Project

After building and running `windeployqt`, run the executable directly:

```text
D:\Projects\GUIProjects\UpdateSQLData\build\Desktop_Qt_6_10_2_MinGW_64_bit-Debug\UpdateSQLData.exe
```

You can double-click the executable from File Explorer.

## Qt Creator Run Note

On some Windows setups, Qt Creator may show this error when trying to run the project:

```text
The command ... UpdateSQLData.exe could not be started.
Either the invoked program is missing, or you may have insufficient permissions to invoke the program.
```

The executable may still work correctly when launched directly from the build folder.

If Qt Creator cannot run the app, use Qt Creator only for editing and building, then run the generated `.exe` manually after `windeployqt`.

## Do Not Commit Build Files

Do not commit the `build/` folder or deployed DLL files to GitHub. They are generated files and should be recreated on each machine.
