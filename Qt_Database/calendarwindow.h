#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class CalendarWindow;
}

class CalendarWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarWindow(QWidget *parent = nullptr);
    ~CalendarWindow();
    QTcpSocket *socket;
    bool is_creator = false;
    QString calendar_name = "";
    int calendar_id = 0;

private:
    Ui::CalendarWindow *ui;
public slots:
    void GetCalendarInformation(QTcpSocket * soc, QString calendar_information);
};

#endif // CALENDARWINDOW_H
