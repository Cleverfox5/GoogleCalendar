#ifndef WEEKWINDOW_H
#define WEEKWINDOW_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class WeekWindow;
}

class WeekWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WeekWindow(QWidget *parent = nullptr);
    ~WeekWindow();
    QTcpSocket * socket;
    QString calendar_name;
    int calendar_id;
    QString login;
    bool is_creator;
    QString events_id[7];
    int year;
    QString month;
    int day;
    QString days[42];

private:
    Ui::WeekWindow *ui;
    void DrowEvents(QString days[42], int start_position, int end_position);

public slots:
    void GetCalendarInformation(QTcpSocket * socket, QString calendar_name, int calendar_id, bool is_creator, QString login, QString events_id[7], QVector<QString> numbers, int year, QString month, QString days[]);
private slots:
    void on_pushButton_month_clicked();
};

#endif // WEEKWINDOW_H
