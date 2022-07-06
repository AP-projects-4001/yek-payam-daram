#include "nameofgroup.h"
#include "ui_nameofgroup.h"

Nameofgroup::Nameofgroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nameofgroup)
{
    ui->setupUi(this);
}

Nameofgroup::~Nameofgroup()
{
    delete ui;
}

void Nameofgroup::on_buttonBox_accepted()
{
    emit name_ofgroup(ui->groupnamelineEdit->text());
}

