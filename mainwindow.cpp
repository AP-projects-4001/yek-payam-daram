#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sign_in.h"
#include "log_in.h"
#include <QByteArray>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
    clientsocket->write("exit");
    clientsocket->waitForBytesWritten(-1);
}

//sign in function

void MainWindow::on_signin_openwindow_Button_clicked()
{
    Sign_in* d = new Sign_in(this);
    d->show();
    clientsocket = new QTcpSocket(this);

    connect(d,SIGNAL(recive_info(QString,QString,QString,QString,int,int,int)),this,SLOT(submit_acc(QString,QString,QString,QString,int,int,int)));

    }

void MainWindow::submit_acc(QString nameinp, QString emailinp, QString phonenuminp, QString passinp, int year, int month, int day)
{
    new_acc = new Account;
    new_acc->set_user_name(nameinp);
    new_acc->set_email(emailinp);
    new_acc->set_number(phonenuminp);
    new_acc->set_password(passinp);
    new_acc->set_Date_birthday(year,month,day);
    Accounts.push_back(new_acc);

    clientsocket->connectToHost("127.0.0.1", 1025);

    connect(clientsocket,SIGNAL(connected()),this, SLOT(connecttoserver()));

    connect(clientsocket,SIGNAL(bytesWritten(qint64)),this,SLOT(writingdata()));

    connect(clientsocket,SIGNAL(readyRead()),this,SLOT(readingdata()));

    connect(clientsocket,SIGNAL(disconnected()),this,SLOT(dissconnect()));


}

void MainWindow::readingdata()
{
    QByteArray data =clientsocket->readAll();
    qDebug() << data;
    qDebug() << "reading secssusfuly";
}

void MainWindow::writingdata()
{

    qDebug() << "writing data ... ";
}

void MainWindow::connecttoserver()
{
    qDebug() << "connected.";
    clientsocket->write("signin");
    clientsocket->write(",");
    std::string ba = Accounts[Accounts.size()-1]->get_user_name().toStdString();
    const char *c_str1 = ba.data();
    clientsocket->write(c_str1);
    clientsocket->write(",");

    std::string ba1 = Accounts[Accounts.size()-1]->get_email().toStdString();
    const char *c_str2 = ba1.data();
    clientsocket->write(c_str2);
    clientsocket->write(",");

    std::string ba2 = Accounts[Accounts.size()-1]->get_number().toStdString();
    const char *c_str3 = ba2.data();
    clientsocket->write(c_str3);
    clientsocket->write(",");

    std::string ba3 = Accounts[Accounts.size()-1]->get_password().toStdString();
    const char *c_str4 = ba3.data();
    clientsocket->write(c_str4);
    clientsocket->write(",");

    QByteArray qbaint1;
    qbaint1.setNum(new_acc->get_yDate());
    clientsocket->write(qbaint1);
    clientsocket->write(",");
    QByteArray qbaint2 ;
    qbaint2.setNum(new_acc->get_mDate());
    clientsocket->write(qbaint2);
    clientsocket->write(",");
    QByteArray qbaint3 ;
    qbaint3.setNum(new_acc->get_dDate());
    clientsocket->write(qbaint3);


}

void MainWindow::dissconnect()
{
    qDebug() << "connection lost!";


}


///////////////////////////////////////////////////////////////

//log in function

void MainWindow::on_Login_openwindow_Button_clicked()
{
    d = new Log_in(this);
    d->show();
    clientsocket = new QTcpSocket(this);
    connect(d,SIGNAL(login_info(QString,QString)),this,SLOT(login_acc(QString,QString)));

}

void MainWindow::login_acc(QString user_inp, QString pass)
{
    clientsocket->connectToHost("127.0.0.1", 1025);

//    while(!clientsocket->waitForReadyRead(-1))
//        qDebug() << "data recive" << clientsocket->readAll();
    clientsocket->write("login");
    clientsocket->write(",");
    QByteArray us = user_inp.toUtf8();
    clientsocket->write(us);
    clientsocket->write(",");
    QByteArray pa = pass.toUtf8();
    clientsocket->write(pa);
    clientsocket->waitForBytesWritten(-1);
    qDebug() << "massege sent";
    while(clientsocket->waitForReadyRead(-1))
    {

        QByteArray datain = clientsocket->readAll();
        qDebug() << "data recive" << datain;
        d->login_status((QString)datain);


        if (datain != "your username or password is wrong!!!")
        {
            delete d;

            myAccount(user_inp);

        }
        break;
    }

}

//////////////////////////////////////////////////////////////////////////////
// account functions


