#include "mainpage.h"
#include "ui_mainpage.h"
#include <QPushButton>
#include <QCommandLinkButton>
#include <QDebug>
#include <typechatwin.h>
#include <contact.h>

MainPage::MainPage(std::vector<Account*>& contacts,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);

    Accounts_main = contacts;

}

MainPage::~MainPage()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////
///load chatroom and show massages

void MainPage::load_chatrooms(QStringList list_chatroom)
{
    ui->Chatrooms_listwidget->clear();
    for (int i = 0; i < 5 ; i++) {
        ui->Chatrooms_listwidget->addItem("salam");

    }
    connect(ui->Chatrooms_listwidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(onListChatroomItemClicked(QListWidgetItem*)));
}

void MainPage::onListChatroomItemClicked(QListWidgetItem *item)
{
    emit select_chatroom(item->text());
    for (int i = 0; i < 5 ; i++) {

        if (ui->Chatrooms_listwidget->item(i) == item)
        {
            /////////////////
            //loading chat here ...
            /////////////////
            chatroom_name = ui->Chatrooms_listwidget->item(i)->text();
            QString name = ui->Chatrooms_listwidget->item(i)->text();
            qDebug() << name;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
///add chattoom functions

void MainPage::on_AddChatroomButton_clicked()
{
    list_order_type_name.append("create_chatroom");
    Typechatwin *d = new Typechatwin(this);
    d->show();

    connect(d,SIGNAL(selecet_typeof(QString)),this,SLOT(addchatroom(QString)));

}

void MainPage::addchatroom(QString type_chat)
{
    Contact* d = new Contact(this);
    d->show();
    d->show_contact(Accounts_main);
    connect(d,SIGNAL(select_contact(QString)),this,SLOT(selectcontact(QString)));

    list_order_type_name.append(type_chat);
    //emit create_chatroom(type_chat);
}

void MainPage::selectcontact(QString name)
{
    list_order_type_name.append(name);
    emit create_chatroom(list_order_type_name[0],list_order_type_name[1],list_order_type_name[2]);
}



/////////////////////////////////////////////////////////////////////////
//send massage function

void MainPage::on_sendButton_clicked()
{

    emit send_massage("send-massage",ui->textmassageEdit->text(),chatroom_name);
}



