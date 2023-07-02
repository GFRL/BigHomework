#include"BaseClass.h"
#include "ui_result.h"

Result::Result(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
}

Result::~Result()
{
    delete ui;
}
void Result::paintEvent(QPaintEvent* e){
    std::vector<USER>Q=Now_player.MAP.get_users();
    int now_left=0;
    for(int i=0;i<Q.size();i++){
        if(Q[i].get_days_in_prison()!=114514){now_left=i;break;}
    }
    ui->label->setText("Winner is "+QString::fromStdString(Q[now_left].get_name()));
}
void Result::on_pushButton_clicked()
{
    Now_player.init();Now_player.self_Write();
    BaseClass::Logic(2,3);
}

