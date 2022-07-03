#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <account.h>

namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(std::vector<Account*>& contacts,QWidget *parent = nullptr);
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
signals:
    void create_chatroom(QString,QString,QString);

    void send_massage(QString,QString,QString);

    ///to show chats in chatroom
    void select_chatroom(QString);


private slots:
    void on_AddChatroomButton_clicked();
    void addchatroom(QString type_chat);
    void selectcontact(QString name);

public:
    std::vector<Account*> Accounts_main;
    QString chatroom_name;
};

#endif // MAINPAGE_H
