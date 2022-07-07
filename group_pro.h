#ifndef GROUP_PRO_H
#define GROUP_PRO_H

#include <QMainWindow>

namespace Ui {
class Group_pro;
}

class Group_pro : public QMainWindow
{
    Q_OBJECT

public:
    explicit Group_pro(QWidget *parent = nullptr);
    ~Group_pro();

private:
    Ui::Group_pro *ui;

public slots:
    void set_subject(QString sub);
    void show_group_members(QString member);
};

#endif // GROUP_PRO_H
