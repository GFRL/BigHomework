#include "game.h"
#include "ui_game.h"
#include "BaseClass.h"
#include "bubbletipswidget.h"
#include <QPainter>
#include<thread>
BubbleTipsWidget* tips[100];
/*
    QFont f;
    f.setFamily("Microsoft YaHei UI");
    f.setPixelSize(14);
    tips->setContentFont(f);

    tips->setBackColor(48, 49, 51, 240);
    tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
    tips->setContent(tr("自定义气泡\n气泡大小根据文本大小自适应\n"
                        "设置气泡三角位置以及位置系数"),
                     QColor(Qt::white));
    tips->show();
*/
bool page_init_=true;
int special_mode=0;
QPushButton* map_button[32];
int Widgest_mode=0,Widgest_mode1=0;
Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    for(int i=0;i<Now_player.MAP.size();i++)
        tips[i]=NULL;

    QPushButton* map_button_tmp[32]={
        ui->pushButton_00,ui->pushButton_01,ui->pushButton_02,ui->pushButton_03,ui->pushButton_04,ui->pushButton_05,ui->pushButton_06,ui->pushButton_07,ui->pushButton_08,
        ui->pushButton_09,ui->pushButton_10,ui->pushButton_11,ui->pushButton_12,ui->pushButton_13,ui->pushButton_14,ui->pushButton_15,ui->pushButton_16,ui->pushButton_17,
        ui->pushButton_18,ui->pushButton_19,ui->pushButton_20,ui->pushButton_21,ui->pushButton_22,ui->pushButton_23,ui->pushButton_24,ui->pushButton_25,ui->pushButton_26,
        ui->pushButton_27,ui->pushButton_28,ui->pushButton_29,ui->pushButton_30,ui->pushButton_31};
    memcpy(map_button,map_button_tmp,sizeof(map_button_tmp));
}
void page_init(){
    Now_player.self_Read();
}
void Game::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    //qDebug()<<"ANS!!!"<<this->width()<<" "<<this->height();
    int now__user=Now_player.MAP.now_user;
    int now__user__pos=Now_player.MAP.get_users()[now__user].pos;
    if(Widgest_mode==0){
        ui->widget->hide();ui->pushButton->show();
    }
    else if(Widgest_mode==1){//经过住宅
        ui->pushButton->hide();
        ui->widget->show();
        ui->label->setText("经过住宅!\n您现在的钱: "+QString::number(Now_player.MAP.get_users()[now__user].get_money()));
        if(Now_player.MAP.get_House(now__user__pos)->owner==now__user){
        if(Now_player.MAP.get_House(now__user__pos)->get_upgrade_price()){
                ui->label_detail->setText("这是你的住宅，是否要升级?\n升级需要 "+
                                          QString::number(Now_player.MAP.get_House(now__user__pos)->get_upgrade_price())
                                          +"\n是否需要出售,售价为 "+QString::number(Now_player.MAP.get_House(now__user__pos)->get_sell_price()));
                Widgest_mode1=1;
                ui->choice1->show();ui->choice1->setText("升级");
                ui->choice2->show();ui->choice2->setText("出售");
                ui->choice3->show();ui->choice3->setText("返回");
            }
        else{
            ui->label_detail->setText("这是你的住宅，已经升级到最高级\n是否需要出售,售价为 "
                                      +QString::number(Now_player.MAP.get_House(now__user__pos)->get_sell_price()));
            Widgest_mode1=2;
            ui->choice2->setText("出售");ui->choice3->setText("返回");
            ui->choice1->hide();ui->choice2->show();ui->choice3->show();
            }
        }
        else if(Now_player.MAP.get_House(now__user__pos)->owner==-1){
            ui->label_detail->setText("这是空的住宅，是否要购买?\n购买需要 "+
                                      QString::number(Now_player.MAP.get_House(now__user__pos)->get_upgrade_price()));
            Widgest_mode1=3;
            ui->choice1->setText("购买");ui->choice3->setText("返回");
            ui->choice1->show();ui->choice2->hide();ui->choice3->show();
        }
        else if(Now_player.MAP.get_House(now__user__pos)->owner){
            int penalty=Now_player.MAP.get_House(now__user__pos)->get_penalty();
            if(Now_player.MAP.get_users()[now__user].free_of_penalty){
                ui->label_detail->setText("这是别人的住宅，需要交过路费(已经免费)\n需要支付 "+
                                          QString::number(penalty));
                Widgest_mode1=5;Now_player.MAP.get_users()[now__user].free_of_penalty=false;
                ui->choice3->setText("返回");
                                ui->choice1->hide();ui->choice2->hide();ui->choice3->show();
            }
            else{
                ui->label_detail->setText("这是别人的住宅，需要交过路费\n需要支付 "+
                                      QString::number(penalty));
                Widgest_mode1=4;Now_player.MAP.get_users()[now__user].free_of_penalty=false;
                ui->choice1->show();
                ui->choice1->setText("支付");ui->choice3->setText("破产");ui->choice2->hide();ui->choice3->show();
            }
        }
    }
    else if(Widgest_mode==2){//经过校车
        ui->pushButton->hide();
        ui->widget->show();
        ui->label->setText("经过校车!\n您现在的钱: "+QString::number(Now_player.MAP.get_users()[now__user].get_money()));
        if(Now_player.MAP.get_House(now__user__pos)->owner==now__user){
        ui->label_detail->setText("这是你的校车\n是否需要出售,售价为 "
                                  +QString::number(Now_player.MAP.get_House(now__user__pos)->get_sell_price()));
        Widgest_mode1=2;
        ui->choice2->setText("出售");ui->choice3->setText("返回");
        ui->choice1->hide();ui->choice2->show();ui->choice3->show();
        }
    else if(Now_player.MAP.get_House(now__user__pos)->owner==-1){
        ui->label_detail->setText("这是空的校车，是否要购买?\n购买需要 "+
                                  QString::number(Now_player.MAP.get_House(now__user__pos)->get_upgrade_price()));
        Widgest_mode1=3;
        ui->choice1->setText("购买");ui->choice3->setText("返回");
        ui->choice1->show();ui->choice2->hide();ui->choice3->show();
        }
    else if(Now_player.MAP.get_House(now__user__pos)->owner){
        int penalty=Now_player.MAP.get_House(now__user__pos)->get_penalty();
        if(Now_player.MAP.get_users()[now__user].free_of_penalty){
            ui->label_detail->setText("这是别人的校车，需要交过路费(已经免费)\n需要支付 "+
                                      QString::number(penalty));
            Widgest_mode1=5;Now_player.MAP.get_users()[now__user].free_of_penalty=false;
            ui->choice3->setText("返回");
                            ui->choice1->hide();ui->choice2->hide();ui->choice3->show();
        }
        else{
            ui->label_detail->setText("这是别人的住宅，需要交过路费\n需要支付 "+
                                  QString::number(penalty));
            Widgest_mode1=4;Now_player.MAP.get_users()[now__user].free_of_penalty=false;
            ui->choice1->show();
            ui->choice1->setText("支付");ui->choice3->setText("破产");ui->choice2->hide();ui->choice3->show();
        }
    }
}
    else if(Widgest_mode==3){Widgest_mode=0;}
    else if(Widgest_mode==4){//机会
        ui->pushButton->hide();
        ui->widget->show();
        if(Widgest_mode1==0){
            ui->label->setText("接受命运的审判吧！");
            ui->label_detail->setText("你将随机获得一项buff/debuff");
            ui->choice2->setText("开始抽奖!");ui->choice1->hide();ui->choice2->show();ui->choice3->hide();
        }
        else{
            ui->choice3->setText("返回");ui->choice1->hide();ui->choice3->show();ui->choice2->hide();
        }
    }
    else if(Widgest_mode==5){//挑战
        ui->pushButton->hide();
        ui->widget->show();
        ui->label->setText("迎接你的挑战吧");
        ui->label_detail->setText("门票500;获胜可返回1000和一次掷骰子机会");
        if(Widgest_mode1==0){
            ui->choice1->setText("开始挑战");ui->choice1->show();
        }
        else ui->choice1->hide();
        ui->choice2->hide();ui->choice3->show();
        ui->choice3->setText("返回");
    }
    if(page_init_)page_init_=false,page_init();
    std::vector<USER>Q=Now_player.MAP.get_users();
    int now_left=0;
    for(int i=0;i<Q.size();i++){
        if(Q[i].get_days_in_prison()==114514)continue;
        now_left++;
        int m=Q[i].pos;
        int x=map_button[m]->pos().x(),y=map_button[m]->pos().y();
        painter.setPen(QColor(Qt::red));
        if(m<9){
            painter.drawText(QRectF(x,y-i*10-20,60,60), Qt::AlignHCenter, QString::fromStdString(Q[i].get_name()));//字体水平居中
        }
        else if(m<16){
            painter.drawText(QRectF(x+60,y-i*15+30,60,60), Qt::AlignHCenter, QString::fromStdString(Q[i].get_name()));//字体水平居中
        }
        else if(m<25){
            painter.drawText(QRectF(x,y+i*10+20+60,60,60), Qt::AlignHCenter, QString::fromStdString(Q[i].get_name()));//字体水平居中
        }
        else if(m<32){
            painter.drawText(QRectF(x-60,y-i*15+30,60,60), Qt::AlignHCenter, QString::fromStdString(Q[i].get_name()));//字体水平居中
        }
    }
    if(now_left==1){
        page_init_=true;
        BaseClass::Logic(5,4);
    }
    Q[0].get_label(ui->label_0);Q[1].get_label(ui->label_1);
}
Game::~Game()
{
    delete ui;
}

