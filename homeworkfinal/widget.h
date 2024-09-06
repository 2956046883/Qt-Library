#ifndef WIDGET_H
#define WIDGET_H
#include<QPainter>
#include <QWidget>
#include<QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);

private:
    Ui::Widget *ui;

private slots:
    void on_cancelButton_clicked();
    void on_bt_login_clicked();
    void on_bt_signup_clicked();
    void on_bt_cancel_clicked();
    void on_checkBox_clicked(bool checked);
};
#endif // WIDGET_H
