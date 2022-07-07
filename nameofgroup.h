#ifndef NAMEOFGROUP_H
#define NAMEOFGROUP_H

#include <QDialog>

namespace Ui {
class Nameofgroup;
}

class Nameofgroup : public QDialog
{
    Q_OBJECT

public:
    explicit Nameofgroup(QWidget *parent = nullptr);
    ~Nameofgroup();

private:
    Ui::Nameofgroup *ui;

signals:
    void name_ofgroup(QString);


private slots:
    void on_buttonBox_accepted();
};

#endif // NAMEOFGROUP_H
