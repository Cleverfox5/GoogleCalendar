#ifndef CREATINGEVENTS_H
#define CREATINGEVENTS_H

#include <QDialog>
#include <QListWidgetItem>
#include <QTcpSocket>


namespace Ui {
class CreatingEvents;
}

class CreatingEvents : public QDialog
{
    Q_OBJECT

public:
    explicit CreatingEvents(QWidget *parent = nullptr);
    ~CreatingEvents();

public slots:
    void getData(QString str);
    void getDescriptor(QTcpSocket * soc, QString login);
private slots:
    void on_SaveButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::CreatingEvents *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(QString str, quint16 curr_mode);
    quint16 nextBlockSize;
    quint16 mode;
    QString log;
};

#endif // CREATINGEVENTS_H
