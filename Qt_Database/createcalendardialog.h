#ifndef CREATECALENDARDIALOG_H
#define CREATECALENDARDIALOG_H

#include <QWidget>

namespace Ui {
class CreateCalendarDialog;
}

class CreateCalendarDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CreateCalendarDialog(QWidget *parent = nullptr);
    ~CreateCalendarDialog();

private slots:


    void on_ComboBox_activated(int index);

private:
    Ui::CreateCalendarDialog *ui;
};

#endif // CREATECALENDARDIALOG_H
