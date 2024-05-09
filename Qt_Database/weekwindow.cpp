#include "weekwindow.h"
#include "ui_weekwindow.h"

WeekWindow::WeekWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeekWindow)
{
    ui->setupUi(this);
}

void WeekWindow::GetCalendarInformation(QTcpSocket * socket, QString calendar_name, int calendar_id, bool is_creator, QString login, QVector<QString> events_id[7], QString str){
    this->socket = socket;
    this->calendar_name = calendar_name;
    this->calendar_id = calendar_id;
    this->is_creator = is_creator;
    this->login = login;
    //QVector weekstr
    //this->events_id = events_id;
}

WeekWindow::~WeekWindow()
{
    delete ui;
}
