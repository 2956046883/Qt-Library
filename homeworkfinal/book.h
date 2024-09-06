#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include<QVector>
#include"person.h"
#include<QDateTime>
class Book;
extern int GlobalBook;
extern QVector<Book*>vec;//第一次写这里出现了错误，要存的应该是指针或者引用，否则修改后无法同步
class Book : public QObject
{
    Q_OBJECT

private:
    QString BookName;//通过传入的bknm赋值
    QString Author;//通过传入的小写author赋值
    QString BookID;//通过书加入图书馆的位次自动生成
    int OrderInCopies;//  在构造时 将Book添加后遍历vec获得(构造函数种已实现)
    QString BorrowerName;//初始化为空
    QString BorrowerId;//初始化为空
    int NumOfBorrow;//通过遍历vec实现更新，在构造，即添加新书（已实现），删除书，借书，还书时都要更新
    int NumOfNoBorrow;//通过遍历vec实现更新，在构造，即添加新书（已实现），删除书，借书，还书时都要更新
    bool isborrowed;//构造时默认为零，借书还书时要更新
    bool isInLibrary;//**有着极高的优先级，如果此变量为false那么大部分增删改查操作都不能进行
    QString Date;
public:
    explicit Book(QObject *parent = nullptr);
    //static int GlobalBook;
    Book(const Book&a){
        BookName=a.BookName;
        Author=a.Author;
        BookID=a.BookID;
        OrderInCopies=a.OrderInCopies;
        BorrowerName=a.BorrowerName;
        BorrowerId=a.BorrowerId;
        NumOfBorrow=a.NumOfBorrow;
        NumOfNoBorrow=a.NumOfNoBorrow;
        isborrowed=a.isborrowed;
        isInLibrary=a.isInLibrary;
        Date=a.Date;

    }

    //我们现在来重载一个构造函数，有了这个构造函数，我们可以在文件传入之后更加得体的构造book对象
    Book(QString bknm,QString auth,QString bookid,int order,QString borrownm,QString borrowid,int numofb,int numofnob,bool isb,bool isiLib,QString date){
    BookName=bknm;
    Author=auth;
    BookID=bookid;
    OrderInCopies=order;
    BorrowerName=borrownm;
    BorrowerId=borrowid;
    NumOfBorrow=numofb;
    NumOfNoBorrow=numofnob;
    isborrowed=isb;
    isInLibrary=isiLib;
    Date=date;
    };

