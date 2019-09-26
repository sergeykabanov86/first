#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>

#include "ocilib.hpp"

#define SIZE_STR 260


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnConnect_clicked();

    void on_btnQuery_clicked();

private:
    Ui::MainWindow *ui;
    ocilib::Connection con;
    ocilib::Statement state;
    void OracleCleanup();

};

#endif // MAINWINDOW_H