void Game::Do(int u,const QString pic_root="Resource/lib.jpg"){
    if(tips[u]==NULL)tips[u]=new BubbleTipsWidget(this);
    Now_player.MAP.get_House(u)->get_tips(tips[u],pic_root);
    tips[u]->show();
}
void Game::Undo(int u){
    if(tips[u])tips[u]->hide();
}
void Game::on_pushButton_00_pressed(){Do(0);}
void Game::on_pushButton_00_released(){Undo(0);}
void Game::on_pushButton_01_pressed(){Do(1);}
void Game::on_pushButton_01_released(){Undo(1);}
void Game::on_pushButton_02_pressed(){Do(2,"Resource/54.jpg");}
void Game::on_pushButton_02_released(){Undo(2);}
void Game::on_pushButton_03_pressed(){Do(3);}
void Game::on_pushButton_03_released(){Undo(3);}
void Game::on_pushButton_04_pressed(){Do(4);}
void Game::on_pushButton_04_released(){Undo(4);}
void Game::on_pushButton_05_pressed(){Do(5);}
void Game::on_pushButton_05_released(){Undo(5);}
void Game::on_pushButton_06_pressed(){Do(6);}
void Game::on_pushButton_06_released(){Undo(6);}
void Game::on_pushButton_07_pressed(){Do(7,"Resource/dorm.jpg");}
void Game::on_pushButton_07_released(){Undo(7);}
void Game::on_pushButton_08_pressed(){Do(8);}
void Game::on_pushButton_08_released(){Undo(8);}
void Game::on_pushButton_09_pressed(){Do(9);}
void Game::on_pushButton_09_released(){Undo(9);}
void Game::on_pushButton_10_pressed(){Do(10);}
void Game::on_pushButton_10_released(){Undo(10);}
void Game::on_pushButton_11_pressed(){Do(11);}
void Game::on_pushButton_11_released(){Undo(11);}
void Game::on_pushButton_12_pressed(){Do(12,"Resource/gym2.jpg");}
void Game::on_pushButton_12_released(){Undo(12);}
void Game::on_pushButton_13_pressed(){Do(13);}
void Game::on_pushButton_13_released(){Undo(13);}
void Game::on_pushButton_14_pressed(){Do(14,"Resource/3w.jpg");}
void Game::on_pushButton_14_released(){Undo(14);}
void Game::on_pushButton_15_pressed(){Do(15,"Resource/nongyuan.jpg");}
void Game::on_pushButton_15_released(){Undo(15);}
void Game::on_pushButton_16_pressed(){Do(16);}
void Game::on_pushButton_16_released(){Undo(16);}
void Game::on_pushButton_17_pressed(){Do(17,"Resource/baijiang.jpg");}
void Game::on_pushButton_17_released(){Undo(17);}
void Game::on_pushButton_18_pressed(){Do(18,"Resource/lijiao.jpg");}
void Game::on_pushButton_18_released(){Undo(18);}
void Game::on_pushButton_19_pressed(){Do(19);}
void Game::on_pushButton_19_released(){Undo(19);}
void Game::on_pushButton_20_pressed(){Do(20,"Resource/mellower.jpg");}
void Game::on_pushButton_20_released(){Undo(20);}
void Game::on_pushButton_21_pressed(){Do(21);}
void Game::on_pushButton_21_released(){Undo(21);}
void Game::on_pushButton_22_pressed(){Do(22,"Resource/2class.jpg");}
void Game::on_pushButton_22_released(){Undo(22);}
void Game::on_pushButton_23_pressed(){Do(23);}
void Game::on_pushButton_23_released(){Undo(23);}
void Game::on_pushButton_24_pressed(){Do(24);}
void Game::on_pushButton_24_released(){Undo(24);}
void Game::on_pushButton_25_pressed(){Do(25);}
void Game::on_pushButton_25_released(){Undo(25);}
void Game::on_pushButton_26_pressed(){Do(26,"Resource/lib.jpg");}
void Game::on_pushButton_26_released(){Undo(26);}
void Game::on_pushButton_27_pressed(){Do(27);}
void Game::on_pushButton_27_released(){Undo(27);}
void Game::on_pushButton_28_pressed(){Do(28,"Resource/yannan.jpg");}
void Game::on_pushButton_28_released(){Undo(28);}
void Game::on_pushButton_29_pressed(){Do(29);}
void Game::on_pushButton_29_released(){Undo(29);}
void Game::on_pushButton_30_pressed(){Do(30,"Resource/lake.jpg");}
void Game::on_pushButton_30_released(){Undo(30);}
void Game::on_pushButton_31_pressed(){Do(31,"Resource/newboya.jpg");}
void Game::on_pushButton_31_released(){Undo(31);}



