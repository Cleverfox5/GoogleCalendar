#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTableView>
#include <QLabel>
#include "createcalendardialog.h"
#include "calendarlist.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void displayDatabase();
    void on_loginButton_clicked();
    void on_createCalendarButton_clicked();


private:
    Ui::MainWindow *ui;
    QString loggedInUsername;
    calendarList *calendars;
    int Descriptor;
    QString login;

signals:
    void senData(QString log);

public slots:
    void getLogin(QString log);

};
#endif // MAINWINDOW_H
