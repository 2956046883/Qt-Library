#include "mainoperator.h"
#include "ui_mainoperator.h"
#include "widget.h"
#include<QTableWidget>
#include"explore.h"
#include<QMessageBox>
#include"book.h"
#include<QDebug>
#include<person.h>
extern QVector<Book*>vec;
extern QVector<person*>vc2;
extern QString memo;

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------以下是在重写用户窗口的退出事件，使得程序退出时，book的信息可以写入文件-----------
//-------------------------------------------------------------------------------
void mainoperator::closeEvent(QCloseEvent *event){
    QFile ff("D:\\qt_homework_file2\\book.txt");
    ff.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&ff);
    out.setCodec("UTF-8");

    //现在遍历一遍vec容器，逐一检查对象的属性：isinlibrary是否为真，只有为真才有写文件的资格
    //********记的关闭文件
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetisInLibrary()==true){
            out<<vec[i]->GetBookName() <<endl;
            out<<vec[i]->GetAuthor()<<endl;
            out<<vec[i]->GetBookID()<<endl;

            QString ww=QString::number(vec[i]->GetOrderInCopies());
            out<<ww<<endl;
            out<<vec[i]->GetBorrowerName()<<endl;
            out<<vec[i]->GetBorrowID()<<endl;
            out<<vec[i]->GetDate()<<endl;
            QString ww1=QString::number(vec[i]->GetNumOfBorrow());
            out<<ww1<<endl;
            QString ww2=QString::number(vec[i]->GetNumOfNoBorrow());
            out<<ww2<<endl;
            if(vec[i]->Getisborrowed())
                out<<"true"<<endl;
            else
                out<<"false"<<endl;

            if(vec[i]->GetisInLibrary())
                out<<"true"<<endl;
            else
                out<<"false"<<endl;


        }
    }
    ff.close();

    //接下来要来更新一下person文件
    QFile f2("D:\\qt_homework_file2\\person.txt");
    f2.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out2(&f2);
    out2.setCodec("UTF-8");
    for(int i=0;i<vec2.size();i++){
        out2<<vec2[i]->GetPersonname()<<endl;
        out2<<vec2[i]->GetPersonID()<<endl;
        out2<<vec2[i]->GetBookHeHad()<<endl;
        out2<<vec2[i]->GetPersonType()<<endl;
        out2<<vec2[i]->GetPassword()<<endl;
    }
    f2.close();



};
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------



//--------------------------以下是借书表格的添加函数---------------------------------------------
void mainoperator::AppendOneRowForBorrow(QString bookname,QString author,QString Bookid){
    int count=ui->tw_borrow->rowCount();
    ui->tw_borrow->setRowCount(count+1);
    QTableWidgetItem *bknmitem=new QTableWidgetItem(bookname);
    QTableWidgetItem *authitem=new QTableWidgetItem(author);
    QTableWidgetItem *bkiditem=new QTableWidgetItem(Bookid);


    bknmitem->setTextAlignment(Qt::AlignCenter);
    authitem->setTextAlignment(Qt::AlignCenter);
    bkiditem->setTextAlignment(Qt::AlignCenter);

    ui->tw_borrow->setItem(count,0,bknmitem);
    ui->tw_borrow->setItem(count,1,authitem);
    ui->tw_borrow->setItem(count,2,bkiditem);
};
//--------------------------以上是借书表格的添加函数------------------------------------------------



//--------------------------以下是还书表格的添加函数---------------------------------------------
void mainoperator::AppendOneRowForReturn(QString bookname,QString author,QString Bookid){
    int count=ui->tw_return->rowCount();
    ui->tw_return->setRowCount(count+1);
    QTableWidgetItem *bknmitem=new QTableWidgetItem(bookname);
    QTableWidgetItem *authitem=new QTableWidgetItem(author);
    QTableWidgetItem *bkiditem=new QTableWidgetItem(Bookid);


    bknmitem->setTextAlignment(Qt::AlignCenter);
    authitem->setTextAlignment(Qt::AlignCenter);
    bkiditem->setTextAlignment(Qt::AlignCenter);

    ui->tw_return->setItem(count,0,bknmitem);
    ui->tw_return->setItem(count,1,authitem);
    ui->tw_return->setItem(count,2,bkiditem);
};
//--------------------------以上是还书表格的添加函数------------------------------------------------




