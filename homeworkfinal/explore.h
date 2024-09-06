#ifndef EXPLORE_H
#define EXPLORE_H

#include <QWidget>

namespace Ui {
class explore;
}

class explore : public QWidget
{
    Q_OBJECT
signals:
    void back();
    void refresh();

public:
    explicit explore(QString a,QWidget *parent = nullptr);
    void AppendOneRow(QString exploreType,QString bookname,QString author,QString Bookid,bool isborrowed);
    ~explore();
void paintEvent(QPaintEvent *event);
    void SetStr(QString a);
    QString GetStr(){return str;}
private slots:
    void on_bt_back_clicked();

    void on_bt_quit_clicked();

    void on_bt_explore_clicked();

    void on_bt_borrow_clicked();

private:
    Ui::explore *ui;
    QString str;
protected:
    void closeEvent(QCloseEvent *event)override;
};

#endif // EXPLORE_H
