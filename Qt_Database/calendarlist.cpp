#include "calendarlist.h"
#include "ui_calendarlist.h"
#include <QString>
#include <QTime>

calendarList::calendarList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calendarList)
{
    ui->setupUi(this);
}

calendarList::~calendarList()
{
    delete ui;
}

void calendarList::getID(QString login)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &calendarList::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
    mode = 0;
    socket->connectToHost("127.0.0.1", 2323);
    SendToServer(login, 4);
}

void calendarList::SendToServer(QString str, quint16 curr_mode)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    if (curr_mode == 4){
        out << quint16(0) << curr_mode << str;
        out.device()->seek(0);
        out << quint16(Data.size() - 2*sizeof(quint16));
        socket->write(Data);
    }
    else if (curr_mode == 5){

    }
}

void calendarList::slotReadyRead()
{
    QDataStream in (socket);
    in.setVersion(QDataStream::Qt_6_6);
    if(in.status() == QDataStream::Ok){
        for (;;){
            if (nextBlockSize == 0){
                if (socket->bytesAvailable() < 2){
                    break;
                }
                in >> nextBlockSize;
                in >> mode;
            }
            if (socket->bytesAvailable() < nextBlockSize){
                break;
            }
            QString str;
            nextBlockSize = 0;
            in >> str;
            if (mode == 1){
                /*QString str;
                QTime time;
                in >> time >> str;
                nextBlockSize = 0;
                //ui->textBrowser->append(time.toString() + " " + str);
                mode = 0;*/
            }
            else if (mode == 2){
                //ui->listWidget->addItem(str);
            }
            else if (mode == 4){
                if (str == "True"){
                    //Ура успех
                }
                else{
                    //Выделение новго дескриптора и проверка, чтобы он не совпадал с использующимися сейчас!
                }
            }
        }
    }
    else{
        //Сообщение: отсутствует соединение!
    }
}

void calendarList::on_pushButton_clicked()
{

}

