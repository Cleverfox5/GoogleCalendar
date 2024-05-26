#include "eventwindow.h"
#include "ui_eventwindow.h"

EventWindow::EventWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventWindow)
{
    ui->setupUi(this);
}

EventWindow::~EventWindow()
{
    delete ui;
}

void EventWindow::getEventLabel(QTcpSocket *socket, QString label, QString login, QString calendar_name, int calendar_id, int event_id)
{
    ui->textBrowser->clear();

    this->socket = socket;
    ui->pushButton_event_name->setText(label);
    this->login = login;
    ui->pushButton_calendar_name->setText(calendar_name);
    this->calendar_id = calendar_id;
    this->event_id = event_id;
    //ui->textBrowser->append("Какой-то текст");
    SendToServer(QString::number(event_id), 8);
}

void EventWindow::getMessages(QString str)
{
    QVector<QString> massages = str.split("|");
    for (int i = 0; i < massages.size(); i++){
        ui->textBrowser->append(massages[i]);
    }
}

void EventWindow::on_pushButton_send_clicked()
{
    QString massage = ui->lineEdit->text();
    if (!massage.contains("|") && massage != ""){
        SendToServer(login + "|" + QDate::currentDate().toString() + "|" + QTime::currentTime().toString() + "|" + QString::number(event_id) + "|" + massage, 9);
    }
}

void EventWindow::SendToServer(QString str, quint16 curr_mode)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    if (curr_mode != 1){
        out << quint16(0) << curr_mode << str;
        out.device()->seek(0);
        out << quint16(Data.size() - 2*sizeof(quint16));
        socket->write(Data);
    }
}

