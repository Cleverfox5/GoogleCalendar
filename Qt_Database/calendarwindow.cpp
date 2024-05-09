#include "calendarwindow.h"
#include "ui_calendarwindow.h"
#include <QDate>

CalendarWindow::CalendarWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarWindow)
{
    ui->setupUi(this);

    QDate curr_data = QDate::currentDate();
    day = curr_data.day();
    month = curr_data.month();
    year = curr_data.year();

    int week_number = 0;

    //привязка кнопок к функциям
    for (int i = 0; i < 7; i++){
        QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(week_number*7 + i + 1));
        connect(button, SIGNAL(clicked()), this, SLOT(first_week()));
    }
    /*connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(first_week()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));*/
    week_number++;
    for (int i = 0; i < 7; i++){
        QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(week_number*7 + i + 1));
        connect(button, SIGNAL(clicked()), this, SLOT(second_week()));
    }
    week_number++;
    for (int i = 0; i < 7; i++){
        QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(week_number*7 + i + 1));
        connect(button, SIGNAL(clicked()), this, SLOT(third_week()));
    }
    week_number++;
    for (int i = 0; i < 7; i++){
        QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(week_number*7 + i + 1));
        connect(button, SIGNAL(clicked()), this, SLOT(fourth_week()));
    }
    week_number++;
    for (int i = 0; i < 7; i++){
        QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(week_number*7 + i + 1));
        connect(button, SIGNAL(clicked()), this, SLOT(fifth_week()));
    }
    week_number++;
    for (int i = 0; i < 7; i++){
        QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(week_number*7 + i + 1));
        connect(button, SIGNAL(clicked()), this, SLOT(sixth_week()));
    }
    /*
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_19, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_22, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_24, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_25, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_26, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_27, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_28, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_29, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_30, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_31, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_32, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_33, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_34, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_35, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_36, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_37, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_38, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_39, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_40, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_41, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_42, SIGNAL(clicked()), this, SLOT(digits_numbers()));*/

    week_window = new WeekWindow;
}

void CalendarWindow::broker(int week_number){
    QString str;
    QVector<QString> events_id[7];
    for (int i = 0; i < 7; i++){
        QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(week_number*7 + i + 1));
        str.push_back(button->text());
    }
    for (int i = 0; i < 7; i++){
        events_id[i] = days[i + 1 + week_number*7];
    }

    delete week_window;
    week_window = new WeekWindow;
    week_window->show();

    connect(this, &CalendarWindow::SendCalendarInformation, week_window, &WeekWindow::GetCalendarInformation);

    emit SendCalendarInformation(socket, calendar_name, calendar_id, is_creator, login, events_id, str);
}

void CalendarWindow::first_week(){
    broker(0);
}

void CalendarWindow::second_week(){
    broker(1);
}

void CalendarWindow::third_week(){
    broker(2);
}

void CalendarWindow::fourth_week(){
    broker(3);
}

void CalendarWindow::fifth_week(){
    broker(4);
}

void CalendarWindow::sixth_week(){
    broker(5);
}

void CalendarWindow::DrawData(int selected_year, int selecet_month){//вывод дат
    ui->label_2->setText(months[selecet_month - 1] + " " + QString::number(selected_year));
    if (selecet_month == 2){//Февраль
        if ((selected_year % 400 == 0) || ((selected_year % 4 == 0) && (selected_year % 100 != 0))){
            count_day_in_month[2 - 1] = 29;
        }
        else{
            count_day_in_month[2 - 1] = 28;
        }
    }
    QDate date(selected_year, selecet_month, 1);
    int first_day_in_month = date.dayOfWeek();

    for (int i = first_day_in_month - 1; i < first_day_in_month - 1 + count_day_in_month[selecet_month - 1]; i++){
        QPushButton* button = this->findChild<QPushButton *>("pushButton_" + QString::number(i+1));
        if (button){
            button->setText(QString::number(i + 1 - first_day_in_month + 1));
        }
        else{
            ui->label_2->setText("Error");
        }
    }

    //Добавление рамки для текущего дня
}
//ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
//слот получает информацию
void CalendarWindow::GetCalendarInformation(QTcpSocket * soc, QString calendar_information, QString login){
    socket = soc;

    if (calendar_information[0] == '*'){
        is_creator = true;
        calendar_information.remove(0, 1);
    }

    QVector<QString> information;

    information = calendar_information.split(" ");

    calendar_name = information[0];

    calendar_id = information[1].toInt();

    ui->pushButton_calendarName->setText(calendar_name);

    this->login = login;

    DrawData(year, month);
}

CalendarWindow::~CalendarWindow()
{
    delete ui;
    delete week_window;
}

void CalendarWindow::cleaner(){//стереть все даты
    for (int i = 0; i < 42; i++){
        QPushButton * button = this->findChild<QPushButton *>("pushButton_" + QString::number(i+1));
        if (button){
            button->setText("");
        }
    }
}
//описание кнопок <-- и -->
void CalendarWindow::next(){
    month++;
    if (month == 13){
        month = 1;
        year++;
    }
    DrawData(year, month);
}

void CalendarWindow::previous(){
    month--;
    if (month == 0){
        month = 12;
        year--;
    }
    DrawData(year, month);
}

void CalendarWindow::on_pushButton_sudema_clicked()
{
    cleaner();
    next();
}

void CalendarWindow::on_pushButton_tudema_clicked()
{
    cleaner();
    previous();
}

