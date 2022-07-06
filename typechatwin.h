#ifndef TYPECHATWIN_H
#define TYPECHATWIN_H

#include <QDialog>

namespace Ui {
class Typechatwin;
}

class Typechatwin : public QDialog
{
    Q_OBJECT

public:
    explicit Typechatwin(QWidget *parent = nullptr);
    ~Typechatwin();

private:
    Ui::Typechatwin *ui;

public:
    QString selected_chat;
private slots:
    void on_private_radioButton_clicked();
    void on_group_radioButton_clicked();
    void on_channel_radioButton_clicked();
    void on_buttonBox_accepted();
signals:
    void selecet_typeof(QString);
};

#endif // TYPECHATWIN_H
