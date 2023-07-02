
#include "ui_hello.h"
#include <QDebug>
#include "hello.h"
#include "BaseClass.h"

int page=0;//0 主界面，1 登录界面， 2注册界面
std::string NAME="";
int tmppage=1;//记录小页面数(1正常，2非法用户名，3已存在用户名)
int Page=0;
const int archives_per_page=5;
int page_update=1;
bool ALL_INIT=true;//重新加载窗口
archive_system AS;
archive Now_player;
Hello::Hello(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hello)
{
    ui->setupUi(this);

}

Hello::~Hello()
{
    delete ui;
}

void Hello::init(){
    qDebug()<<"init";
    ui->pushButton1->setVisible(false);ui->pushButton2->setVisible(false);
    ui->lineEdit->setVisible(false);ui->listWidget->setVisible(false);
    ui->pushButton->setVisible(false);ui->register_instruction->setVisible(false);
}
void ALL_init(){
    AS.Root_place="Archives";AS.Read_all_archive("Archives");page=Page=0;page_update=tmppage=1;
}
void Hello::paintEvent(QPaintEvent *e){
    if(ALL_INIT)ALL_init(),ALL_INIT=false,ui->lineEdit->clear();
    if(!page_update)return;
    else page_update=0;
    init();
    Page++;
    qDebug()<<"NOWPAINt"<<Page;

    if(page==0){
        ui->pushButton->setVisible(true);
        ui->label->setText("Crazy Meals");
        ui->pushButton1->setVisible(true);ui->pushButton2->setVisible(true);
        ui->pushButton1->setText("Login");ui->pushButton2->setText("Register");
    }
    else if(page==1){
        ui->pushButton->setVisible(true);
        ui->listWidget->setVisible(true);
        ui->pushButton1->setVisible(true);ui->pushButton2->setVisible(true);
        ui->pushButton1->setText("Former");ui->pushButton2->setText("Next");
        if(tmppage<=1)ui->pushButton1->setVisible(false);
        ui->listWidget->clear();
        vector<string>Q=AS.Getpage(tmppage,archives_per_page);
        if(Q.empty())return;
        for(int i=Q.size()-1;i>=0;i--){
            ui->listWidget->addItem(QString::fromStdString(Q[i]));
        }
    }
    else if(page==2){
        ui->register_instruction->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->lineEdit->setVisible(true);
        if(tmppage==1)ui->register_instruction->setText("Only alpha is allowed in your username");
        else if(tmppage==2)ui->register_instruction->setText("Only alpha is allowed in your username\nInvalid username");
        else if(tmppage==3)ui->register_instruction->setText("Only alpha is allowed in your username\nThis username exsited,Please directly login");
    }
    else if(page==3){
        ALL_INIT=true;
        BaseClass::Logic(2,1);return;
    }

}
void Hello::mousePressEvent(QMouseEvent *e){}
void Hello::on_pushButton1_clicked()
{
    page_update=1;
    if(page==0)page=1,tmppage=1;
    else{
        tmppage--;
    }
    repaint();
}


void Hello::on_pushButton2_clicked()
{
    page_update=1;
    qDebug()<<"pushButton2";
    if(page==0)page=2,tmppage=1;
    else if(page==1)tmppage++;
    repaint();
    return;
}


void Hello::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    page_update=1;
    page=3;NAME=item->text().toStdString();
    Now_player=AS.Get_name(NAME);
    ALL_INIT=true;
    BaseClass::Logic(2,1);
    return;
}


void Hello::on_lineEdit_returnPressed()
{
    page_update=1;
    QString tryname=ui->lineEdit->text();
    string Tryname=tryname.toStdString();
    bool legal=true;
    for(int i=Tryname.length()-1;i>=0;i--){
        if(!isalpha(Tryname[i])){
            legal=false;break;
        }
    }
    if(legal){
        if(AS.find_name(Tryname)){
            tmppage=3;
        }
        else {
            AS.Build_new(Tryname);page=3;NAME=Tryname;
            Now_player=AS.Get_name(Tryname);
        }
    }
    else{
        tmppage=2;
    }
    repaint();
}


void Hello::on_pushButton_clicked()
{
    if(!page)qApp->quit();
    page_update=1;
    page=0;repaint();
}

