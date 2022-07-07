#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QMainWindow>

namespace Ui {
class UserSettings;
}

class UserSettings : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserSettings(QWidget *parent = nullptr);
    ~UserSettings();

private:
    Ui::UserSettings *ui;

public slots:
    void show_info(QString usr, QString email, QString num);
private slots:
    void on_pushButton_clicked();
signals:
    void send_change_info(QString,QString,QString);


};

#endif // USERSETTINGS_H