void MainWindow::myAccount(QString curent_user)
{


//    clientsocket->write("ok");
//    clientsocket->waitForBytesWritten(-1);

    updata_clinet_vector();

    mainpagewindow = new MainPage(Accounts,curent_user,this);
    mainpagewindow->show();

    // recive data from server
    //connect(clientsocket,SIGNAL(readyRead()),this,SLOT(update_chatroomlist()));
    clientsocket->write("show chatrooms");
    clientsocket->waitForBytesWritten(-1);

    update_chatroomlist();

    mainpagewindow->load_chatrooms(chatrooms_name);

    connect(mainpagewindow, SIGNAL(create_chatroom(QString,QString,QString)),this, SLOT(createchat(QString,QString,QString)));
    connect(mainpagewindow, SIGNAL(send_massage(QString,QString,QString)),this,SLOT(send_massage(QString,QString,QString)));
    connect(mainpagewindow, SIGNAL(select_chatroom(QString)),this, SLOT(select_chat(QString)));
    connect(mainpagewindow, SIGNAL(send_change_toserver(QString,QString,QString,QString)), this , SLOT(change_info(QString,QString,QString,QString)));
    connect(mainpagewindow, SIGNAL(send_profile_info(QString, QString)), this , SLOT(profile_info(QString,QString)));
}

///////////////////////////////////////////////////////////////////////////
//orders:

// crate chatroom and show in window
void MainWindow::createchat(QString order, QString type, QString name)
{
    clientsocket->write(order.toUtf8(),order.toUtf8().size());
    clientsocket->write(",");

    clientsocket->write(type.toUtf8(),type.toUtf8().size());
    clientsocket->write(",");

    clientsocket->write(name.toUtf8(),name.toUtf8().size());
    clientsocket->waitForBytesWritten(-1);

    qDebug() << "wait for read";
    //clientsocket->waitForBytesWritten(10000);
    clientsocket->flush();
    clientsocket->waitForBytesWritten(-1);

    clientsocket->write("show chatrooms");
    clientsocket->waitForBytesWritten(-1);

    // recive data from server
    update_chatroomlist();

    mainpagewindow->load_chatrooms(chatrooms_name);

    //connect(clientsocket,SIGNAL(readyRead()),this,SLOT(update_chatroomlist()));
    //update_chatroomlist();
}

// send massage
void MainWindow::send_massage(QString order, QString text, QString chatroomname)
{
    QByteArray send = order.toUtf8();
    clientsocket->write(send);
    clientsocket->write(",");

    QByteArray countain = text.toUtf8();
    clientsocket->write(countain);
    clientsocket->write(",");

    QByteArray chatname = chatroomname.toUtf8();
    clientsocket->write(chatname);
    clientsocket->flush();
    clientsocket->waitForBytesWritten(-1);
}

//select chatroom for update chats
void MainWindow::select_chat(QString chatroomname)
{
    clientsocket->write("select_chatroom");
    clientsocket->write(",");
    clientsocket->write(chatroomname.toUtf8(), chatroomname.toUtf8().size());
    clientsocket->flush();
    clientsocket->waitForBytesWritten(-1);

    update_selected_chatroom();
    mainpagewindow->update_massages_ui(massages);
}

//change user settings info
void MainWindow::change_info(QString order, QString user, QString email, QString number)
{
    clientsocket->write(order.toUtf8(),order.toUtf8().size());
    clientsocket->write(",");
    clientsocket->write(user.toUtf8(),user.toUtf8().size());
    clientsocket->write(",");
    clientsocket->write(email.toUtf8(),email.toUtf8().size());
    clientsocket->write(",");
    clientsocket->write(number.toUtf8(),number.toUtf8().size());
    clientsocket->waitForBytesWritten(-1);
}

void MainWindow::profile_info(QString order_p,QString user_p)
{
    clientsocket->write(order_p.toUtf8());
    clientsocket->write(",");
    clientsocket->write(user_p.toUtf8());
    clientsocket->waitForBytesWritten(-1);

    QByteArray data;
    while(clientsocket->waitForReadyRead(-1))
    {
         data = clientsocket->readAll();
         break;
    }
    mainpagewindow->show_profile((QString)data);
}

///////////////////////////////////////////////////////////////////////////
//update client vector from server

void MainWindow::updata_clinet_vector()
{
    int size_vector = 0;
    QStringList list0;

    while(clientsocket->waitForReadyRead(-1))
    {
        QByteArray Data = clientsocket->readAll();
        QStringList qData = QString(Data).split(":");
        size_vector = qData[0].toInt();
        list0 = qData[1].split('/');
        break;
    }

    for (int i = 0; i < size_vector; i++) {
        QStringList list1 = list0[i].split(",");
        Account* newacc = new Account;
        newacc->set_user_name(list1[0]);
        newacc->set_email(list1[1]);
        newacc->set_number(list1[2]);
        for (int j = 4; j < list1[3].toInt() ; j++ ) {
            newacc->frend.push_back(list1[j]);
        }
        Accounts.push_back(newacc);
    }

}

///////////////////////////////////////////////////////////////////////////
//update chatroom list from server

void MainWindow::update_chatroomlist()
{

    while(clientsocket->waitForReadyRead(-1))
    {
        QByteArray Data = clientsocket->readAll();
        chatrooms_name = ((QString)Data).split(",");
        break;
    }
}

void MainWindow::update_selected_chatroom()
{
    while(clientsocket->waitForReadyRead(-1))
    {
        QByteArray Data = clientsocket->readAll();
        massages = ((QString)Data).split(",");
        break;
    }
}