void Game::on_Return_clicked()
{
    Now_player.self_Write();
    page_init_=true;
    BaseClass::Logic(2,3);
}


void Game::on_pushButton_clicked()
{
    /*
    for(int i=0;i<Now_player.MAP.users.size();i++){
        if(Now_player.MAP.users[i].get_days_in_prison()>0&&Now_player.MAP.users[i].get_days_in_prison()!=114514)
            Now_player.MAP.users[i].get_days_in_prison()--;
    }
    */
    if(special_mode){
        if(special_mode==1){
            int tmp=Random_Engine()%6+1;
            while(tmp--){
                Now_player.MAP.users[Now_player.MAP.now_user].pos++;
                if(Now_player.MAP.users[Now_player.MAP.now_user].pos>31){
                    Now_player.MAP.users[Now_player.MAP.now_user].pos-=32;
                    Now_player.MAP.users[Now_player.MAP.now_user].add_money(Now_player.MAP.get_House(0)->get_penalty());
                }
                repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            special_mode=0;
            repaint();
        }
        else if(special_mode==2){
            int tmp=Random_Engine()%6+1;
            while(tmp--){
                Now_player.MAP.users[Now_player.MAP.now_user].pos--;
                if(Now_player.MAP.users[Now_player.MAP.now_user].pos<0){
                    Now_player.MAP.users[Now_player.MAP.now_user].pos+=32;
                }
                repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            special_mode=0;
        }
        else if(special_mode==3){
            Now_player.MAP.users[Now_player.MAP.now_user].get_days_in_prison()++;
            special_mode=0;
        }
        else if(special_mode==4){
            int tmp=Random_Engine()%32;
            Now_player.MAP.users[Now_player.MAP.now_user].pos=tmp;special_mode=0;
        }
        repaint();
        return;
    }

    Now_player.MAP.now_user++;int all_in_prison=0;
    while(1){
        if(Now_player.MAP.now_user>=Now_player.MAP.users.size())Now_player.MAP.now_user-=Now_player.MAP.users.size();
        if(Now_player.MAP.users[Now_player.MAP.now_user].get_days_in_prison()!=114514)break;
    }
    //int tmp=1+Random_Engine()%12;
    if(Now_player.MAP.users[Now_player.MAP.now_user].get_days_in_prison()){
        Now_player.MAP.users[Now_player.MAP.now_user].get_days_in_prison()--;
        ui->widget->show();
        ui->label->setText("您已入狱！本回合停止一回合！");
        return;
    }
    int tmp=Random_Engine()%6+1;
    tmp=1;
    while(tmp--){
        Now_player.MAP.users[Now_player.MAP.now_user].pos++;
        if(Now_player.MAP.users[Now_player.MAP.now_user].pos>31){
            Now_player.MAP.users[Now_player.MAP.now_user].pos-=32;
            Now_player.MAP.users[Now_player.MAP.now_user].add_money(Now_player.MAP.get_House(0)->get_penalty());
        }
        repaint();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    Widgest_mode=Now_player.MAP.get_House(Now_player.MAP.users[Now_player.MAP.now_user].pos)->mode;


    repaint();
}


void Game::on_choice1_clicked()
{
    int now__user=Now_player.MAP.now_user;
    int now__user__pos=Now_player.MAP.get_users()[now__user].pos;
    if(Widgest_mode==1||Widgest_mode==2){
        if(Widgest_mode1==1){
            if(Now_player.MAP.get_users()[now__user].get_money()>=Now_player.MAP.get_House(now__user__pos)->get_upgrade_price()){
                Now_player.MAP.get_House(now__user__pos)->upgrade();
                BaseClass::money_transform(now__user,100,Now_player.MAP.get_House(now__user__pos)->get_upgrade_price(),3);
            }
        }
        else if(Widgest_mode1==3){
            if(Now_player.MAP.get_users()[now__user].get_money()>=Now_player.MAP.get_House(now__user__pos)->get_upgrade_price()){
                Now_player.MAP.house_owner_change(2,now__user__pos,-1,now__user,Now_player.MAP.get_House(now__user__pos)->get_upgrade_price());
            }
        }
        else if(Widgest_mode1==4){
            if(BaseClass::money_transform(now__user,Now_player.MAP.get_House(now__user__pos)->owner,Now_player.MAP.get_House(now__user__pos)->get_penalty(),3)){
                Widgest_mode=0;
            }
        }
    }
    else if(Widgest_mode==5){
        if(Now_player.MAP.users[now__user].get_money()>=500){
            Now_player.MAP.users[now__user].add_money(-500);
            Widgest_mode1=1;
            BaseClass::Logic(6,3);
        }
    }
    repaint();
}


void Game::on_choice2_clicked()
{
    int now__user=Now_player.MAP.now_user;
    int now__user__pos=Now_player.MAP.get_users()[now__user].pos;
    if(Widgest_mode==1||Widgest_mode==2){
        if(Widgest_mode1==3)
            Now_player.MAP.house_owner_change(2,now__user__pos,-1,now__user,Now_player.MAP.get_House(now__user__pos)->get_upgrade_price());
        else if(Widgest_mode1==2||Widgest_mode1==1)
            Now_player.MAP.house_owner_change(1,now__user__pos,now__user,-1,Now_player.MAP.get_House(now__user__pos)->get_sell_price());
    }
    else if(Widgest_mode==4){
        Widgest_mode1=1;
        int tmp=Random_Engine()%4;
        if(tmp==1){
            ui->label_detail->setText("你将多获得一次掷骰子机会!");special_mode=1;
        }
        else if(tmp==2){
            ui->label_detail->setText("你将多获得一次向后移动的掷骰子机会!");special_mode=2;
        }
        else if(tmp==3){
            ui->label_detail->setText("你将入狱!");special_mode=3;
        }
        else if(tmp==4){
            ui->label_detail->setText("你将在下一次随机传送！");special_mode=4;
        }
    }
    repaint();
}


void Game::on_choice3_clicked()
{
    if(Widgest_mode==1||Widgest_mode==2){
        if(Widgest_mode1!=4){
            Widgest_mode=0;Widgest_mode1=0;
            repaint();
        }
        else{
            Now_player.MAP.bankrupty(Now_player.MAP.now_user);
            Widgest_mode=0;Widgest_mode1=0;
            repaint();
        }
    }
    else if(Widgest_mode==4||Widgest_mode==5){
        Widgest_mode=0;Widgest_mode1=0;repaint();
    }
}

