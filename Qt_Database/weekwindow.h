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
    QVector<QString> events_id[7];

private:
    Ui::WeekWindow *ui;

public slots:
    void GetCalendarInformation(QTcpSocket * socket, QString calendar_name, int calendar_id, bool is_creator, QString login, QVector<QString> events_id[7], QString str);
};

#endif // WEEKWINDOW_H
