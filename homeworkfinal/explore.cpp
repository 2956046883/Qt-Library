#include "explore.h"
#include "ui_explore.h"
#include<QMessageBox>
#include"widget.h"
#include<QVector>
#include"book.h"
#include<QDebug>
extern QString memo;
extern QVector<Book*>vec;


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------以下是在重写explore窗口的退出事件，使得程序退出时，book的信息可以写入文件-----------
//-------------------------------------------------------------------------------
void explore::closeEvent(QCloseEvent *event){
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
void explore::AppendOneRow(QString exploreType,QString bookname,QString author,QString Bookid,bool isborrowed){
    int count=ui->tw_show->rowCount();
    ui->tw_show->setRowCount(count+1);

    QString temp;
    if(isborrowed){
        temp="BORROWED";
    }
    else{temp="AVAILABLE";}

    QTableWidgetItem *extpitem=new QTableWidgetItem(exploreType);
    QTableWidgetItem *bknmitem=new QTableWidgetItem(bookname);
    QTableWidgetItem *authitem=new QTableWidgetItem(author);
    QTableWidgetItem *bkiditem=new QTableWidgetItem(Bookid);
    QTableWidgetItem *modeitem=new QTableWidgetItem(temp);

    extpitem->setTextAlignment(Qt::AlignCenter);
    bknmitem->setTextAlignment(Qt::AlignCenter);
    authitem->setTextAlignment(Qt::AlignCenter);
    bkiditem->setTextAlignment(Qt::AlignCenter);
    modeitem->setTextAlignment(Qt::AlignCenter);

    ui->tw_show->setItem(count,0,extpitem);
    ui->tw_show->setItem(count,1,bknmitem);
    ui->tw_show->setItem(count,2,authitem);
    ui->tw_show->setItem(count,3,bkiditem);
    ui->tw_show->setItem(count,4,modeitem);
};
//--------------------------以上是借书表格的添加函数------------------------------------------------




explore::explore(QString a,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::explore)
{
    qDebug()<<memo;
    ui->setupUi(this);
    this->setWindowTitle("搜索结果");
    str=a;
    //能被成功构建explore界面，就证明在用户主界面搜索的内容不为空，这下子事情就明了一些了
    //与此同时，我们也收获了上一步的搜索内容，这是一个没什么太大作用的参数，仅仅起到把信息传到explore界面的作用

//--------------------------------------------以下完成对表格信息的初始化---------------------------------------------------------
    //这里的表格我要求与之前的表格不同我要添加一个新的列，就是检索类型，并且设置在第一行
    //我还想再多一行就是该书的状态

    ui->tw_show->setColumnCount(5);
    QStringList horizontallist;

    ui->tw_show->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tw_show->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tw_show->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tw_show->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tw_show->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);


        horizontallist<<"搜索关联";
        horizontallist<<"书名";
        horizontallist<<"作者";
        horizontallist<<"登陆号";
        horizontallist<<"书籍状态";


    ui->tw_show->setHorizontalHeaderLabels(horizontallist);

    //单元格不可以编辑
    ui->tw_show->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置行选择

    ui->tw_show->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_show->setSelectionMode(QAbstractItemView::SingleSelection);
//--------------------------------------------以上完成对表格信息的初始化---------------------------------------------------------




//_____________________________________________接下来我们要判断一下，搜索的内容到底能不能和我们的vec关联起来，如果不能，我们的表格不显示，并且弹出提示框_________________________________
    //在str中储藏了一个QString，这个可以与vec同目标对象进行比对
    //一下三种情况我们都可以查找到，并将它加入到表格中
    //1.搜索内容与某本书的bookid完全一致
    //2.搜索内容是某本书书名的一部分或全部
    //3.搜索内容是某本书作者名的一部分或全部
    //我先去重载以下explore的appendonerow函数

    //----------------------------------------情况一--------------------------------------------

    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetisInLibrary()==true&&vec[i]->GetBookID()==str){
            QString itm0="Serach ID";
            auto itm1=vec[i]->GetBookName();
            auto itm2=vec[i]->GetAuthor();
            auto itm3=vec[i]->GetBookID();
            auto itm4=vec[i]->Getisborrowed();

            AppendOneRow(itm0,itm1,itm2,itm3,itm4);
        }
    }
    //----------------------------------------情况一完成-----------------------------------------

    //----------------------------------------情况二---------------------------------------------
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetBookName().contains(str)){
               QString itm0="BookName";
               auto itm1=vec[i]->GetBookName();
               auto itm2=vec[i]->GetAuthor();
               auto itm3=vec[i]->GetBookID();
               auto itm4=vec[i]->Getisborrowed();

               AppendOneRow(itm0,itm1,itm2,itm3,itm4);
        }
    }
    //----------------------------------------情况二完成------------------------------------------

    //----------------------------------------情况三---------------------------------------------
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetAuthor().contains(str)){
               QString itm0="Author";
               auto itm1=vec[i]->GetBookName();
               auto itm2=vec[i]->GetAuthor();
               auto itm3=vec[i]->GetBookID();
               auto itm4=vec[i]->Getisborrowed();

               AppendOneRow(itm0,itm1,itm2,itm3,itm4);
        }
    }
    //----------------------------------------情况三完成------------------------------------------

    //在用户主界面搜索框内输入的值也要拿到第二个界面来
    ui->le_explore->setText(str);



}
explore::~explore()
{
    delete ui;
}

void explore::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/333.jpg"));
}
void explore::SetStr(QString a){str=a;};

void explore::on_bt_back_clicked()
{
    emit back();
}

