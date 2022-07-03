#ifndef CONTACT_H
#define CONTACT_H

#include <QDialog>
#include <account.h>
#include <QListWidgetItem>
namespace Ui {
class Contact;
}

class Contact : public QDialog
{
    Q_OBJECT

public:
    explicit Contact(QWidget *parent = nullptr);
    ~Contact();
    QListWidgetItem* contact;

private:
    Ui::Contact *ui;

public slots:
    //show contact fo private chat
    void show_contact(std::vector<Account*> Accounts_contact);
    //select contact fo private chat
    void contact_select(QListWidgetItem* item);
private slots:
    void on_buttonBox_accepted();

signals:
    void select_contact(QString);

};

#endif // CONTACT_H
