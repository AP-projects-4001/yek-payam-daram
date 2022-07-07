#include "typechatwin.h"
#include "ui_typechatwin.h"

Typechatwin::Typechatwin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Typechatwin)
{
    ui->setupUi(this);
}

Typechatwin::~Typechatwin()
{
    delete ui;
}

void Typechatwin::on_private_radioButton_clicked()
{
    selected_chat = "private";
}


void Typechatwin::on_group_radioButton_clicked()
{
    selected_chat = "group";
}


void Typechatwin::on_channel_radioButton_clicked()
{
    selected_chat = "channel";
}


void Typechatwin::on_buttonBox_accepted()
{
    emit selecet_typeof(selected_chat);
}

