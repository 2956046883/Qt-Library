#ifndef SUPER_EXPLORE_H
#define SUPER_EXPLORE_H

#include <QWidget>
#include<QPainter>
namespace Ui {
class super_explore;
}

class super_explore : public QWidget
{
    Q_OBJECT

public:
    void SetStr(QString a){
        str=a;
    }
    explicit super_explore(QString a,QWidget *parent = nullptr);
    ~super_explore();
    void AppendOneRow(QString expltype,QString bookname, QString author, QString Bookid, bool isborrow, QString borrowname, QString borrowid, QString date,int numincopies, int hasborrow, int hasnotborrow);
    void paintEvent(QPaintEvent *event);
private:
    Ui::super_explore *ui;
    QString str;
signals:
    void back();
private slots:
    void on_bt_explore_clicked();
    void on_bt_back_clicked();
    void on_bt_quit_clicked();

protected:
    void closeEvent(QCloseEvent *event)override;
};

#endif // SUPER_EXPLORE_H
