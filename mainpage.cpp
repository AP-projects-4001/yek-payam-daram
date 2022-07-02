#include "mainpage.h"
#include "ui_mainpage.h"
#include <QPushButton>
#include <QCommandLinkButton>

MainPage::MainPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);

}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::load_chatrooms(QString wel)
{
    for (int i = 0; i < 10; ++i) {
        QCommandLinkButton* button = new QCommandLinkButton(this);
        button->setText(QString::number(i));
        ui->chatroomsLayout->addWidget(button);
        /*layout()->addWidget(button);*/ // Add the button to the layout
        button->show();
    }
    ui->settingButton->setText(wel);

}

void MainPage::on_pushButton_clicked()
{

}

