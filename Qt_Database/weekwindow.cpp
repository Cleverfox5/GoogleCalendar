#include "weekwindow.h"
#include "ui_weekwindow.h"

WeekWindow::WeekWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeekWindow)
{
    ui->setupUi(this);
}

void WeekWindow::DrowEvents(QString days[], int start_position, int end_position){
    QPushButton *start_pushButton = this->findChild<QPushButton *>("pushButton_" + QString::number(start_position + 1));
    QPushButton *end_pushButton = this->findChild<QPushButton *>("pushButton_" + QString::number(end_position + 1));

    int counter = start_position + 1;

    for (int i = start_pushButton->text().toInt(); i <= end_pushButton->text().toInt(); i++){
        if (days[i] != ""){
            QVector<QString> day_arr;
            day_arr = days[i].split("|");
            for (int j = 0; j < day_arr.size(); j++){
                QVector<QString> event_arr = day_arr[j].split(" ");
                QListWidget * list_widget;
                QString adder_name;
                if (event_arr[event_arr.size() - 1] == "true"){
                    list_widget = this->findChild<QListWidget *>("listWidget_" + QString::number(counter));
                    for (int k = 0; k < event_arr.size() - 2; k++){
                        adder_name += event_arr[k] + " ";
                    }
                    adder_name.removeLast();
                    list_widget->addItem(adder_name);
                }
                else{
                    list_widget = this->findChild<QListWidget *>("listWidget_" + QString::number(counter) + "_" + QString::number(counter));
                    for (int k = 0; k < event_arr.size() - 1; k++){
                        adder_name += event_arr[k] + " ";
                    }
                    adder_name.removeLast();
                    list_widget->addItem(adder_name);
                }
            }
        }
        counter++;
    }
}

void WeekWindow::GetCalendarInformation(QTcpSocket * socket, QString calendar_name, int calendar_id, bool is_creator, QString login, QString events_id[7], QVector<QString> numbers, int year, QString month, QString days[]){
    this->socket = socket;
    this->calendar_name = calendar_name;
    ui->pushButton_calendarName->setText(calendar_name);
    this->calendar_id = calendar_id;
    this->is_creator = is_creator;
    this->login = login;
    this->month = month;
    this->year = year;
    int start_position = 0;
    int end_position = 6;

    for (int i = 0; i < 7; i++){
        if (numbers[0] == "*"){
            if (numbers[i] != "*"){
                QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(i + 1));
                button->setText(numbers[i]);
            }
            else{
                start_position++;
            }
        }
        else{
            if (numbers[i] != "*"){
                QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(i + 1));
                button->setText(numbers[i]);
            }
            else{
                end_position--;
            }
        }
    }
    ui->pushButton_month->setText(month + " " + QString::number(year));
    DrowEvents(days, start_position, end_position);
    //this->events_id = events_id;
}

WeekWindow::~WeekWindow()
{
    delete ui;
}

void WeekWindow::on_pushButton_month_clicked()
{
    reject();
}

