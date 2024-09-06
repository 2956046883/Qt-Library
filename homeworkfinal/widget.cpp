#include "widget.h"
#include "ui_widget.h"
#include "mainoperator.h"
#include "superviser_mainioeratorfor.h"
#include "regis.h"
#include <QMessageBox>
#include"person.h"
#include<QDebug>
extern QString memo;
extern QVector<person*> vec2;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");
    ui->le_passwd->setEchoMode(QLineEdit::Password);
    ui->le_passwd->setMaxLength(10);



    //链接信号与槽
    connect(ui->bt_cancel,&QPushButton::clicked,this,&Widget::on_cancelButton_clicked);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/drawkit-grape-pack-illustration-1.png"));
}

void Widget::on_cancelButton_clicked(){
    this->close();
}




//跳转到主界面，注意 这里的难点是根据账号的不同决定是登录用户主页面还是登录到管理员主界面
void Widget::on_bt_login_clicked()
{//---------------以下实现账号登录的功能--------------------------------
    //1.先从对话框中接收信息O
    //2.拿着账号遍历容器，如果没有对应账号返回警告
    //3.用账号和密码比对，如果一致根据type决定进入管理员界面还是用户界面，如果不一致返回警告
    QString account=ui->le_account->text();
    QString password=ui->le_passwd->text();

    if(account==""||password==""){
        QMessageBox::information(this,"错误","账号或密码未输入");
    }
    else{
    int temp=-1;
    int i=0;
    for(;i<vec2.size();i++)
    {
        if(vec2[i]->GetPersonID()==account)
        {
            temp=i;
            break;
        }
    }
    if(temp==-1){
        QMessageBox::warning(this,"错误","账号未注册");

    }
    else{

        if(vec2[i]->GetPassword()==password){
            //通过get类型来看究竟登录到哪一个界面
            if(vec2[i]->GetPersonType()==10){

                QMessageBox a;
                a.about(this,"欢迎界面","恭喜您，登录成功");
                memo=vec2[i]->GetPersonID();//完成对memo的传值操作

                mainoperator*w=new mainoperator();
                w->show();
                this->hide();


            }
            else{
                QMessageBox a;
                a.about(this,"欢迎界面","恭喜您，登录成功");
                superviser_mainioeratorfor*w=new  superviser_mainioeratorfor();
                w->show();
                this->hide();

            }
        }
       else{
            //弹出警告密码错误
            QMessageBox::warning(this,"错误","账号或密码有误");

        }

    }



}
}


//跳转到注册界面
void Widget::on_bt_signup_clicked()
{
    regis *w=new regis();
    w->show();
    this->hide();

}


//退出
void Widget::on_bt_cancel_clicked()
{


}


//显示密码
void Widget::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        //显示     Normal, NoEcho, Password, PasswordEchoOnEdit   不要忘记在这些枚举类前加上作用于::否则会报错，因为在当前的作用域中没有normal password 这些变量
        ui->le_passwd->setEchoMode(QLineEdit::Normal);
    }
    else{
        //密文
        ui->le_passwd->setEchoMode(QLineEdit::Password);

    }

}
