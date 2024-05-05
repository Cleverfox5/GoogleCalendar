#include "server.h"

#include <QSqlQueryModel>
#include <QVector>



server::server()
{
    if (this->listen(QHostAddress::Any, 2323)){
        qDebug() << "Start";
    }
    else {
        qDebug() << "Error";
    }
    nextBlockSize = 0;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db_calendar.db");
    if(db.open())
    {
        qDebug("open");

    }
    else
    {
        qDebug("no open");
    }
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE UserList(id INTEGER PRIMARY KEY AUTOINCREMENT , Login TEXT,  Password TEXT, LastName TEXT, FirstName TEXT, MiddleName TEXT, JobTitle TEXT, Department TEXT, Nickname TEXT, Descriptor INTEGER DEFAULT 0)");

    query->exec("CREATE TABLE GlobalCalendarslist (id INTEGER PRIMARY KEY AUTOINCREMENT, creator_id INTEGER,calendar_name TEXT, FOREIGN KEY(creator_id) REFERENCES UserList(id))");
    query->exec("CREATE TABLE CalendarMembers (calendar_id INTEGER,user_id INTEGER,FOREIGN KEY(calendar_id) REFERENCES GlobalCalendarslist(id),FOREIGN KEY(user_id) REFERENCES UserList(id))");

    query->exec("CREATE TABLE Events (id INTEGER PRIMARY KEY AUTOINCREMENT,calendar_id INTEGER NOT NULL, title TEXT NOT NULL,description TEXT,location TEXT,type TEXT,priority INTEGER,start_date DATETIME,end_date DATETIME,FOREIGN KEY (calendar_id) REFERENCES GlobalCalendarslist(id) )");
    query->exec("CREATE TABLE EventParticipants (event_id INTEGER,user_id INTEGER,is_informed INTEGER DEFAULT 0,FOREIGN KEY (event_id) REFERENCES Events(id),FOREIGN KEY (user_id) REFERENCES UserList(id))");
    query->exec("CREATE TABLE EventInformants (event_id INTEGER,user_id INTEGER,FOREIGN KEY (event_id) REFERENCES Events(id),FOREIGN KEY (user_id) REFERENCES UserList(id))");

    query->exec("CREATE TABLE Notifications (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, type TEXT, message TEXT, timestamp DATETIME, is_read INTEGER DEFAULT 0, FOREIGN KEY (user_id) REFERENCES UserList(id))");
}

