#include "contact.h"
#include "ui_contact.h"

Contact::Contact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contact)
{
    ui->setupUi(this);

}

Contact::~Contact()
{
    delete ui;
}

void Contact::show_contact(std::vector<Account*> Accounts_contact)
{
    for (int i = 0; i < (int)Accounts_contact.size() ; i++) {
        ui->ContantslistWidget->addItem(Accounts_contact[i]->get_user_name());

    }
    connect(ui->ContantslistWidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(contact_select(QListWidgetItem*)));
}

void Contact::contact_select(QListWidgetItem* item)
{
    contact = item;
}



void Contact::on_buttonBox_accepted()
{
    emit select_contact(contact->text());
}

