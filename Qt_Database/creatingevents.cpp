#include "creatingevents.h"
#include "ui_creatingevents.h"
//#include <QSqlQuery>
//#include <QtSql>
//#include <QSqlError>
//#include <QDebug>

CreatingEvents::CreatingEvents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatingEvents)
{
    ui->setupUi(this);

    // Установка режима множественного выбора для ParticipantslistWidget
    ui->ParticipantslistWidget->setSelectionMode(QAbstractItemView::MultiSelection);

}

CreatingEvents::~CreatingEvents()
{
    delete ui;
}


void CreatingEvents::on_SaveButton_clicked()
{
    if (ui->TitleLineEdit->text() != "" && !ui->TitleLineEdit->text().contains(" ")){//проверка на соотвествие
        QList<QListWidgetItem *> selectedItems = ui->ParticipantslistWidget->selectedItems();
        QString Title = ui->TitleLineEdit->text();
        QString Description = ui->DescriptionTextEdit->toPlainText();
        QString  Location= ui->LocationLineEdit->text();
        QString  Type= ui->TypeLineEdit->text();
        QString  Priority= ui->PriorityLineEdit->text();
        QString Start = ui->StartDateTimeEdit->text();
        QString  End= ui->EndDateTimeEdit->text();

        for (auto item : selectedItems) {
            Title+= " " + item->text();
        }
        SendToServer(Title + " " + Description + " " + Location + " " + Type + " " + Priority + " " + Start + " " + End+ " " + log, 20);

        accept();
    }
    else{//вывод предупреждения
        //Не все поля заполнены или в названии не должно быть пробелов
        ui->label->setText("?");
    }

}
void CreatingEvents::getDescriptor(QTcpSocket * soc, QString login){//передача сокета с клиента в окно
    socket = soc;
    log = login;
    SendToServer("UserList Nickname", 5); //передача обрабатываемой таблицы и
    //столбца на сервер для выгрузки ников всех пользователей

    //нам нужны только ники из определенного календаря
}


void CreatingEvents::getData(QString str){
    qDebug() << "Received data from server: " << str; // Выводим полученные данные в консоль
    int len = str.size();
    QString curr_str = "";
    for (int i = 0; i < len; i++){
        if (str[i] == ' '){
            ui->ParticipantslistWidget->addItem(curr_str);
            curr_str = "";
        }
        else if (i == len - 1){
            curr_str.push_back(str[i]);
            ui->ParticipantslistWidget->addItem(curr_str);
        }
        else{
            curr_str.push_back(str[i]);
        }
    }
}
void CreatingEvents::SendToServer(QString str, quint16 curr_mode) //отправка на сервер
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    if (curr_mode == 5 || curr_mode == 20){
        out << quint16(0) << curr_mode << str;
        out.device()->seek(0);
        out << quint16(Data.size() - 2*sizeof(quint16));
        socket->write(Data);
    }
}
void CreatingEvents::on_CancelButton_clicked()
{
    reject();
}





