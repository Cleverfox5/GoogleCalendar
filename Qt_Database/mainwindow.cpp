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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() //кнопка зарегестрироваться
{
    //model->insertRow(model->rowCount()); //появляется новая строка в таблице
    //ui->pushButton->hide(); // Скрыть кнопку после нажатия
    InputDataDialog inputDataDialog;
    if(inputDataDialog.exec() == QDialog::Accepted)
    {
        // Вывести сообщение об успешной регистрации или выполнить другие действия

        //displayDatabase();
    }
}

void MainWindow::displayDatabase() //вывод базы данных
{
    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    queryModel->setQuery("SELECT * FROM UserList"); // SQL-запрос для выборки всех записей из таблицы UserList

    // Создайте виджет для отображения таблицы данных
    QTableView *tableView = new QTableView(this);
    tableView->setModel(queryModel);

    // Отображение виджета таблицы данных в главном окне
    setCentralWidget(tableView);
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
