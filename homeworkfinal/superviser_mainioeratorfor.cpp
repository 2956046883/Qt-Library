#include "superviser_mainioeratorfor.h"
#include "ui_superviser_mainioeratorfor.h"
#include "widget.h"

#include"book.h"
#include<QTableWidget>
#include<QVector>
#include<QDebug>
#include<QMessageBox>
#include<QCheckBox>
#include<QTextStream>
extern int GlobalBook;
extern QVector<Book*>vec;


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------以下是在重写管理员窗口的退出事件，使得程序退出时，book的信息可以写入文件-----------
//-------------------------------------------------------------------------------
void superviser_mainioeratorfor::closeEvent(QCloseEvent *event){
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
this->close();


}

void superviser_mainioeratorfor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/333.jpg"));
};
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------以上是在重写管理员窗口的退出事件，使得程序退出时，book的信息可以写入文件-----------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------


superviser_mainioeratorfor::superviser_mainioeratorfor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::superviser_mainioeratorfor)
{
    ui->setupUi(this);
    this->setWindowTitle("管理员主界面");

    //图书馆列表的设置操作
    ui->tw_library->setColumnCount(10);
    QStringList horizontallist;


        horizontallist<<"书名";
        horizontallist<<"作者";
        horizontallist<<"登陆号";
        horizontallist<<"状态";
        horizontallist<<"借书人姓名";
        horizontallist<<"借书人ID";
        horizontallist<<"借书时间";
        horizontallist<<"副本编号";
        horizontallist<<"副本借出数";
        horizontallist<<"副本库存";


    ui->tw_library->setHorizontalHeaderLabels(horizontallist);

    //设置行表头是否显示
    if(ui->tw_library->horizontalHeader()->isHidden())
        ui->ckb_rowhead->setChecked(false);
    else
        ui->ckb_rowhead->setChecked(true);

    connect(ui->ckb_rowhead,&QCheckBox::stateChanged,this,[=](int state){
        if(state==Qt::Checked){
            ui->tw_library->horizontalHeader()->show();
        }else{
            ui->tw_library->horizontalHeader()->hide();
        }
    });

    //设置列表头是否显示
    if(ui->tw_library->verticalHeader()->isHidden())
        ui->ckb_columnhead->setChecked(false);
    else
        ui->ckb_columnhead->setChecked(true);

    connect(ui->ckb_columnhead,&QCheckBox::stateChanged,[=](int state){
        if(state==Qt::Checked)
           ui->tw_library->verticalHeader()->show();
        else
            ui->tw_library->verticalHeader()->hide();

    });
    //设置交替显示背景色
    if(ui->tw_library->alternatingRowColors())
        ui->ckb_color->setChecked(true);
    else
        ui->ckb_color->setChecked(false);

    connect(ui->ckb_color,&QCheckBox::stateChanged,[this](int state){
        if(state==Qt::Checked)
            ui->tw_library->setAlternatingRowColors(true);
        else
            ui->tw_library->setAlternatingRowColors(false);
    });


    //单元格不可以编辑
    ui->tw_library->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置行选择
    ui->tw_library->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_library->setSelectionMode(QAbstractItemView::SingleSelection);







    //在打开superviser的ui之前需要将容器中的book对象的信息展示到列表中，这需要我们利用之前定义的appendonerow函数进行赋值我们首先需要读取下来信息
    //首先这是一个定数循环因为vec中有多少个对象就要添加几行

        for(int i=0;i<vec.size();i++){
            auto itm1=vec[i]->GetBookName();
            auto itm2=vec[i]->GetAuthor();
            auto itm3=vec[i]->GetBookID();
            auto itm4=vec[i]->Getisborrowed();
            auto itm5=vec[i]->GetBorrowerName();
            auto itm6=vec[i]->GetBorrowID();
            auto itm7=vec[i]->GetDate();
            auto itm8=vec[i]->GetOrderInCopies();
            auto itm9=vec[i]->GetNumOfBorrow();
            auto itm10=vec[i]->GetNumOfNoBorrow();
            AppendOneRow(itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
        }









}

superviser_mainioeratorfor::~superviser_mainioeratorfor()
{
    delete ui;
}


//以下是用来简化表格操作的添加行操作
void superviser_mainioeratorfor::AppendOneRow(QString bookname, QString author, QString Bookid, bool isborrow, QString borrowname, QString borrowid, QString date,int numincopies, int hasborrow, int hasnotborrow)
{
    int count=ui->tw_library->rowCount();
    ui->tw_library->setRowCount(count+1);

    QTableWidgetItem *bknmItem=new QTableWidgetItem(bookname);
    QTableWidgetItem *authItem=new QTableWidgetItem(author);
    QTableWidgetItem *bkIDItem=new QTableWidgetItem(Bookid);
    QTableWidgetItem *isbrItem=new QTableWidgetItem(isborrow==true?"BORROWED":"AVAILABLE");
    QTableWidgetItem *brnmItem=new QTableWidgetItem(borrowname);
    QTableWidgetItem *brIDItem=new QTableWidgetItem(borrowid);
    QTableWidgetItem *dateItem=new QTableWidgetItem(date);
    QTableWidgetItem *numinCopyItem=new QTableWidgetItem(QString::number(numincopies));
    QTableWidgetItem *hsbrItem=new QTableWidgetItem(QString::number(hasborrow));
    QTableWidgetItem *hnbrItem=new QTableWidgetItem(QString::number(hasnotborrow));


    bknmItem->setTextAlignment(Qt::AlignCenter);
    authItem->setTextAlignment(Qt::AlignCenter);
    bkIDItem->setTextAlignment(Qt::AlignCenter);
    isbrItem->setTextAlignment(Qt::AlignCenter);
    brnmItem->setTextAlignment(Qt::AlignCenter);
    brIDItem->setTextAlignment(Qt::AlignCenter);
    dateItem->setTextAlignment(Qt::AlignCenter);
    numinCopyItem->setTextAlignment(Qt::AlignCenter);
    hsbrItem->setTextAlignment(Qt::AlignCenter);
    hnbrItem->setTextAlignment(Qt::AlignCenter);


    ui->tw_library->setItem(count,0,bknmItem);
    ui->tw_library->setItem(count,1,authItem);
    ui->tw_library->setItem(count,2,bkIDItem);
    ui->tw_library->setItem(count,3,isbrItem);
    ui->tw_library->setItem(count,4,brnmItem);
    ui->tw_library->setItem(count,5,brIDItem);
    ui->tw_library->setItem(count,6,dateItem);
    ui->tw_library->setItem(count,7,numinCopyItem);
    ui->tw_library->setItem(count,8,hsbrItem);
    ui->tw_library->setItem(count,9,hnbrItem);


}



//跳转到登录界面
void superviser_mainioeratorfor::on_bt_return_clicked()
{
    //程序运行过程中遇到了逻辑问题：如果刚刚作为管理员添加完一本书籍，不点击叉子关闭程序，而是点击返回来到登录界面，我们再次通过输入账号密码进入到程序中时，会出现表格显示多余内容的问题
    //这是由于我们仅仅点击了返回按钮，内存没有被释放，因此表格也没有被删除
    //我们的解决方案是，在点击返回的时候，就把表格清除掉
    //并弹出警告按钮，你真的要退出吗
    //ui->tw_library->clear();
//--------------------------------------------------------以下是原来写的返回槽函数，但并不能返回到上一个界面-------------------------------------------------------
//    switch( QMessageBox::information(this,"提示","您真的要退出登录吗",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)){
//    case QMessageBox::Yes:
//        this->hide();
//        emit back();
//        ui->tw_library->clear();
//    case QMessageBox::No:
//        return;

//    }
//    Widget*w=new Widget();
//    w->show();
//    this->close();
//}
//---------------------------------------------------------以上是原来写的返回函数-------------------------------------------------------------------------------

    int reply;
        reply = QMessageBox::information(this,"提示","您真的要退出吗",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
        if(reply==QMessageBox::Yes)
        {
            this->close();
            Widget *w=new Widget;
            w->show();
        }
        else{
            return;
        }


}


void superviser_mainioeratorfor::on_bt_addbook_clicked()
{
    //读取添加部件中的两个最关键的信息，书名和作者，将它压入图书容器，并且添加到表格中
    QString bookname=ui->le_bookname->text();
    QString author=ui->le_author->text();
    ui->le_author->setText("");
    ui->le_bookname->setText("");

    if(bookname==""||author==""){
        QMessageBox::warning(this,"错误","书名或作者为空\n这是不被允许的");

    }

    else{
    Book*book=new Book(bookname,author);



    while (ui->tw_library->rowCount() > 0) {
        ui->tw_library->removeRow(0);}

    //在打开superviser的ui之前需要将容器中的book对象的信息展示到列表中，这需要我们利用之前定义的appendonerow函数进行赋值我们首先需要读取下来信息
    //首先这是一个定数循环因为vec中有多少个对象就要添加几行

        for(int i=0;i<vec.size();i++){
            auto itm1=vec[i]->GetBookName();
            auto itm2=vec[i]->GetAuthor();
            auto itm3=vec[i]->GetBookID();
            auto itm4=vec[i]->Getisborrowed();
            auto itm5=vec[i]->GetBorrowerName();
            auto itm6=vec[i]->GetBorrowID();
            auto itm7=vec[i]->GetDate();
            auto itm8=vec[i]->GetOrderInCopies();
            auto itm9=vec[i]->GetNumOfBorrow();
            auto itm10=vec[i]->GetNumOfNoBorrow();
            AppendOneRow(itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
        }

    //现在要做的是添加书本操作时，把书的信息写入书的文件
    QFile f3("D:\\qt_homework_file2\\book.txt");
    f3.open(QIODevice::Append|QIODevice::Text);
    QTextStream out(&f3);
    out.setCodec("UTF-8");

//    QByteArray ba1=book->GetBookName().toLatin1();
//    char*mm=ba1.data();
//    QString hel=QObject::tr(mm);
    out<<book->GetBookName() <<endl;
    out<<book->GetAuthor()<<endl;
    out<<book->GetBookID()<<endl;
    QString ww=QString::number(book->GetOrderInCopies());
    out<<ww<<endl;
    out<<book->GetBorrowerName()<<endl;
    out<<book->GetBorrowID()<<endl;
    out<<book->GetDate()<<endl;
    QString ww1=QString::number(book->GetNumOfBorrow());
    out<<ww1<<endl;
    QString ww2=QString::number(book->GetNumOfNoBorrow());
    out<<ww2<<endl;
    if(book->Getisborrowed())
        out<<"true"<<endl;
    else
        out<<"false"<<endl;

    if(book->GetisInLibrary())
        out<<"true"<<endl;
    else
        out<<"false"<<endl;
    f3.close();



    //改变用来计数的全局变量GlobalBook
    QFile f2("D:\\qt_homework_file2\\bookglobal.txt");
    f2.open(QIODevice::WriteOnly|QIODevice::Text);
    QByteArray temp=QByteArray::number(GlobalBook);
    f2.write(temp);
    f2.close();


    }


}






void superviser_mainioeratorfor::on_bt_d_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->tw_library->selectedItems();
    if (!selectedItems.isEmpty()){
    int reply;
        reply = QMessageBox::warning(this, "删除书籍",
                                     "您确定要删除这本书籍吗？",
                                     QMessageBox::Yes|QMessageBox::No,
                                     QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            //下面来进行检查，如果书籍处在借阅状态则会弹出对话框提示，如果处于在库状态，则完成删除操作
            int CurrentRow=ui->tw_library->currentRow();
            QTableWidgetItem*item=ui->tw_library->item(CurrentRow,3);
            QString text=item->text();
            if(text=="BORROWED"){
                QMessageBox::information(this,"错误","该书处在借出状态，不能删除");
            }
            else{
                //------------------以下开启删除书的操作----------------------
                // 1.表格操作获取被删除这一行对象的uid；
                // 2.遍历容器，对它调用delete函数
                // 3.重新展示一下表格
                //STEP1:---------------------------------------------------
                QTableWidgetItem*item2=ui->tw_library->item(CurrentRow,2);
                QString id= item2->text();
                //STEP2:---------------------------------------------------
                int m=0;
                for(;m<vec.size();m++){
                    if(vec[m]->GetBookID()==id)
                        break;
                }
                //i就是要被删除的对象对应的索引
                vec[m]->DeleteBook();
                //STEP3:---------------------------------------------------
                 // 从第一行开始，逐行移除
                while (ui->tw_library->rowCount() > 0) {
                    ui->tw_library->removeRow(0);}

                //在打开superviser的ui之前需要将容器中的book对象的信息展示到列表中，这需要我们利用之前定义的appendonerow函数进行赋值我们首先需要读取下来信息
                //首先这是一个定数循环因为vec中有多少个对象就要添加几行

                    for(int i=0;i<vec.size();i++){
                        auto itm1=vec[i]->GetBookName();
                        auto itm2=vec[i]->GetAuthor();
                        auto itm3=vec[i]->GetBookID();
                        auto itm4=vec[i]->Getisborrowed();
                        auto itm5=vec[i]->GetBorrowerName();
                        auto itm6=vec[i]->GetBorrowID();
                        auto itm7=vec[i]->GetDate();
                        auto itm8=vec[i]->GetOrderInCopies();
                        auto itm9=vec[i]->GetNumOfBorrow();
                        auto itm10=vec[i]->GetNumOfNoBorrow();
                        AppendOneRow(itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
                    }


            }



        }


 else {}
}
    else{
        QMessageBox::information(this,"错误","选中的内容不可以为空");
    }
}



void superviser_mainioeratorfor::on_bt_explore_clicked()
{
    QString temp=ui->le_explore->text();

    if(temp==""){
        QMessageBox::information(this,"错误","搜索内容不能为空");
    }
    else{
    ppp=new super_explore(temp);
    connect(this->ppp,&super_explore::back,this,[=](){
        this->show();
        this->ppp->hide();
    });
    this->hide();
    ppp->show();
    }

}
