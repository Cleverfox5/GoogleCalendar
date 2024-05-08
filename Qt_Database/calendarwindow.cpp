#include "calendarwindow.h"
#include "ui_calendarwindow.h"
#include <QDate>

CalendarWindow::CalendarWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarWindow)
{
    ui->setupUi(this);

}

void CalendarWindow::GetCalendarInformation(QTcpSocket * soc, QString calendar_information){
    socket = soc;

    if (calendar_information[0] == '*'){
        is_creator = true;
        calendar_information.remove(0, 1);
    }

    QString curr_str = "";

    QVector<QString> information;


    information = calendar_information.split(" ");

    calendar_name = information[0];

    calendar_id = information[1].toInt();

    ui->pushButton_calendarName->setText(calendar_name);
}

CalendarWindow::~CalendarWindow()
{
    delete ui;
}
