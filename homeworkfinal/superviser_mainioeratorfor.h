#ifndef SUPERVISER_MAINIOERATORFOR_H
#define SUPERVISER_MAINIOERATORFOR_H

#include <QWidget>

#include<QFile>
#include"super_explore.h"
namespace Ui {
class superviser_mainioeratorfor;
}

class superviser_mainioeratorfor : public QWidget
{
    Q_OBJECT

public:
    super_explore *ppp;
    explicit superviser_mainioeratorfor(QWidget *parent = nullptr);
    ~superviser_mainioeratorfor();

    void AppendOneRow(QString bookname,QString author,QString Bookid,bool isborrow,QString borrowname,QString borrowid,QString date,int numincopies,int hasborrow,int hasnotborrow);



//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
protected:
//    void closeEvent(QCloseEvent *event) override {
//        // 在这里执行你的特定操作：将vector中的数据写入文件
//        QFile file("output.txt");
//        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//            QTextStream out(&file);
//            for (int num : myVector) {
//                out << num << "\n";
//            }
//            file.close();
//            qDebug() << "Data written to file successfully.";
//        } else {
//            qDebug() << "Failed to open file for writing.";
//        }

//        // 调用基类的closeEvent以完成其他关闭时的操作
//        QMainWindow::closeEvent(event);
//    }

    void closeEvent(QCloseEvent *event)override;
    void paintEvent(QPaintEvent *event);







//---------------------------------------------------------------------------------


private slots:
    void on_bt_return_clicked();

    void on_bt_addbook_clicked();





    void on_bt_d_clicked();

    void on_bt_explore_clicked();

private:
    Ui::superviser_mainioeratorfor *ui;
signals:
    void back();
};

#endif // SUPERVISER_MAINIOERATORFOR_H
