#include "contacts.h"
#include "ui_contacts.h"

Contacts::Contacts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contacts)
{
    ui->setupUi(this);
}

Contacts::~Contacts()
{
    delete ui;
}
