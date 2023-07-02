#ifndef BASECLASS_H
#define BASECLASS_H
#include "mainwindow.h"
#include "hello.h"
#include "bubbletipswidget.h"
#include "startmenu.h"
#include "game.h"
#include "sell.h"
#include "result.h"
#include "minesweepinggame.h"
//#include "nogo.h"
#include <qlabel.h>
#include <map>
#include <QPalette>
#include<vector>
#include<iostream>
#include<filesystem>
#include<random>
#include<ctime>
#include<fstream>
extern std::default_random_engine Random_Engine;

class BaseClass{
public:
    static MainWindow* w;
    static Hello* HELLO;
    static StartMenu* STARTMENU;
    static Game* GAME;
    static Sell* SELL;
    static Result* RESULT;
    static MineSweepingGame* MINESWEEPINGGAME;
    //static Nogo* NOGO;
    static std::map<int,QMainWindow*> WINDOWS;
    static std::map<int,void(*)()>Special_check;
public:
    static inline void init_WINDOWS(){
        WINDOWS[0]=w;WINDOWS[1]=HELLO;WINDOWS[2]=STARTMENU;WINDOWS[3]=GAME;
        WINDOWS[4]=SELL;WINDOWS[5]=RESULT;WINDOWS[6]=MINESWEEPINGGAME;
        //WINDOWS[7]=NOGO;
    }
    static inline void Logic(int page_to_show,int page_to_hide,int special=0){//tmp=0涉及w,B,C切换,tmp=1时涉及身份逻辑跳转
        if(!special){
            WINDOWS[page_to_show]->show(),WINDOWS[page_to_hide]->hide();
        }
        else {
            WINDOWS[page_to_show]->show(),WINDOWS[page_to_hide]->hide();//(*Special_check[special])();
        }
    }
    static inline bool money_transform(int from,int to,int money,int previous_page);//-1是没有，100是银行
};

class House{
public:
    int mode=0;//1住宅，2校车,3交易，4机会，5挑战，6银行，7考场，8命运
    int owner=-1;
    virtual bool upgrade(){return false;}
    virtual int get_penalty(){return 0;}
    virtual int get_upgrade_price(){return 0;}
    virtual int get_sell_price(){return 0;}
    virtual void get_tips(BubbleTipsWidget* tips,const QString pic_root=""){
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
        tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        if(owner!=-1)ANS="房子主人 "+QString::number(owner)+"\n";
        else ANS="房子为空\n";
        ANS+="地皮类型:未知\n";
        ANS+="买卖权限:未知\n";
        ANS+="特殊事件:未知\n";
        tips->setContent(ANS),
                         QColor(Qt::white);
    }
    virtual void get_sell_tips(BubbleTipsWidget* tips,const QString pic_root=""){
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
        tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS=QString::number(get_sell_price());
        ANS="原出售价(不包含折扣，溢价): "+ANS;
        tips->setContent(ANS);
    }
    virtual void init(int new_color=-1){owner=-1;return; }
    virtual void Save(std::ostream& o){ o<<mode<<" "<<owner<<std::endl;return;}
    virtual void Read(std::ifstream& o){o>>mode>>owner;return;}
    virtual void add_money(int value){return ;}

};
class startpoint:public House{
public:
    int get_penalty()override{return 250;}
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
            QFont f;
            f.setFamily("Microsoft YaHei UI");
            f.setPixelSize(14);
            tips->setContentFont(f);
            tips->set_background_rootplace(pic_root);
            //tips->setBackColor(48, 49, 51, 240);
            tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
            QString ANS="";
            ANS+="地皮类型:起点\n";
            ANS+="买卖权限:不可买卖\n";
            ANS+="特殊事件:经过获得1500元\n";
            tips->setContent(ANS),
                             QColor(Qt::white);
        }
};

