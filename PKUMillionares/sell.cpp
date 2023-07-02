#include "sell.h"
#include "ui_sell.h"
#include "BaseClass.h"
BubbleTipsWidget* tipss=NULL;
Sell::Sell(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sell)
{

    ui->setupUi(this);
}
void Sell::paintEvent(QPaintEvent *e){

    if(mode[0]==0){
         ui->label->setText("你还需要赚"+QString::number(goal_money)+"本次售价将在原价基础上乘50%");
        if(mode[1]>=0){
            std::vector<int>TMP=Now_player.MAP.get_users()[mode[1]].house_list;
            ui->listWidget->clear();
            for(int i=0;i<TMP.size();i++)
                ui->listWidget->addItem(QString::number(TMP[i]));
        }
    }
}
Sell::~Sell()
{
    delete ui;
}

void Sell::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int this_number=item->text().toInt();
    if(!tipss)tipss=new BubbleTipsWidget;
    Now_player.MAP.get_House(this_number)->get_sell_tips(tipss,"");
    tipss->show();
}


void Sell::on_pushButton_clicked()
{
    return;
}


void Sell::on_pushButton_2_clicked()
{
    BaseClass::Logic(previous_page,4);

}


void Sell::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(ui->listWidget->currentItem()==NULL)return;
    int this_number=ui->listWidget->currentItem()->text().toInt();
    Now_player.MAP.house_owner_change(1,this_number,mode[1],-1,Now_player.MAP.get_House(this_number)->get_sell_price()/2);
    goal_money-=Now_player.MAP.get_House(this_number)->get_sell_price()/2;Now_player.MAP.get_House(this_number)->init(-1);
    repaint();
}

