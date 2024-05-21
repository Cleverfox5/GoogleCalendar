#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputdatadialog.h"
#include "loginform.h"

#include <QSqlQueryModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    input_data_dialog = new InputDataDialog(this);
}

void MainWindow::on_pushButton_clicked() //кнопка зарегестрироваться
{
    input_data_dialog = new InputDataDialog(this);
    input_data_dialog->show();
}

void MainWindow::on_loginButton_clicked()
{

    // Создаем экземпляр формы входа
    LoginForm loginForm(this);
    connect(&loginForm, &LoginForm::loginSuccessful, this, &MainWindow::getLogin);

    // Отображаем форму входа и ожидаем ее закрытия
    if(loginForm.exec() == QDialog::Accepted)
    {

        //переходим на другое окно
        hide();
        calendars = new calendarList(this);
        calendars->show();

        connect(this, &MainWindow::senData, calendars, &calendarList::getID);
        //считываем дескриптор

        emit senData(login);
    }
}


void MainWindow::on_createCalendarButton_clicked()
{

}

void MainWindow::getLogin(QString log){
    login = log;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete calendars;
    delete input_data_dialog;
}