class apartment:public House{
private:
    int grade;
    int color;
    int data[6][10]={
        {4,200,80,120,160},
        {4,300,120,170,210},
        {4,400,160,220,280},
        {4,500,200,270,340},
        {4,600,240,320,400},
        {4,800,320,420,520}
    };
    int penalty[6][10]={
        {4,500,600,600,800},
        {4,750,1000,1150,1300},
        {4,1000,1200,1400,1600},
        {4,1250,1500,1750,2000},
        {4,1500,1800,2100,2400},
        {4,2000,2400,2800,3200}
    };
    int background_color[6][3]={
        {184,213,247},
        {246,242,164},
        {189,251,193},
        {221,160,139},
        {253,93,93},
        {180,150,214}
    };
    QString Colorname[6]={"Blue","Yellow","Green","Brown","Red","Purple"};
    //紫色>红色>褐色 >绿色>黄色>蓝色 对应5到0,data[i][0]记录一共有几级，此后记录每级多少钱，买完地皮视为一级;
public:
    int get_penalty()override{
        return penalty[color][grade];
    }
    int get_upgrade_price()override{
        return grade<data[color][0]?data[color][grade+1]:0;
    }
    bool upgrade()override{
        if(grade<data[color][0]){
            grade++;return true;
        }
        else return false;
    }
    int get_sell_price()override{
        int sum=0;for(int i=1;i<=grade;i++)sum+=penalty[color][i];
        return sum;
    }
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
        QFont f;

        tips->setBackColor(background_color[color][0],background_color[color][1],background_color[color][2]);
        //pal.setColor(QPalette::Base);
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
        //tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        if(owner!=-1)ANS="房子主人 "+QString::number(owner)+"\n"+"房子数量="+QString::number(grade-1);
        else ANS="房子为空\n";
        //ANS+="售价:"+QString::number(get_upgrade_price());
        //ANS+="地皮类型:住宅("+Colorname[color]+")\n";
        //ANS+="买卖权限:可买卖,可升级\n";
        tips->setContent(ANS),
                         QColor(Qt::white);
    }
    void init(int new_color=-1)override{
        if(new_color!=-1)color=new_color;
        grade=0;owner=-1;

    }
    void Save(std::ostream& o)override{
        o<<mode<<" "<<owner<<std::endl;
        o<<grade<<" "<<color<<std::endl;
    }
    void Read(std::ifstream& o)override{
        o>>mode>>owner;
        o>>grade>>color;
    }
};
class schoolbus:public House{
    int penalty=1000,price=100;
public:
    int get_penalty()override{
        return penalty;
    }
    int get_sell_price()override{
        return price;
    }
    int get_upgrade_price()override{if(owner==-1)return price;else return 0;}
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
        //tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        ANS+="地皮类型:校车\n";
        ANS+="买卖权限:可买卖,不可升级\n";
        ANS+="特殊事件:无\n";
        tips->setContent(ANS),
        QColor(Qt::white);
    }
};
class tradegrid:public House{
public:
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
        //tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        ANS+="地皮类型:交易行\n";
        ANS+="买卖权限:不可买卖,不可升级\n";
        ANS+="特殊事件:拍卖房产，玩家交易房产\n";
        tips->setContent(ANS),
        QColor(Qt::white);
    }
};
class chance:public House{
public:
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
        //tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        ANS+="地皮类型:机会格\n";
        ANS+="买卖权限:不可买卖,不可升级\n";
        ANS+="特殊事件:抽机会卡\n";
        tips->setContent(ANS),
        QColor(Qt::white);
    }
};
class challenge:public House {
public:
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
        //tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        ANS+="地皮类型:挑战格\n";
        ANS+="买卖权限:不可买卖,不可升级\n";
        ANS+="特殊事件:玩小游戏\n";
        tips->setContent(ANS),
        QColor(Qt::white);
    }
};
class exam:public House{
    int get_penalty()override{
        return 1000;
    }
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
        //tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        ANS+="地皮类型:考场格\n";
        ANS+="明天就要考试啦，请你好好复习！暂停一轮";
        ANS+="特殊事件:被迫参加考试\n";
        tips->setContent(ANS),
        QColor(Qt::white);
    }
};
class life:public House{
public:
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
    //    tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        ANS+="地皮类型:命运格\n";
        ANS+="买卖权限:不可买卖,不可升级\n";
        ANS+="特殊事件:抽取buff/debuff\n";
        tips->setContent(ANS),
        QColor(Qt::white);
    }
    std::pair<int,int> get_choice(){
        int s=Random_Engine()%4;
        if(s==1||s==2){
            return std::make_pair(s,1+Random_Engine()%6);
        }
        else if(s==3)return std::make_pair(s,500+Random_Engine()%301);
        else return std::make_pair(s,0);
    }
};
class Bank:public House{
public:
    void get_tips(BubbleTipsWidget* tips,const QString pic_root="")override{
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);
        tips->set_background_rootplace(pic_root);
       // tips->setBackColor(48, 49, 51, 240);
        tips->setDirect(DIRECT::DIRECT_TOP, 0.4);
        QString ANS="";
        ANS+="地皮类型:银行\n";
        ANS+="买卖权限:不可买卖,不可升级\n";
        ANS+="特殊事件:出售财产\n";
        tips->setContent(ANS),
        QColor(Qt::white);
    }
    int money=3000;
    void Save(std::ostream& o)override{
        o<<mode<<" "<<owner<<std::endl;
        o<<money<<std::endl;
    }
    void Read(std::ifstream& o)override{
        o>>mode>>owner;
        o>>money;
    }
    void add_money(int s)override{money+=s;}
};

