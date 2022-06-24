#include "sign_in.h"
#include "ui_sign_in.h"

Sign_in::Sign_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sign_in)
{
    ui->setupUi(this);
}

Sign_in::~Sign_in()
{
    delete ui;
}

void Sign_in::on_SigninButton_clicked()
{
    //emit(recive_info(ui->lineUserName_sign->text(),ui->lineEmail_sign->text(),ui->linePhoneNumber_sign->text(),ui->linePassword_sign->text(),ui->dateOfBirh->YearSection,ui->dateOfBirh->MonthSection, ui->dateOfBirh->DaySection));
}

