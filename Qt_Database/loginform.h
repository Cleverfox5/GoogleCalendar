#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT
signals:
    void loginSuccessful(const QString& username);

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(QString str, quint16 curr_mode);
    quint16 nextBlockSize;
    quint16 mode;
    QString login;

public slots:
    void slotReadyRead();

private slots:
    void on_loginButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
