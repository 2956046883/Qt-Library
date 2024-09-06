#ifndef REGIS_H
#define REGIS_H

#include <QWidget>
#include"person.h"

namespace Ui {
class regis;
}

class regis : public QWidget
{
    Q_OBJECT

public:
    explicit regis(QWidget *parent = nullptr);
    ~regis();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_bt_signup_user_clicked();

    void on_bt_signup_superviser_clicked();

    void on_bt_cancel_clicked();

private:
    Ui::regis *ui;
};

#endif // REGIS_H