mainoperator::mainoperator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainoperator)
{
    //this->ppage=new explore("");
    ui->setupUi(this);
    this->setWindowTitle("用户主界面");


    //connect(this->ppage,&explore::back,this,[=](){
//        this->ppage->hide();
//        this->show();    });





//---------------------------以下对借书表格进行初始化操作-------------------------------------------


        ui->tw_borrow->setColumnCount(3);
        QStringList horizontallist;

        ui->tw_borrow->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tw_borrow->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->tw_borrow->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);



            horizontallist<<"书名";
            horizontallist<<"作者";
            horizontallist<<"登陆号";
            //不必设置状态，因为给借书人浏览的界面就说明是可以借阅的


        ui->tw_borrow->setHorizontalHeaderLabels(horizontallist);


        //单元格不可以编辑
        ui->tw_borrow->setEditTriggers(QAbstractItemView::NoEditTriggers);

        //设置行选择

        ui->tw_borrow->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_borrow->setSelectionMode(QAbstractItemView::SingleSelection);


//---------------------------以上对借书表格初始化---------------------------------------------------




//----------------------------以下对还书表格进行初始化-----------------------------------------------
        ui->tw_return->setColumnCount(3);
        ui->tw_return->setHorizontalHeaderLabels(horizontallist);
        ui->tw_return->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tw_return->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->tw_return->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        //单元格不可以编辑
        ui->tw_return->setEditTriggers(QAbstractItemView::NoEditTriggers);

        //设置行选择

        ui->tw_return->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_return->setSelectionMode(QAbstractItemView::SingleSelection);

//----------------------------以上对还书表格初始化--------------------------------------------------




//--------------------------------下面完成对借书列表的初始化显示--------------------------------------

        //所谓初始化显示就是实现一点击登录就能将可以借阅的书籍显示在表格中

        //先来遍历循环并赋值
        for(int i=0;i<vec.size();i++){
            QString booknm;
            QString author;
            QString bookid;
            if(vec[i]->GetisInLibrary()==true&&vec[i]->Getisborrowed()==false){
                //如果图书在库且没被借出，则图书将值给变量
                booknm=vec[i]->GetBookName();
                author=vec[i]->GetAuthor();
                bookid=vec[i]->GetBookID();

                //接下来要调用append函数将上面的数据写进表格，在此之前要定义append函数
                AppendOneRowForBorrow(booknm,author,bookid);
            }
        }

//--------------------------------以上对借书列表的初始化显示-----------------------------------------



//--------------------------------下面完成对还书列表的初始化显示--------------------------------------
//前面已经引入了全局变量QString memo这个变量的作用就是记录登录者的id
//通过遍历vec（书籍容器）比对借书者id，如果和我设定的memo一样，则把这本书拿出来，并且显示在表格上
//如果后面出现错误，可以用debug输出一下memo和id
//for(int i=0;i<vec.size();i++){
//    if(memo==vec[i]->GetBorrowID()){
//        //如果人一致，则开始显示借的书
//       QString str1=vec[i]->GetBookName();
//       QString str2=vec[i]->GetAuthor();
//       QString str3=vec[i]->GetBookID();
//       AppendOneRowForReturn(str1,str2,str3);
//    }

//}
for(int i=0;i<vec.size();i++){
    QString booknm;
    QString author;
    QString bookid;

    if(memo==vec[i]->GetBorrowID()){

        //如果图书在库且没被借出，则图书将值给变量
        booknm=vec[i]->GetBookName();
        author=vec[i]->GetAuthor();
        bookid=vec[i]->GetBookID();

        //接下来要调用append函数将上面的数据写进表格，在此之前要定义append函数
        AppendOneRowForReturn(booknm,author,bookid);
    }
}

//--------------------------------以上对还书列表的初始化显示-----------------------------------------



}

mainoperator::~mainoperator()
{
    delete ui;
}

void mainoperator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/333.jpg"));
}





//我还是决定用文件来保存数据，现在的问题时在何时打开文件，我的设想是文件仅仅作为容器的一个镜像，作用仅仅是在刚刚创建和关闭程序时，把信息放入容器，而在整个程序过程中都使用容器进行操作
//容器如何使用，就是

