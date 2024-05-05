#ifndef CALENDARLIST_H
#define CALENDARLIST_H

#include <QDialog>
#include <QTcpSocket>
#include "addcalendar.h"

namespace Ui {
class calendarList;
}

class calendarList : public QDialog
{
    Q_OBJECT

public:
    explicit calendarList(QWidget *parent = nullptr);
    ~calendarList();
    int Descriptor;

private:
    Ui::calendarList *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(QString str, quint16 curr_mode);
    quint16 nextBlockSize;
    quint16 mode;
    AddCalendar *add_calendar;
    QString log;

signals:
    void sendDescriptor(QTcpSocket * soc, QString login);
    void sendData(QString str, QString login);

public slots:
    void getID(QString login);
    void slotReadyRead();
private slots:
    void on_pushButton_clicked();
};

#endif // CALENDARLIST_H
