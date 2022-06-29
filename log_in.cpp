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


void Log_in::on_pushButton_clicked()
{
    emit login_info(ui->lineUserName->text(), ui->linePassword->text());
}

void Log_in::login_status(QString msg)
{
    ui->loginstatus->clear();
    ui->loginstatus->addItem(msg);


}

