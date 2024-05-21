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