void mainoperator::on_bt_quit_clicked()
{
//    Widget *w=new Widget;
//    w->show();
//    this->close();
    int reply;
        reply = QMessageBox::information(this,"提示","您真的要退出吗",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
        if(reply==QMessageBox::Yes){
            this->close();
        Widget *w=new Widget;
            w->show();
            memo="-----{}{}";
        }
        else
            return;


}


//----------------接下来我们先来实现一下搜索功能------------------------

void mainoperator::on_bt_explore_clicked()
{
    QString info= ui->le_explore->text();
    if(info==""){
        QMessageBox::information(this,"错误","搜索信息不能为空");
    }
    else{


    this->ppage=new explore(info);
    connect(this->ppage,&explore::back,this,[=](){
            this->ppage->hide();
            this->show();    });
    ppage->show();
    this->hide();
    connect(this->ppage,&explore::refresh,this,[=](){
        //在这里面完成对表格的刷新
        //-----------------------------------------以下刷新借书表格-----------------------------------------------------------
                    // 从第一行开始，逐行移除
                   while (ui->tw_borrow->rowCount() > 0) {
                       ui->tw_borrow->removeRow(0);}

                   //在打开superviser的ui之前需要将容器中的book对象的信息展示到列表中，这需要我们利用之前定义的appendonerow函数进行赋值我们首先需要读取下来信息
                   for(int i=0;i<vec.size();i++){
                       QString booknm;
                       QString author;
                       QString bookid;
                       if(vec[i]->GetisInLibrary()==true&&vec[i]->Getisborrowed()==false){
                           //如果图书在库且没被借出，则图书将值给变量
                           booknm=vec[i]->GetBookName();
                           author=vec[i]->GetAuthor();
                           bookid=vec[i]->GetBookID();

                           //接下来要调用append函数将上面的数据写进表格，在此之前要定义append函数
                           AppendOneRowForBorrow(booknm,author,bookid);
                       }
                   }
        //-----------------------------------------以上刷新借书表格-----------------------------------------------------------


        //-----------------------------------------以下刷新还书表格-----------------------------------------------------------
                   // 从第一行开始，逐行移除
                  while (ui->tw_return->rowCount() > 0) {
                      ui->tw_return->removeRow(0);}

                  for(int i=0;i<vec.size();i++){
                      QString booknm;
                      QString author;
                      QString bookid;
                      if(vec[i]->GetBorrowID()==memo){
                          //如果图书在库且没被借出，则图书将值给变量
                          booknm=vec[i]->GetBookName();
                          author=vec[i]->GetAuthor();
                          bookid=vec[i]->GetBookID();

                          //接下来要调用append函数将上面的数据写进表格，在此之前要定义append函数
                          AppendOneRowForReturn(booknm,author,bookid);
                      }
                  }
        //-----------------------------------------以上刷新借书表格-----------------------------------------------------------



    });
    }


}

void mainoperator::on_bt_borrow_clicked()
{
    //-------------辅助测试，无用要删去------------
    for(int i=0;i<vec2.size();i++){
        if(memo==vec2[i]->GetPersonID()){

            break;
        }

    }

    //---------------------------------------


//先来判断一下选中的是不是为空

    //
    QList<QTableWidgetItem*> selectedItems = ui->tw_borrow->selectedItems();
    if (!selectedItems.isEmpty()) {
       //有东西被选中
       //接下来需要遍历两个容器
       //先来遍历一下vec2容器：之后看他到底能不能借书
        int i=0;
        for(;i<vec2.size();i++){
            if(memo==vec2[i]->GetPersonID())
                break;
        }


        if(vec2[i]->GetBookHeHad()>=2){
            //有两本书以上，不能再借阅了
            QMessageBox::information(this,"提示","你的借阅数量已达上限\n还书后再借吧");

        }
        else{
            //借的书小于两本可以借阅
            //void ToBorrowBook(person p)

//            int CurrentRow=ui->tw_library->currentRow();
//            QTableWidgetItem*item=ui->tw_library->item(CurrentRow,3);
//            QString text=item->text();
            int currentrow=ui->tw_borrow->currentRow();
            QTableWidgetItem*item=ui->tw_borrow->item(currentrow,2);
            QString tt=item->text();

            //现在来遍历书籍容器,找到id与选中书籍一致的那本书对它进行借书操作
            int m=0;
            for(;m<vec.size();m++){
                if(vec[m]->GetBookID()==tt){
                    //找到了要借的那本书
                    break;
                }
            }
            //通过两个for循环找到了借书人和要借的书分别对应的索引，接下来要对想借的书调用它的借书函数
            vec[m]->ToBorrowBook((vec2[i]));



//-----------------------------------------以下刷新借书表格-----------------------------------------------------------
            // 从第一行开始，逐行移除
           while (ui->tw_borrow->rowCount() > 0) {
               ui->tw_borrow->removeRow(0);}

           //在打开superviser的ui之前需要将容器中的book对象的信息展示到列表中，这需要我们利用之前定义的appendonerow函数进行赋值我们首先需要读取下来信息
           for(int i=0;i<vec.size();i++){
               QString booknm;
               QString author;
               QString bookid;
               if(vec[i]->GetisInLibrary()==true&&vec[i]->Getisborrowed()==false){
                   //如果图书在库且没被借出，则图书将值给变量
                   booknm=vec[i]->GetBookName();
                   author=vec[i]->GetAuthor();
                   bookid=vec[i]->GetBookID();

                   //接下来要调用append函数将上面的数据写进表格，在此之前要定义append函数
                   AppendOneRowForBorrow(booknm,author,bookid);
               }
           }
//-----------------------------------------以上刷新借书表格-----------------------------------------------------------


//-----------------------------------------以下刷新还书表格-----------------------------------------------------------
           // 从第一行开始，逐行移除
          while (ui->tw_return->rowCount() > 0) {
              ui->tw_return->removeRow(0);}

          for(int i=0;i<vec.size();i++){
              QString booknm;
              QString author;
              QString bookid;
              if(vec[i]->GetBorrowID()==memo){
                  //如果图书在库且没被借出，则图书将值给变量
                  booknm=vec[i]->GetBookName();
                  author=vec[i]->GetAuthor();
                  bookid=vec[i]->GetBookID();

                  //接下来要调用append函数将上面的数据写进表格，在此之前要定义append函数
                  AppendOneRowForReturn(booknm,author,bookid);
              }
          }
//-----------------------------------------以上刷新借书表格-----------------------------------------------------------


        }

    }
    else{
        //没有东西被选中
        QMessageBox::warning(this,"错误","当前没有选中任何书籍\n无法进行借阅操作");
    }



}

void mainoperator::on_bt_return_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->tw_return->selectedItems();//先来判断一下选中的语句是否为空
    if (!selectedItems.isEmpty()){
        //能进入这个大括号证明有选中东西
        int i=0;
        for(;i<vec2.size();i++){
            if(memo==vec2[i]->GetPersonID())
                break;
        }//i是当前登录的用户在vec2中的对应索引
        int currentrow=ui->tw_return->currentRow();
        QTableWidgetItem*item=ui->tw_return->item(currentrow,2);
        QString tt=item->text();

        //现在来遍历书籍容器,找到id与选中书籍一致的那本书对它进行借书操作
        int m=0;
        for(;m<vec.size();m++){
            if(vec[m]->GetBookID()==tt){
                //找到了要借的那本书
                break;
            }
        }//m是要还的书在vec中对应的索引
        //接下来我们来阅读一下return函数
        //接着来调用return函数
        vec[m]->ToReturnBook(vec2[i]);

        //-----------------------------------------以下刷新借书表格-----------------------------------------------------------
                    // 从第一行开始，逐行移除
                   while (ui->tw_borrow->rowCount() > 0) {
                       ui->tw_borrow->removeRow(0);}

                   //在打开superviser的ui之前需要将容器中的book对象的信息展示到列表中，这需要我们利用之前定义的appendonerow函数进行赋值我们首先需要读取下来信息
                   for(int i=0;i<vec.size();i++){
                       QString booknm;
                       QString author;
                       QString bookid;
                       if(vec[i]->GetisInLibrary()==true&&vec[i]->Getisborrowed()==false){
                           //如果图书在库且没被借出，则图书将值给变量
                           booknm=vec[i]->GetBookName();
                           author=vec[i]->GetAuthor();
                           bookid=vec[i]->GetBookID();

                           //接下来要调用append函数将上面的数据写进表格，在此之前要定义append函数
                           AppendOneRowForBorrow(booknm,author,bookid);
                       }
                   }
        //-----------------------------------------以上刷新借书表格-----------------------------------------------------------


        //-----------------------------------------以下刷新还书表格-----------------------------------------------------------
                   // 从第一行开始，逐行移除
                  while (ui->tw_return->rowCount() > 0) {
                      ui->tw_return->removeRow(0);}

                  for(int i=0;i<vec.size();i++){
                      QString booknm;
                      QString author;
                      QString bookid;
                      if(vec[i]->GetBorrowID()==memo){
                          //如果图书在库且没被借出，则图书将值给变量
                          booknm=vec[i]->GetBookName();
                          author=vec[i]->GetAuthor();
                          bookid=vec[i]->GetBookID();

                          //接下来要调用append函数将上面的数据写进表格，在此之前要定义append函数
                          AppendOneRowForReturn(booknm,author,bookid);
                      }
                  }
        //-----------------------------------------以上刷新借书表格-----------------------------------------------------------




    }
    else{
        //没有东西被选中
        QMessageBox::warning(this,"错误","当前没有选中任何书籍\n无法进行归还操作");
    }




}