void explore::on_bt_quit_clicked()
{   int reply;
    reply = QMessageBox::information(this,"提示","您真的要退出吗",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(reply==QMessageBox::Yes){
        Widget *a=new Widget;
        a->show();
        this->close();
        memo="-----{}{}";
    }

}

void explore::on_bt_explore_clicked()
{QString sss=ui->le_explore->text();
    if(sss==""){

        while (ui->tw_show->rowCount() > 0) {
            ui->tw_show->removeRow(0);}
        QMessageBox::information(this,"错误","搜索内容不能为空");

    }
    else{
    //点击搜索的那一刻要先把表格清空
    while (ui->tw_show->rowCount() > 0) {
        ui->tw_show->removeRow(0);}

    QString info=ui->le_explore->text();
    this->SetStr(info);
    //----------------------------------------情况一--------------------------------------------
    qDebug()<<str;
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetisInLibrary()==true&&vec[i]->GetBookID()==str){
            QString itm0="Serach ID";
            auto itm1=vec[i]->GetBookName();
            auto itm2=vec[i]->GetAuthor();
            auto itm3=vec[i]->GetBookID();
            auto itm4=vec[i]->Getisborrowed();
            qDebug()<<vec[i]->Getisborrowed();
            AppendOneRow(itm0,itm1,itm2,itm3,itm4);
        }
    }
    //----------------------------------------情况一完成-----------------------------------------

    //----------------------------------------情况二---------------------------------------------
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetBookName().contains(str)){
               QString itm0="BookName";
               auto itm1=vec[i]->GetBookName();
               auto itm2=vec[i]->GetAuthor();
               auto itm3=vec[i]->GetBookID();
               auto itm4=vec[i]->Getisborrowed();

               AppendOneRow(itm0,itm1,itm2,itm3,itm4);
        }
    }
    //----------------------------------------情况二完成------------------------------------------

    //----------------------------------------情况三---------------------------------------------
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetAuthor().contains(str)){
               QString itm0="Author";
               auto itm1=vec[i]->GetBookName();
               auto itm2=vec[i]->GetAuthor();
               auto itm3=vec[i]->GetBookID();
               auto itm4=vec[i]->Getisborrowed();

               AppendOneRow(itm0,itm1,itm2,itm3,itm4);
        }
    }
    //----------------------------------------情况三完成------------------------------------------

}
}

void explore::on_bt_borrow_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->tw_show->selectedItems();
    if (!selectedItems.isEmpty()){
       //来看一下这本书能不能借阅
        int currentrow=ui->tw_show->currentRow();
        QTableWidgetItem*item=ui->tw_show->item(currentrow,4);
        QString tt=item->text();
        if(tt=="AVAILABLE"){
            //书籍处于可以借阅的状态
            //现在判断这个人借了几本书
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

                int currentrow=ui->tw_show->currentRow();
                QTableWidgetItem*item=ui->tw_show->item(currentrow,3);
                QString mm=item->text();
                qDebug()<<mm;
                //现在来遍历书籍容器,找到id与选中书籍一致的那本书对它进行借书操作
                int m=0;
                for(;m<vec.size();m++){
                    if(vec[m]->GetBookID()==mm){
                        //找到了要借的那本书
                        break;
                    }
                }
                vec[m]->ToBorrowBook((vec2[i]));
                //接线来要刷新当前表格
                while (ui->tw_show->rowCount() > 0) {
                    ui->tw_show->removeRow(0);}
                //----------------------------------------情况一--------------------------------------------
                qDebug()<<str;
                for(int i=0;i<vec.size();i++){
                    if(vec[i]->GetisInLibrary()==true&&vec[i]->GetBookID()==str){
                        QString itm0="Serach ID";
                        auto itm1=vec[i]->GetBookName();
                        auto itm2=vec[i]->GetAuthor();
                        auto itm3=vec[i]->GetBookID();
                        auto itm4=vec[i]->Getisborrowed();
                        qDebug()<<vec[i]->Getisborrowed();
                        AppendOneRow(itm0,itm1,itm2,itm3,itm4);
                    }
                }
                //----------------------------------------情况一完成-----------------------------------------

                //----------------------------------------情况二---------------------------------------------
                for(int i=0;i<vec.size();i++){
                    if(vec[i]->GetBookName().contains(str)){
                           QString itm0="BookName";
                           auto itm1=vec[i]->GetBookName();
                           auto itm2=vec[i]->GetAuthor();
                           auto itm3=vec[i]->GetBookID();
                           auto itm4=vec[i]->Getisborrowed();

                           AppendOneRow(itm0,itm1,itm2,itm3,itm4);
                    }
                }
                //----------------------------------------情况二完成------------------------------------------

                //----------------------------------------情况三---------------------------------------------
                for(int i=0;i<vec.size();i++){
                    if(vec[i]->GetAuthor().contains(str)){
                           QString itm0="Author";
                           auto itm1=vec[i]->GetBookName();
                           auto itm2=vec[i]->GetAuthor();
                           auto itm3=vec[i]->GetBookID();
                           auto itm4=vec[i]->Getisborrowed();

                           AppendOneRow(itm0,itm1,itm2,itm3,itm4);
                    }
                }
                //----------------------------------------情况三完成------------------------------------------
                //现在发送一个emit信号
                emit refresh();

            }


        }
        else{
            QMessageBox::warning(this,"错误","当前书籍已经被借出");
        }

    }
    else{
        //没有东西被选中
        QMessageBox::warning(this,"错误","当前没有选中任何书籍\n无法进行借阅操作");
    }
}
