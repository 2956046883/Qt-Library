#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include<QVector>
#include<QFile>
class person;
//------------------
extern QVector<person*>vec2;

extern int TheGobalNumberOfPerson;
enum persontype{
    student=10,
    librarian=20

};
class Book;
class person : public QObject
{
    Q_OBJECT
    friend class Book;

private:
    QString Person_name;
    QString Person_id;
    int BookNumber_HeHad;
    persontype type;//新加的属性,枚举类形的属性
    QString PassWord;//新添加的密码属性，在构造函数里没有初始化
public:
    explicit person(QObject *parent = nullptr);
    //static int TheGobalNumberOfPerson;



    //设置账号
    void SetPassword(QString pswd){
        PassWord=pswd;

    }


    //设置账号类型
    void SetType(persontype a){
        type=a;
    }
    //获取账号
    QString GetPersonID(){
        return Person_id;
    }
    QString GetPassword(){
        return PassWord;
    }
    persontype GetPersonType(){
        return type;
    }
    QString GetPersonname(){return Person_name;}
    int GetBookHeHad(){return BookNumber_HeHad;}

    //重载一下用于main函数中文件操作来构建person对象的重载函数
    person(QString personname,QString personid,int bookhehad,persontype pt,QString passwd){
        Person_name=personname;
        Person_id=personid;
        BookNumber_HeHad=bookhehad;
        type=pt;
        PassWord=passwd;
    };

    person(QString name){
        Person_name=name;
        TheGobalNumberOfPerson++;
        BookNumber_HeHad=0;

        QString temp=QString::number(TheGobalNumberOfPerson);


        while (temp.size()<6){
            temp="0" + temp;
        }
        Person_id=temp;
    }
    person(const person& a){
        Person_name=a.Person_name;
        Person_id=a.Person_id;
        BookNumber_HeHad=a.BookNumber_HeHad;

    }
    person operator=(const person a){
        Person_name=a.Person_name;
        Person_id=a.Person_id;
        BookNumber_HeHad=a.BookNumber_HeHad;
        type=a.type;
        PassWord=a.PassWord;
        return *this;

    }
    ~person(){}


signals:

};

#endif // PERSON_H
