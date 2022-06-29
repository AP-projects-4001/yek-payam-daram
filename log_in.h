#ifndef LOG_IN_H
#define LOG_IN_H

#include <QDialog>

namespace Ui {
class Log_in;
}

class Log_in : public QDialog
{
    Q_OBJECT

public:
    explicit Log_in(QWidget *parent = nullptr);
    ~Log_in();

private:
    Ui::Log_in *ui;

signals:
    void login_info(QString,QString);
public slots:
    void on_pushButton_clicked();
    void login_status(QString msg);
};

#endif // LOG_IN_H