void server::incomingConnection(qintptr SocketDescripor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(SocketDescripor);
    connect(socket, &QTcpSocket::readyRead, this, &server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    qDebug() << "client connected" << SocketDescripor;

    //Получаю id и меняю его дескриптор


    /*for (int i = 0; i < Sockets.size(); i++){// -1
        QString str = QString::number(Sockets[i]->socketDescriptor());
        SendToClient(str, 2);
    }
    for (int i = 0; i < Sockets.size() - 1; i++){
        socket = Sockets[i];
        SendToClient(QString::number(SocketDescripor), 2);
    }*/
}

void server::slotReadyRead(){
    socket = (QTcpSocket*) sender();
    qDebug() << socket->socketDescriptor();
    QDataStream in (socket);
    in.setVersion(QDataStream::Qt_6_6);
    if(in.status() == QDataStream::Ok){
        qDebug() << "read...";
        for (;;){
            if (nextBlockSize == 0){
                qDebug() << "nextBlockSize = 0";
                if (socket->bytesAvailable() < 2){
                    qDebug() << "Data < 2";
                    break;
                }
                in >> nextBlockSize;//размер блока
                in >> mode;
                qDebug() << "next block size = " << nextBlockSize;
                qDebug() << "mode = " << mode;
            }
            if (socket->bytesAvailable() < nextBlockSize){
                qDebug() << "Data not full";
                break;
            }
            if (mode == 1){
                QString str;
                QTime time;
                in >> time >> str;
                nextBlockSize = 0;
                qDebug() << str;
                SendToClient(str, mode, socket);
            }
            else if (mode == 2){
                QString str;
                QVector<QString> client_data;
                qintptr SocketDescripor = 0;
                QString curr_str;
                int len = str.size();
                in >> str;
                nextBlockSize = 0;
                for (int i = 0; i < str.size(); i++){
                    if (str[i] == ' '){
                        client_data.append(curr_str);
                        curr_str = "";
                    }
                    else if (i == len - 1){
                        curr_str.push_back(str[i]);
                        client_data.append(curr_str);
                    }
                    else{
                        curr_str.push_back(str[i]);
                    }
                }
                query->prepare("INSERT INTO UserList (Login, Password, LastName, FirstName, MiddleName, JobTitle, Department, Nickname, Descriptor) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
                for (int i = 0; i < client_data.size(); i++){
                    query->addBindValue(client_data[i]);
                }
                query->addBindValue(SocketDescripor);
                if(query->exec())
                {
                    qDebug("Пользователь добавлен");
                    SendToClient("True", 2, socket);
                }
                else
                {
                    qDebug("Не удалось добавить пользователя");
                    SendToClient("False", 2, socket);
                }
            }
            else if (mode == 3){
                QSqlQuery query;
                QString str;
                QString login = "";
                QString password = "";
                in >> str;
                nextBlockSize = 0;
                QString curr_str;
                int len = str.size();
                for (int i = 0; i < len; i++){
                    if (str[i] == ' '){
                        login = curr_str;
                        curr_str = "";
                    }
                    else if (i == len - 1){
                        curr_str.push_back(str[i]);
                        password = curr_str;
                    }
                    else{
                        curr_str.push_back(str[i]);
                    }
                }
                qDebug() << login;
                qDebug() << password;
                query.prepare("SELECT * FROM UserList WHERE Login = :login AND Password = :password");
                query.bindValue(":login", login);
                query.bindValue(":password", password);
                if(query.exec() && query.next())
                {
                    qDebug() << "Верно";
                    SendToClient("True", 3, socket);
                }
                else
                {
                    SendToClient("False", 3, socket);
                }
            }
            else if (mode == 4){// !!!Добавление провекри, что данный сокет не используется сейчас!!!
                QSqlQuery query;
                QString str;
                nextBlockSize = 0;
                in >> str;
                query.prepare("UPDATE UserList SET Descriptor = :descriptor WHERE Login = :login");
                query.bindValue(":descriptor", socket->socketDescriptor());
                query.bindValue(":login", str);
                if (query.exec()) {
                    SendToClient("True", 4, socket);
                }
                else{
                    qDebug() << "Ошибка выполнения запроса:";
                    SendToClient("False", 4, socket);
                }
            }
            else if (mode == 5){
                QSqlQuery query;
                QString str;
                QString table;
                QString column;
                nextBlockSize = 0;//на этом всй держится забуду записать сервак рухнет
                QString curr_str;
                in >> str;
                int len = str.size();
                for (int i = 0; i < len; i++){
                    if (str[i] == ' '){
                        table = curr_str;
                        curr_str = "";
                    }
                    else if (i == len - 1){
                        curr_str.push_back(str[i]);
                        column = curr_str;
                    }
                    else{
                        curr_str.push_back(str[i]);
                    }
                }
                qDebug() << table;
                qDebug() << column;
                if (query.exec("SELECT " + column + " FROM " + table)){
                    QString Data;
                    while (query.next()) {
                        QString value = query.value(0).toString(); // Используйте индекс столбца для извлечения значения
                        qDebug() << value;
                        Data.push_back(value);
                        Data.push_back(" ");
                    }
                    Data.chop(1);
                    SendToClient(Data, 5, socket);

                }
                else{
                    qDebug() << "неверный запрос";
                }
            }
            else if (mode == 6){//Добавление нового календаря
                QString str;
                QVector<QString> calendar_data;
                QString curr_str;
                in >> str;
                int len = str.size();
                nextBlockSize = 0;
                for (int i = 0; i < len; i++){
                    if (str[i] == ' '){
                        calendar_data.append(curr_str);
                        qDebug() << curr_str;
                        curr_str = "";
                    }
                    else if (i == len - 1){
                        curr_str.push_back(str[i]);
                        calendar_data.append(curr_str);
                        qDebug() << curr_str;

                    }
                    else{
                        curr_str.push_back(str[i]);
                    }
                }

                QVector<int> id_members;
                QString name = calendar_data[0];

                query->prepare("SELECT id FROM UserList WHERE Login = :login");
                query->bindValue(":login", calendar_data[1]);

                if(!query->exec())
                {
                    qDebug("id creator не получены");
                }

                query->next();

                int id_creator = query->value(0).toInt();

                for (int i = 2; i < calendar_data.size(); i++){
                    query->prepare("SELECT id FROM UserList WHERE Nickname = :nickname");
                    query->bindValue(":nickname", calendar_data[i]);
                    if(!query->exec())
                        qDebug("id пользователей не получены");
                    query->next();
                    id_members.append(query->value(0).toInt());
                }

                if(!query->exec())
                {
                    qDebug("id пользователей не получены");
                }

                query->prepare("INSERT INTO GlobalCalendarslist (creator_id, calendar_name) VALUES (?, ?)");

                query->addBindValue(id_creator);
                query->addBindValue(name);

                if(query->exec())
                {
                    qDebug("Календарь успешно добавлен");
                }
                else
                {
                    qDebug("Календарь не удалось добавить");
                }

                int calendar_id = query->lastInsertId().toInt();

                for (int i = 0; i < id_members.size(); i++){
                    query->prepare("INSERT INTO CalendarMembers (calendar_id, user_id) VALUES (?, ?)");
                    query->addBindValue(calendar_id);
                    query->addBindValue(id_members[i]);
                    if(!query->exec()){
                        qDebug("Не удалось удалить пользователя");
                    }

                }


                SendToClient(name + " " + QString::number(calendar_id), 6, socket);
            }
            mode = 0;
            break;
        }
    }
    else{
        qDebug() << "DataStream error";
    }
}

void server::SendToClient(QString str, quint16 curr_mode, QTcpSocket * curr_socket){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    if(curr_mode == 1){
        out << quint16(0) << curr_mode << QTime::currentTime() << str;//для коректной отправки по частям
        out.device()->seek(0);
        out << quint16(Data.size() - 2*sizeof(quint16));
    }
    else{
        out << quint16(0) << curr_mode << str;//для коректной отправки по частям
        out.device()->seek(0);
        out << quint16(Data.size() - 2*sizeof(quint16));
    }

    curr_socket->write(Data);
}
