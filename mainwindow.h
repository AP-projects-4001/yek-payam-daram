#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "account.h"
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_signin_openwindow_Button_clicked();
    void submit_acc(QString nameinp , QString emailinp, QString phonenuminp, QString passinp, int year, int month, int day);

    void on_Login_openwindow_Button_clicked();

    void readingdata();

    void writingdata();

    void connecttoserver();

    void dissconnect();

private:
    Ui::MainWindow *ui;
    std::vector<Account> Accounts;
    QTcpSocket* clientsocket;
    Account* new_acc;
};
#endif // MAINWINDOW_H