#include "mainpage.h"
#include "ui_mainpage.h"
#include <QPushButton>
#include <QCommandLinkButton>
#include <QDebug>
#include <typechatwin.h>
#include <contact.h>
#include "nameofgroup.h"


MainPage::MainPage(std::vector<Account*>& contacts, QString username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);

    Accounts_main = contacts;

    current_user = username;

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

    for (int i = 0; i < list_chatroom.length() ; i++) {
        ui->Chatrooms_listwidget->addItem(list_chatroom[i]);

    }
    connect(ui->Chatrooms_listwidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(onListChatroomItemClicked(QListWidgetItem*)));
}

void MainPage::update_massages_ui(QStringList list_massage)
{
    massage_list = list_massage;
}

void MainPage::onListChatroomItemClicked(QListWidgetItem *item)
{
    emit select_chatroom(item->text());
    chatroom_name = item->text();

    ui->chatlistofownWidget->clear();
    ui->chatlistofsenderWidget->clear();
    if (massage_list[0] != "empty")
    {
        for (int i = 0; i < ui->Chatrooms_listwidget->count() ; i++) {

            if (ui->Chatrooms_listwidget->item(i) == item)
            {

                qDebug() << chatroom_name;
                for (int j = 0; j < massage_list.length()-1 ; j+=2) {
                    if (massage_list[j] == current_user)
                    {
                        ui->chatlistofownWidget->addItem(massage_list[j]+" :");
                        ui->chatlistofownWidget->addItem(massage_list[j+1]);
                        ui->chatlistofsenderWidget->addItem("");
                        ui->chatlistofsenderWidget->addItem("");
                    }
                    else
                    {
                        ui->chatlistofsenderWidget->addItem(massage_list[j]+" :");
                        ui->chatlistofsenderWidget->addItem(massage_list[j+1]);
                        ui->chatlistofownWidget->addItem("");
                        ui->chatlistofownWidget->addItem("");
                    }
                }//ali,salam,asghar,salam,ali,cheto
                /////////////////
                //loading chat here ...
                /////////////////
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
///add chattoom functions

void MainPage::on_AddChatroomButton_clicked()
{
    list_order_type_name.clear();
    list_order_type_name.append("create_chatroom");
    Typechatwin *d = new Typechatwin(this);
    d->show();

    connect(d,SIGNAL(selecet_typeof(QString)),this,SLOT(addchatroom(QString)));

}

void MainPage::addchatroom(QString type_chat)
{
    Contact* d = new Contact(this);
    d->show();
    d->show_contact(type_chat,Accounts_main);

    connect(d,SIGNAL(select_contact(QString)),this,SLOT(selectcontact(QString)));


    list_order_type_name.append(type_chat);
}

void MainPage::selectcontact(QString name)
{

    if (list_order_type_name[1] == "private")
    {
        qDebug() << "create private chat";
        list_order_type_name.append(name);
        emit create_chatroom(list_order_type_name[0],list_order_type_name[1],list_order_type_name[2]);
    }
    else //if (list_order_type_name[1] == "group")
    {
        Nameofgroup *d = new Nameofgroup(this);
        d->show();
        list_order_type_name.append(name);
        connect(d,SIGNAL(name_ofgroup(QString)),this, SLOT(set_name_of_group(QString)));
    }
}

void MainPage::set_name_of_group(QString nameofgroup)
{

    list_order_type_name[2] += nameofgroup;
    emit create_chatroom(list_order_type_name[0],list_order_type_name[1],list_order_type_name[2]);
}


/////////////////////////////////////////////////////////////////////////
//send massage function

void MainPage::on_sendButton_clicked()
{
    //ui->chatlistofownWidget->addItem(ui->textmassageEdit->text());
    emit send_massage("send_massage",ui->textmassageEdit->text(),chatroom_name);
    ui->textmassageEdit->clear();
}


///////////////////////////////////////////////////////////////////////////
///persnoal setting

void MainPage::on_settingButton_clicked()
{
    d = new UserSettings(this);
    d->show();
    for(int i = 0; (int)Accounts_main.size()-1; i++)
    {
        if (Accounts_main[i]->get_user_name() == current_user)
        {
            d->show_info(Accounts_main[i]->get_user_name(), Accounts_main[i]->get_email(), Accounts_main[i]->get_number());
            break;
        }
    }
    connect(d,SIGNAL(send_change_info(QString,QString,QString)), this, SLOT(update_acc_vector(QString,QString,QString)));
}

void MainPage::update_acc_vector(QString usr, QString email, QString num)
{
    delete d;
    for (int i = 0; i < (int)Accounts_main.size() ; i++ )
    {
        if (Accounts_main[i]->get_user_name()== current_user)
        {
            Accounts_main[i]->set_user_name(usr);
            Accounts_main[i]->set_email(email);
            Accounts_main[i]->set_number(num);
            break;
        }

    }
    emit send_change_toserver("setting", usr, email, num);
}

////////////////////////////////////////////////////////////////////////////
//show profile

void MainPage::on_profileLinkButton_clicked()
{
    QString order = "profile";
    QStringList name = chatroom_name.split(":");

    if(name[0] == current_user)
    {
        emit send_profile_info(order, name[1]);
    }
    else
    {
        emit send_profile_info(order, name[0]);
    }

}


void MainPage::show_profile(QString data)
{
    QStringList list_info = data.split(",");

    Profile* pro_window = new Profile(this);
    pro_window->show();

    pro_window->show_profile(list_info[0], list_info[1], list_info[2]);
}
