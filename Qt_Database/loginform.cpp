#include "loginform.h"
#include "ui_loginform.h"
#include <QSqlQuery>
#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_loginButton_clicked()
{
    login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &LoginForm::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
    mode = 0;
    if (ui->loginLineEdit->text().isEmpty() != true && ui->passwordLineEdit->text().isEmpty() != true){
        QString str = login + " " + password;
        socket->connectToHost("127.0.0.1", 2323);

        SendToServer(str, 3);
    }
    else{
        QMessageBox::warning(this, "Login", "Invalid login or password!");
    }
}

void LoginForm::SendToServer(QString str, quint16 curr_mode)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out << quint16(0) << curr_mode << str; //для коректной отправки по частям
    out.device()->seek(0);//сдвиг указателя в начало
    out << quint16(Data.size() - 2*sizeof(quint16));
    socket->write(Data);
}

void LoginForm::slotReadyRead()
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
            if (mode == 3){
                if (str == "True"){
                    mode = 0;
                    emit loginSuccessful(login);
                    accept();
                }
                else{
                    QMessageBox::warning(this, "Login", "Invalid login or password!");
                }
            }
            else{
                ui->label->setText("mode != 3");
            }
        }
    }
    else{//ошибка!!!!!
        //ui->textBrowser->append("read error");
    }
}

void LoginForm::on_cancelButton_clicked()
{
    reject();
}

