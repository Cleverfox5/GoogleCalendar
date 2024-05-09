#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QDialog>
#include <QTcpSocket>
#include <QPointer>
#include <vector>

#include "weekwindow.h"

namespace Ui {
class CalendarWindow;
}

class CalendarWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarWindow(QWidget *parent = nullptr);
    ~CalendarWindow();
    QTcpSocket *socket;//при входе
    bool is_creator = false;
    QString calendar_name = "";
    int calendar_id = 0;
    QString login;

    int day;
    int month;
    int year;

    void DrawData(int selected_year, int selecet_month);

    QVector<QString> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    QVector<QString> days_of_week = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    QVector<int> count_day_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    QVector<QString> color_range = {"#A6FB55", "#FFFE56", "#FFD151", "#FFA252", "#FC4D51"};

private:
    Ui::CalendarWindow *ui;
    WeekWindow * week_window;
    QVector<QString> days[42];
    void cleaner();
    void next();
    void previous();
    void broker(int week_number);

signals:
    void SendCalendarInformation(QTcpSocket * socket, QString calendar_name, int calendar_id, bool is_creator, QString login, QVector<QString> events_id[7], QString str);

public slots:
    void GetCalendarInformation(QTcpSocket * soc, QString calendar_information, QString login);
private slots:
    void on_pushButton_sudema_clicked();
    void on_pushButton_tudema_clicked();
    void first_week();
    void second_week();
    void third_week();
    void fourth_week();
    void fifth_week();
    void sixth_week();
};

#endif // CALENDARWINDOW_H