class MillionaresMap;
class USER{
    std::string name="player_";

    int money=5000,days_in_prison=0;
    MillionaresMap* RootMap;

public:
    int pos;
    bool free_of_penalty=false;
    std::vector<int>house_list;
    int get_money(){return money;}
    void get_label(QLabel* label){
        label->setText(QString::fromStdString("Name: "+name+"\n"
                       +"Money: "+std::to_string(money)+"\n"
                       +"days_in_exam: "+std::to_string(days_in_prison)+"\nposition: "+std::to_string(pos)));
    }
    void add_money(int u){money+=u;}
    virtual void Save(std::ostream& o){
        o<<name<<std::endl;
        o<<house_list.size()<<std::endl;
        for(int i=0;i<house_list.size();i++){
            o<<house_list[i]<<' ';
        }
        o<<std::endl;
        o<<money<<std::endl<<days_in_prison<<std::endl;
        o<<pos<<std::endl;
        o<<std::endl;
    }
    virtual void Read(std::ifstream& o){
        o>>name;
        int tmp;
        o>>tmp;int tmpp;
        for(int i=0;i<tmp;i++){
            o>>tmpp;house_list.push_back(tmpp);
        }
        o>>money>>days_in_prison>>pos;
    }
    std::string& get_name(){
        return name;
    }
    void set_days_in_prison(int u){days_in_prison=u;}
    int& get_days_in_prison(){return days_in_prison;}
};

class MillionaresMap{
private:
    int map_size=32;

    std::map<int,int>grid_mode;
    std::map<int,House*>Q;
    std::vector<std::vector<int>>apartment_data;

public:
    std::vector<USER>users;
    int now_user;
    void init(){
        Q.clear();users.clear();now_user=0;
        users.push_back(USER());users.push_back(USER());
        users[0].get_name()+="_1";users[1].get_name()+="_2";
        apartment_data.push_back(std::vector<int>{2,4,12});
        apartment_data.push_back(std::vector<int>{1,5,7});
        apartment_data.push_back(std::vector<int>{9,14,20});
        apartment_data.push_back(std::vector<int>{18,22,27});
        apartment_data.push_back(std::vector<int>{15,23,25,28});
        apartment_data.push_back(std::vector<int>{17,26,30,31});
        Q[0]=new startpoint();Q[0]->mode=0;
        for(int i=0;i<6;i++){
            for(int j=0;j<apartment_data[i].size();j++){
                Q[apartment_data[i][j]]=new apartment();
                Q[apartment_data[i][j]]->mode=1;
                Q[apartment_data[i][j]]->init(i);
            }
        }
        Q[3]=new schoolbus();Q[10]=new schoolbus();Q[29]=new schoolbus();Q[3]->mode=Q[10]->mode=Q[29]->mode=2;
        Q[6]=Q[13]=new chance();Q[6]->mode=4;
        Q[8]=Q[21]=new tradegrid();Q[8]->mode=Q[21]->mode=3;
        Q[11]=Q[19]=new exam();Q[11]->mode=Q[19]->mode=7;
        //]=new life();Q[13]->mode=8;
        Q[16]=new challenge();Q[16]->mode=5;
        Q[24]=new Bank();Q[24]->mode=6;
        for(int i=0;i<32;i++)Q[i]->owner=-1;
    }
    int size(){return map_size;}
    int get_mode(int i){return grid_mode[i];}
    House* get_House(int u){return Q[u];}
    void Reload(std::ifstream& o){
        o>>map_size;
        init();
        int tmp;o>>tmp;users.clear();
        for(int i=0;i<tmp;i++){
            users.push_back(USER());
            users[i].Read(o);
        }
        for(int i=0;i<map_size;i++){
            Q[i]->Read(o);
        }
        o>>now_user;
    }
    void Save(std::ostream& o){
        o<<map_size<<std::endl;
        o<<users.size()<<std::endl;
        for(int i=0;i<users.size();i++)users[i].Save(o);
        for(int i=0;i<map_size;i++)Q[i]->Save(o);
        o<<now_user<<std::endl;
    }
    std::vector<USER> get_users(){
        return users;
    }
    void house_owner_change(int mode,int bh,int pre_owner,int now_owner,int value){//-1表示银行
        if(mode==1){//sell to bank;
           std::vector<int>::iterator it=users[pre_owner].house_list.begin();
           for(;it<users[pre_owner].house_list.end();it++){
                if(*it==bh)break;
           }
           users[pre_owner].house_list.erase(it);
           Q[bh]->init();
           Q[bh]->owner=now_owner;users[pre_owner].add_money(value);
           Q[24]->add_money(-1*value);
        }
        else{

            users[now_owner].house_list.push_back(bh);
            Q[bh]->owner=now_owner;users[now_owner].add_money(-1*value);Q[bh]->upgrade();
            Q[24]->add_money(value);
        }
    }
    void bankrupty(int u){
        users[u].set_days_in_prison(114514);
        for(int i=0;i<users[u].house_list.size();i++){
            house_owner_change(1,users[u].house_list[i],u,-1,0);
        }
        users[u].house_list.clear();
    }
};
using namespace std;
class archive{
public:
    MillionaresMap MAP;
    string Root_place,Name;
    void Write(ostream& o){
        o<<Name<<endl;
        MAP.Save(o);
    }
    void Read(ifstream& o){
        o>>Name;
        MAP.Reload(o);
    }
    void init(){
        MAP.init();
    }
    void self_Read(){
        ifstream ifs;
        ifs.open(Root_place+"/"+Name+"/total.txt");
        Read(ifs);
    }
    void self_Write(){
        if(Name==""){
            qDebug()<<"Wrong page!";
            return;
        }
        ofstream ofs;
        ofs.open(Root_place+"/"+Name+"/total.txt");
        Write(ofs);
    }
};

