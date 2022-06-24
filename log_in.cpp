#include "log_in.h"
#include "ui_log_in.h"

Log_in::Log_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log_in)
{
    ui->setupUi(this);
}

Log_in::~Log_in()
{
    delete ui;
}