    Book operator=(const Book&a){
        BookName=a.BookName;
        Author=a.Author;
        BookID=a.BookID;
        OrderInCopies=a.OrderInCopies;
        BorrowerName=a.BorrowerName;
        BorrowerId=a.BorrowerId;
        NumOfBorrow=a.NumOfBorrow;
        NumOfNoBorrow=a.NumOfNoBorrow;
        isborrowed=a.isborrowed;
        isInLibrary=a.isInLibrary;
        Date=a.Date;
        return *this;
    }
    Book(QString bknm,QString author){
        BookName=bknm;
        Author=author;
        isborrowed=false;
        isInLibrary=true;
        BorrowerName="";
        BorrowerId="";
        Date="";

        GlobalBook++;
        QString a=QString::number(GlobalBook);
        while(a.size()<8){
            a="0"+a;
        }
        BookID=a;
//**************************************以下用来获取numofnoborr，numofborrow,初始化orderincopies**********************************************
        int Counter1=0;//用来计数该种书总数
        int Counter2=0;//用来计数库存

        vec.append(this);//在vector容器中添加Book元素
        for(int i=0;i<vec.size();i++){
            if((*(vec[i])).BookName==BookName&&(*(vec[i])).Author==Author){
                 Counter1++;
                 if((*(vec[i])).isborrowed==false)
                     Counter2++;
            }
        }
        int Counter3=Counter1-Counter2;//用来计数借出的数量
        NumOfBorrow=Counter3;
        NumOfNoBorrow=Counter2;
        OrderInCopies=Counter1;
//****************************************************************************************************************************************



//**************************************以下用来更新与刚刚存入的书是同一种书的numofborrow,numofnoborrow信息**************************************
        for(int i=0;i<vec.size();i++){
            if((*(vec[i])).BookName==BookName&&(*(vec[i])).Author==Author){
                (*(vec[i])).NumOfBorrow=Counter3;
                (*(vec[i])).NumOfNoBorrow=Counter2;
            }
        }
//*****************************************************************************************************************************************



    }
    void ToBorrowBook(person* p){
        //人可以借书的大前提是已经借阅的数量小于2
        if(p->BookNumber_HeHad<2){
            BorrowerId=p->Person_id;
            BorrowerName=p->Person_name;
            isborrowed=true;
            p->BookNumber_HeHad++;
            QDateTime now = QDateTime::currentDateTime();
            Date=QString::number( now.date().year())+"-"+QString::number(now.date().month())+"-"+QString::number(now.date().day());
            //**************************************更新借出后的库存数和借出数******************************************************************
            int Counter1=0;//用来计数该种书总数
            int Counter2=0;//用来计数库存


            for(int i=0;i<vec.size();i++){
                if((*(vec[i])).BookName==BookName&&(*(vec[i])).Author==Author){
                     Counter1++;
                     if((*(vec[i])).isborrowed==false)
                         Counter2++;
                }
            }
            int Counter3=Counter1-Counter2;//用来计数借出的数量
            NumOfBorrow=Counter3;
            NumOfNoBorrow=Counter2;

            //********************************************************************************************************************************
            for(int i=0;i<vec.size();i++){
                if((*(vec[i])).BookName==BookName&&(*(vec[i])).Author==Author){
                    (*(vec[i])).NumOfBorrow=Counter3;
                    (*(vec[i])).NumOfNoBorrow=Counter2;
                }
            }
            //**************************************借出后的库存数和借出数更新完毕******************************************************************

        }



    }
    void ToReturnBook(person* p){
        BorrowerId="";
        BorrowerName="";
        Date="";
        isborrowed=false;
        p->BookNumber_HeHad--;

        //*********************************************************************************************************************************
        int Counter1=0;//用来计数该种书总数
        int Counter2=0;//用来计数库存


        for(int i=0;i<vec.size();i++){
            if((*(vec[i])).BookName==BookName&&(*(vec[i])).Author==Author){
                 Counter1++;
                 if((*(vec[i])).isborrowed==false)
                     Counter2++;
            }
        }
        int Counter3=Counter1-Counter2;//用来计数借出的数量

        NumOfNoBorrow=Counter2;
        NumOfBorrow=Counter3;
       // OrderInCopies=Counter1;
        //**********************************************************************************************************************************
        for(int i=0;i<vec.size();i++){
            if((*(vec[i])).BookName==BookName&&(*(vec[i])).Author==Author){
                (*(vec[i])).NumOfBorrow=Counter3;
                (*(vec[i])).NumOfNoBorrow=Counter2;
            }
        }


    }
    void DeleteBook(){
        //删除书本的操作通过充分利用变量isinlibrary来实现
        //删除操作通过以下两步来实现：1.将 待删除书本对象 的相关属性更改 2.将该Book从容器中移出

        //----------------------STEP1:将 待删除书本对象 的相关属性更改--------------------------
        isInLibrary=false;
        isborrowed=false;
        //考虑到被删除的书以后也可能被查询，因此保留其Bookname,Author以及一定不能删除的Bookid属性是有必要的，而Numberofborrow，Numberofnoborrow，OrderInCopies可以大胆删除（置为零）用来显示已经被删除
        BorrowerId="";
        BorrowerName="";
        Date="";
        OrderInCopies=0;
        NumOfBorrow=0;
        NumOfNoBorrow=0;
        //-----------------------STEP2:从容器中弹出要移除的book-------------------------------
        for(int i=0;i<vec.size();i++){
            if(vec[i]==this){
                vec.remove(i);
            }
        }
        //还需要再次遍历一遍，更改与删除书籍为同一种书的成员变量：库存数和借出数以及OrderInCopies
        //我们注意到，删除书后 该种书的其他副本的成员变量：库存数会减一，借出数不变

        int counter=0;
        for(int i=0;i<vec.size();i++){
            if((*(vec[i])).BookName==BookName&&(*(vec[i])).Author==Author){
                counter++;
                (*(vec[i])).OrderInCopies=counter;
                (*(vec[i])).NumOfNoBorrow--;
            }
        }


    }

    QString GetBookName(){ return BookName;}
    QString GetAuthor(){return Author;}
    QString GetBookID(){return BookID;}
    int GetOrderInCopies(){return OrderInCopies;}
    QString GetBorrowerName(){return BorrowerName;}
    QString GetBorrowID(){return BorrowerId;}
    int GetNumOfBorrow(){return NumOfBorrow;}
    int GetNumOfNoBorrow(){return NumOfNoBorrow;}
    bool Getisborrowed(){return isborrowed;}
    bool GetisInLibrary(){return isInLibrary;}
    QString GetDate(){return Date;}








signals:

};

#endif // BOOK_H
