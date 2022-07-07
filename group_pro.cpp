#include "group_pro.h"
#include "ui_group_pro.h"

Group_pro::Group_pro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Group_pro)
{
    ui->setupUi(this);
}

Group_pro::~Group_pro()
{
    delete ui;
}

void Group_pro::set_subject(QString sub)
{
    ui->SubjectlistWidget->addItem(sub);
}

void Group_pro::show_group_members(QString member)
{
    ui->membersWidget->addItem(member);
}