class archive_system{
public:
    vector<string>Q;
    int now_page=1;
    string Root_place="1";
    void Read_all_archive(string place){
        Root_place=place;
        Q.clear();
        now_page=1;
        ifstream ifs;
        ifs.open(place+"/total.txt");
        if(ifs.is_open()){
            string tmp;
            while(ifs>>tmp){
                Q.push_back(tmp);
            }
        }
        ifs.close();
    }
    vector<string> Getpage(int& page_num,int num_per_page){
        if(page_num<=0)page_num=1;
        if(Q.size()==0)return vector<string>();
        int m=Q.size()/num_per_page;
        if(Q.size()%num_per_page!=0)m++;
        if(page_num>m)page_num=m;
        int s=page_num*num_per_page;
        if(s>Q.size())s=Q.size();
        return vector<string>(Q.begin()+(page_num-1)*num_per_page,Q.begin()+s);
    }
    bool find_name(string A){
        for(int i=Q.size()-1;i>=0;i--){
            if(Q[i]==A)return true;
        }
        return false;
    }
    archive Get_name(string A){//please be sure that the name exsits
        archive S;
        ifstream ifs;
        ifs.open(Root_place+"/"+A+"/total.txt");
        S.Read(ifs);S.Root_place=Root_place;
        ifs.close();
        return S;
    }
    void Save_name(archive& S,string A){
        ofstream ofs;
        ofs.open(Root_place+"/"+A+"total.txt");
        S.Write(ofs);
        ofs.close();
        return;
    }
    void Build_new(string A){
        ofstream ofs;
        ofs.open(Root_place+"/total.txt",ios::app);
        ofs<<A<<endl;
        Q.push_back(A);
        filesystem::create_directories(Root_place+"/"+A);
        ofs.close();
        ofs.open(Root_place+"/"+A+"/total.txt");
        archive S;S.Name=A;S.Root_place=Root_place;
        S.init();
        S.Write(ofs);
        ofs.close();
    }
};
extern archive Now_player;
bool BaseClass::money_transform(int from,int to,int money,int previous_page){
    bool over=true;
    {
        if(from==100){
            Now_player.MAP.get_House(24)->add_money(-1*money);
        }
        else if(from!=-1){
            if(Now_player.MAP.get_users()[from].get_money()>=money){
                Now_player.MAP.users[from].add_money(-1*money);
            }
            else{
                SELL->set_sell(previous_page,0,from,-1,money-Now_player.MAP.get_users()[from].get_money());
                BaseClass::Logic(4,previous_page);
                return false;
            }
        }
    }
    {
        if(to==100)Now_player.MAP.get_House(24)->add_money(money);
        else if(to!=-1){
            Now_player.MAP.users[to].add_money(money);
        }
    }
    return over;
}
#endif // BASECLASS_H
