#include "contact.h"
#include "ui_contact.h"

Contact::Contact( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contact)
{
    ui->setupUi(this);

}

Contact::~Contact()
{
    delete ui;
}

void Contact::show_contact(QString typechat,std::vector<Account*> Accounts_contact)
{
    type_chatroom = typechat;
    ui->ContantslistWidget->clear();
    for (int i = 0; i < (int)Accounts_contact.size() ; i++) {
        ui->ContantslistWidget->addItem(Accounts_contact[i]->get_user_name());

    }
    connect(ui->ContantslistWidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(contact_select(QListWidgetItem*)));
}

void Contact::contact_select(QListWidgetItem* item)
{
    if (type_chatroom == "private")
        contact = item->text();
    else
    {
        contact = contact + item->text() + ",";
    }
}



void Contact::on_buttonBox_accepted()
{
    emit select_contact(contact);
}

