#include "widget.h"

#include <QApplication>
#include<QFile>
#include<QVector>
#include"book.h"
#include"person.h"
#include<QDebug>
#include<QTextStream>
QString memo="-----{}{}";
extern QVector<Book*>vec;
extern QVector<person*>vec2;

int main(int argc, char *argv[])
{

    //----------------------以下代码用来处理两个全局变量-------------------
    //1.TheGobalNumberOfPerson
    extern int TheGobalNumberOfPerson;
    QFile ff("D:\\qt_homework_file2\\personglobal.txt");
    ff.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray ba=ff.readAll();
    TheGobalNumberOfPerson=ba.toInt();
    ff.close();
    //2.GlobalBook
    extern int GlobalBook;
    QFile fff("D:\\qt_homework_file2\\bookglobal.txt");
    fff.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray ba2=fff.readAll();
    GlobalBook=ba2.toInt();
    fff.close();
    //-----------------------------------------------------------------


    //打开文件，通过循环把所需数据压入vec中，实际就是 通过构造函数构造对象，现在我们要重载构造函数，因为从文件中读取的时候
    //需要注意的是我们是按照getline方法获取的，得到的是QString
    QFile file("D:\\qt_homework_file2\\book.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    while(!out.atEnd())
    {
        QString bookName="";//通过传入的bknm赋值
        QString author="";//通过传入的小写author赋值
        QString bookID="";//通过书加入图书馆的位次自动生成
        int orderInCopies=0;//  在构造时 将Book添加后遍历vec获得(构造函数种已实现)
        QString borrowerName="";//初始化为空
        QString borrowerId="";//初始化为空
        QString date="";
        int numOfBorrow=0;//通过遍历vec实现更新，在构造，即添加新书（已实现），删除书，借书，还书时都要更新
        int numOfNoBorrow=0;//通过遍历vec实现更新，在构造，即添加新书（已实现），删除书，借书，还书时都要更新
        bool i_sborrowed;//构造时默认为零，借书还书时要更新
        bool i_sInLibrary;//**有着极高的优先级，如果此变量为false那么大部分增删改查操作都不能进行


     for(int i=0;i<11;i++)
     {

         QString aa=out.readLine();
//         if(aa==""){
//             i--;
//             continue;
//         }

         QString info=aa.trimmed();

         switch (i) {
         case 0:
             bookName=info;
             break;
         case 1:
             author=info;
             break;
         case 2:
             bookID=info;
             break;
         case 3:
             orderInCopies=info.toInt();
             break;
         case 4:
             borrowerName=info;
             break;
         case 5:
             borrowerId=info;
             break;
         case 6:
             date=info;
             break;
         case 7:
             numOfBorrow=info.toInt();
             break;
         case 8:
             numOfNoBorrow=info.toInt();
             break;
         case 9:
             if(info=="true")
                 i_sborrowed=true;
             else
                 i_sborrowed=false;
             break;
         case 10:
             if(info=="true")
                 i_sInLibrary=true;
             else
                 i_sInLibrary=false;
             break;

         }//switch case结束
         //至此我们已经获得了可以用来构建book对象的全部所需的参数，可以开始构建了


     }//for循环结束，我取到了所需的属性
    Book* book=new Book(bookName,author,bookID,orderInCopies,borrowerName,borrowerId,numOfBorrow,numOfNoBorrow,i_sborrowed,i_sInLibrary,date);
     //Book* book=new Book(bookName,author,bookID,orderInCopies,borrowerName,borrowerId,date,numOfBorrow,numOfNoBorrow,i_sborrowed,i_sInLibrary);
     vec.append(book);


    }


    file.close();

    //众所周知，我们这个程序中涉及到两个qvector容器，一个用来存放book，另一个用来存放person
    //对于person我们也采取类似book的操作但不同得是，由于book可能被删除或者借出归还，我们需要在程序结束时写入文件而person一旦创建，大部分属性不会被更改（除了他现在拥有的书本数量）
    //由于person适合调试，我们决定采取在创建时写入文件的操作


    //针对于person的管理员系统我们在界面中点击返回就会退出登录，而点击叉则会直接结束程序，由于整个过程中————只要不关闭程序，无论是登入状态还是登出状态，无论是图书管理员还是读者，这其中内存都没有被释放
    //因此我们在这过程中的任何操作都是基于两个vector容器的操作，并未影响文件，只有在刚刚创建程序和结束程序运行时才会更改文件
    QFile file2("D:\\qt_homework_file2\\person.txt");
    file2.open(QIODevice::ReadOnly);

    while (!file2.atEnd()) {
        QString pername;
        QString perid;
        int bookhehad;
        persontype ptype;
        QString passwd;


        for(int i=0;i<5;i++){
            QByteArray data;
            data=file2.readLine();
            QString info=QString(data);
            info=info.trimmed();
            switch (i) {
            case 0:
                pername=info;
                break;
            case 1:
                perid=info;
                break;
            case 2:
                bookhehad=info.toInt();
                break;
            case 3:
                if(info.toInt()==10)
                    ptype=student;
                else if(info.toInt()==20)
                    ptype=librarian;

                break;
            case 4:
                passwd=info;
                break;


            }

        }
        //接下来需要重载一下person的构造函数然后利用上述的属性来构造person
        person *pn1=new person(pername,perid,bookhehad,ptype,passwd);
        vec2.append(pn1);

        QString help=vec2[0]->GetPassword();


    }
    file2.close();







    //教程说要加上一下一句话
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
