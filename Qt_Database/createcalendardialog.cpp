#include "createcalendardialog.h"
#include "ui_createcalendardialog.h"

CreateCalendarDialog::CreateCalendarDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateCalendarDialog)
{
    ui->setupUi(this);
}

CreateCalendarDialog::~CreateCalendarDialog()
{
    delete ui;
}



void CreateCalendarDialog::on_ComboBox_activated(int index)
{

}

