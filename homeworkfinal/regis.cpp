#include "regis.h"
#include "ui_regis.h"
#include "widget.h"
#include<QMessageBox>
#include<QString>
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include"book.h"
extern int TheGobalNumberOfPerson;
extern QVector<person*>vec2;
regis::regis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regis)
{
    ui->setupUi(this);
    this->setWindowTitle("用户注册");
    ui->le_passwd->setEchoMode(QLineEdit::Password);
    ui->le_passwd2->setEchoMode(QLineEdit::Password);
    ui->le_passwd->setMaxLength(10);
    ui->le_passwd2->setMaxLength(10);


}

regis::~regis()
{
    delete ui;
}

void regis::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.drawPixmap(0,0,width(),height(),QPixmap(":/zhuce.png"));
}

//注意：注册成功后不是直接进入主页面而是返回到登录界面
//跳转到登录界面
void regis::on_bt_signup_user_clicked()
{   //----------------------------------------------------
    QString str=ui->le_passwd->text();
     if(str.length()<6){
         QMessageBox a;
         a.warning(this,"警告","密码位数太少，请换用安全系数更高的密码");
         return;
     }
     //----------------------------------------------------

     //___________________以下用来验证两次输入的密码是否一致-----
     QString str1=ui->le_passwd->text();
     QString str2=ui->le_passwd2->text();
     int i = QString::compare(str1,str2);
     if(i){
         QMessageBox::warning(this,"警告","两次密码输入不一致");
         return;

     }
     //user的成员对象：
//     QString Person_name;
//     QString Person_id;
//     int BookNumber_HeHad;
//     persontype type;//新加的属性,枚举类形的属性
//     QString PassWord;//新添加的密码属性，在构造函数里没有初始化

     QString str4=ui->le_passwd->text();//获得了密码
     QString str3=ui->le_account->text();//获得了姓名

     person* user=new person(str3);
     user->SetPassword(str4);
     user->SetType(student);
     //至此，user构建完成,要把它压入容器中
     vec2.append(user);

     //我要得到账号，账号就是ID，是固定的，不能自己指定
     QString id=user->GetPersonID();
     QString info="恭喜您，用户注册成功\n您的账号为："+id+"\n请务必牢记";

     QMessageBox a;
     a.about(this,"注册成功",info);

    //通过遍历这个user的属性来写文件
     QFile f("D:\\qt_homework_file2\\person.txt");
     f.open(QIODevice::Append|QIODevice::Text);
     QTextStream out(&f);
     out<<user->GetPersonname()<<endl;
     out<<user->GetPersonID()<<endl;
     out<<user->GetBookHeHad()<<endl;
     out<<user->GetPersonType()<<endl;
     out<<user->GetPassword()<<endl;

     f.close();

     //注册后还要对全局变量进行修改
     QFile f1("D:\\qt_homework_file2\\personglobal.txt");
     f1.open(QIODevice::WriteOnly|QIODevice::Text);
     QByteArray temp=QByteArray::number(TheGobalNumberOfPerson);
     f1.write(temp);
     f1.close();



    Widget*w=new Widget();
    w->show();
    this->hide();

}
//跳转到登录界面
void regis::on_bt_signup_superviser_clicked()
{
    //----------------------------------------------------
        QString str=ui->le_passwd->text();
         if(str.length()<6){
             QMessageBox a;
             a.warning(this,"警告","密码位数太少，请换用安全系数更高的密码");
             return;
         }
         //----------------------------------------------------

         //___________________以下用来验证两次输入的密码是否一致-----
         QString str1=ui->le_passwd->text();
         QString str2=ui->le_passwd2->text();
         int i = QString::compare(str1,str2);
         if(i){
             QMessageBox::warning(this,"警告","两次密码输入不一致");
             return;

         }
         QString str3=ui->le_account->text();//获得用户的名字
         QString str4=ui->le_passwd->text();//获得用户的密码
         person*p=new person(str3);
         p->SetPassword(str4);
         p->SetType(librarian);

         vec2.append(p);
         //得到ID
         QString id=p->GetPersonID();
         QMessageBox a;
         QString info="恭喜您，管理员注册成功\n您的账号为："+id+"\n请务必牢记";
         a.about(this,"注册成功",info);


         //通过遍历这个user的属性来写文件
          QFile f("D:\\qt_homework_file2\\person.txt");
          f.open(QIODevice::Append|QIODevice::Text);
          QTextStream out(&f);
          out.setCodec("UTF-8");
          out<<p->GetPersonname()<<endl;
          out<<p->GetPersonID()<<endl;
          out<<p->GetBookHeHad()<<endl;
          out<<p->GetPersonType()<<endl;
          out<<p->GetPassword()<<endl;

          f.close();



         //注册后对全局变量进行修改
         QFile f1("D:\\qt_homework_file2\\personglobal.txt");
         f1.open(QIODevice::WriteOnly|QIODevice::Text);
         QByteArray temp=QByteArray::number(TheGobalNumberOfPerson);
         f1.write(temp);
         f1.close();


    Widget*w=new Widget();
    w->show();
    this->hide();

}
//跳转到登录界面
void regis::on_bt_cancel_clicked()
{
    Widget*w=new Widget();
    w->show();
    this->hide();

}
