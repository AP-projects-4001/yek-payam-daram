#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>

namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

private:
    Ui::MainPage *ui;

public slots:
    void load_chatrooms(QString wel);
private slots:
    void on_pushButton_clicked();
};

#endif // MAINPAGE_H
