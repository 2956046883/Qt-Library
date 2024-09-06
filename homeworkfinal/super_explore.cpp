#include "super_explore.h"
#include "ui_super_explore.h"
#include<QVector>
#include"book.h"
#include"person.h"
#include<QMessageBox>
#include<QDebug>
#include<widget.h>
extern QVector<Book*>vec;
extern QVector<person*>vec2;
void super_explore::AppendOneRow(QString expltype, QString bookname, QString author, QString Bookid, bool isborrow, QString borrowname, QString borrowid,QString date, int numincopies, int hasborrow, int hasnotborrow)
{
    int count=ui->tw_library->rowCount();
    ui->tw_library->setRowCount(count+1);

    QTableWidgetItem *extpItem=new QTableWidgetItem(expltype);
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


    extpItem->setTextAlignment(Qt::AlignCenter);
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


    ui->tw_library->setItem(count,0,extpItem);
    ui->tw_library->setItem(count,1,bknmItem);
    ui->tw_library->setItem(count,2,authItem);
    ui->tw_library->setItem(count,3,bkIDItem);
    ui->tw_library->setItem(count,4,isbrItem);
    ui->tw_library->setItem(count,5,brnmItem);
    ui->tw_library->setItem(count,6,brIDItem);
    ui->tw_library->setItem(count,7,dateItem);
    ui->tw_library->setItem(count,8,numinCopyItem);
    ui->tw_library->setItem(count,9,hsbrItem);
    ui->tw_library->setItem(count,10,hnbrItem);


}

void super_explore::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/333.jpg"));
}
super_explore::super_explore(QString a,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::super_explore)
{
    ui->setupUi(this);
    str=a;

ui->le_explore->setText(str);

//----------------------------------------------以下对两个checkbox进行初始化----------------------------------------------
    ui->ckb_OnlyByID->setChecked(false);
    ui->ckb_OnlyDispalyAvailable->setChecked(false);

//----------------------------------------------初始化表格-------------------------------------------------
    ui->tw_library->setColumnCount(11);
    QStringList horizontallist;


    horizontallist<<"搜索关联";
    horizontallist<<"书名";
        horizontallist<<"作者";
        horizontallist<<"登陆号";
        horizontallist<<"状态";
        horizontallist<<"借书人姓名";
        horizontallist<<"借书人ID";
        horizontallist<<"借书日期";
        horizontallist<<"副本编号";
        horizontallist<<"副本借出数";
        horizontallist<<"副本库存";


    ui->tw_library->setHorizontalHeaderLabels(horizontallist);

    //单元格不可以编辑
    ui->tw_library->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置行选择
    ui->tw_library->setSelectionBehavior(QAbstractItemView::SelectRows);


    //设置三种初始化形式
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetBookID()==str){
            QString itm0="Search ID";
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
            AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
        }
    }
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetBookName().contains(str)){
            QString itm0="BookName";
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
            AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
        }
    }
    for(int i=0;i<vec.size();i++){
        if(vec[i]->GetAuthor().contains(str)){
            QString itm0="Author";
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
            AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
        }
    }


}

super_explore::~super_explore()
{
    delete ui;
}

void super_explore::on_bt_explore_clicked()
{
    while (ui->tw_library->rowCount() > 0) {
        ui->tw_library->removeRow(0);}
    QString info=ui->le_explore->text();
    this->SetStr(info);
    if(info==""){
        QMessageBox::information(this,"错误","搜索内容不能为空");
    }
    else{
//----------------------------------------------以下是情况一：仅搜索可借，进搜索id---------------------------------------
        if(ui->ckb_OnlyByID->isChecked()&&ui->ckb_OnlyDispalyAvailable->isChecked()){
            for(int i=0;i<vec.size();i++){
                if(vec[i]->GetisInLibrary()==true&&vec[i]->GetBorrowID()==str&&vec[i]->Getisborrowed()==false){
                    QString itm0="Search ID";
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
                    AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
                }

            }
        }
//----------------------------------------------以上情况一结束---------------------------------------------------------

//----------------------------------------------以下是情况二：仅搜索id，不限制可借----------------------------------------
        if(ui->ckb_OnlyByID->isChecked()&&!ui->ckb_OnlyDispalyAvailable->isCheckable()){

            for(int i=0;i<vec.size();i++){
                if(vec[i]->GetisInLibrary()==true&&vec[i]->GetBookID()==str){
                    QString itm0="Search ID";
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
                    AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
                }
            }
        }
//---------------------------------------------以上情况二结束----------------------------------------------------------

//------------------------------------------以下是情况三：进限制可借，不限制id搜索-----------------------------------------
        if((!ui->ckb_OnlyByID->isChecked())&&ui->ckb_OnlyDispalyAvailable->isChecked()){
            for(int i=0;i<vec.size();i++){
                if(vec[i]->GetisInLibrary()==true&&(!vec[i]->Getisborrowed())&&vec[i]->GetBookID()==str){

                    QString itm0="Search ID";
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
                    AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);

                }


            }
            for(int i=0;i<vec.size();i++){
                if((vec[i]->GetisInLibrary()==true&&!vec[i]->Getisborrowed()==true)&&vec[i]->GetBookName().contains(str)){
                    qDebug()<<vec[i]->Getisborrowed();
                    QString itm0="BookName";
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
                    AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
                }
            }
            for(int i=0;i<vec.size();i++){
                if(vec[i]->GetisInLibrary()==true&&!vec[i]->Getisborrowed()==true&&vec[i]->GetAuthor().contains(str)){
                    QString itm0="Author";
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
                    AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
                }
            }


        }
//--------------------------------------------------情况三结束----------------------------------------------------------
//----------------------------------现在我先去修改一下表格初始化，添加一下搜索关联这一列-------------------------------------
//--------------------------------------------------情况四：不限制id搜索，也不限制未被借出---------------------------------、
        if((!ui->ckb_OnlyByID->isChecked())&&!ui->ckb_OnlyDispalyAvailable->isChecked()){
            for(int i=0;i<vec.size();i++){
                if(vec[i]->GetisInLibrary()==true&&vec[i]->GetBookID()==str){
                    QString itm0="Search ID";
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
                    AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);

                }


            }
            for(int i=0;i<vec.size();i++){
                if(vec[i]->GetisInLibrary()==true&&vec[i]->GetBookName().contains(str)){
                    QString itm0="BookName";
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
                    AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
                }
            }
            for(int i=0;i<vec.size();i++){
                if(vec[i]->GetisInLibrary()==true&&vec[i]->GetAuthor().contains(str)){
                    QString itm0="Author";
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
                    AppendOneRow(itm0,itm1,itm2,itm3,itm4,itm5,itm6,itm7,itm8,itm9,itm10);
                }
            }


        }
//-----------------------------------------------------情况四已经结束--------------------------------------------------------------------------
    }

}

void super_explore::on_bt_back_clicked()
{
    emit back();
}

void super_explore::closeEvent(QCloseEvent *event)
{

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




}

void super_explore::on_bt_quit_clicked()
{
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
