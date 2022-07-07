#ifndef PROFILE_H
#define PROFILE_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class Profile;
}

class Profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();
    QListWidget* members;

private:
    Ui::Profile *ui;

public slots:
    void show_profile(QString type ,QString usr, QString email, QString num);

};

#endif // PROFILE_H
