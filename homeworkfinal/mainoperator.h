#ifndef MAINOPERATOR_H
#define MAINOPERATOR_H

#include <QWidget>
#include"explore.h"

namespace Ui {
class mainoperator;
}

class mainoperator : public QWidget
{
    Q_OBJECT

public:
    explicit mainoperator(QWidget *parent = nullptr);
    void AppendOneRowForBorrow(QString bookname,QString author,QString Bookid);
    void AppendOneRowForReturn(QString bookname,QString author,QString Bookid);
    ~mainoperator();
    explore*ppage=NULL;
    void paintEvent(QPaintEvent *event);
private slots:


    void on_bt_quit_clicked();

    void on_bt_explore_clicked();



    void on_bt_borrow_clicked();

    void on_bt_return_clicked();

private:
    Ui::mainoperator *ui;

protected:
    void closeEvent(QCloseEvent *event)override;

};

#endif // MAINOPERATOR_H
