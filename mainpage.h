#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <account.h>
#include "usersettings.h"
#include "profile.h"

namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(std::vector<Account*>& contacts, QString username, QWidget *parent = nullptr);
    ~MainPage();

private:
    Ui::MainPage *ui;

public:
    //for create chatroom order
    QStringList list_order_type_name;

public slots:
    void load_chatrooms(QStringList list_chatroom);

    void on_sendButton_clicked();

    void onListChatroomItemClicked(QListWidgetItem* item);

    void update_massages_ui(QStringList list_massage);

    void show_profile(QString data);

signals:
    void create_chatroom(QString,QString,QString);

    void send_massage(QString,QString,QString);

    ///to show chats in chatroom
    void select_chatroom(QString);

    ///send change user info
    void send_change_toserver(QString,QString,QString,QString);

    ///send info for recive profile
    void send_profile_info(QString, QString);

private slots:
    void on_AddChatroomButton_clicked();
    void addchatroom(QString type_chat);
    void selectcontact(QString name); 
    void set_name_of_group(QString nameofgroup);

    void on_settingButton_clicked();

    void update_acc_vector(QString usr,QString email,QString num);

    void on_profileLinkButton_clicked();

public:
    std::vector<Account*> Accounts_main;
    ///chatroom witch selected for recive massages
    QString chatroom_name;

    QStringList massage_list;

    QString current_user;

    UserSettings* d;
};

#endif // MAINPAGE_H
