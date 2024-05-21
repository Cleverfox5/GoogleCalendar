#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QDialog>

namespace Ui {
class EventWindow;
}

class EventWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EventWindow(QWidget *parent = nullptr);
    ~EventWindow();

private:
    Ui::EventWindow *ui;
};

#endif // EVENTWINDOW_H
