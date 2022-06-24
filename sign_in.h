#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QDialog>

namespace Ui {
class Sign_in;
}

class Sign_in : public QDialog
{
    Q_OBJECT

public:
    explicit Sign_in(QWidget *parent = nullptr);
    ~Sign_in();

private:
    Ui::Sign_in *ui;

signals:
    void recive_info(QString,QString,QString,QString,int,int,int);
private slots:
    void on_SigninButton_clicked();
};

#endif // SIGN_IN_H
