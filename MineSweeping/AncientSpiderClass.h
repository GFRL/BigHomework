#ifndef ANCIENTSPIDER_H
#define ANCIENTSPIDER_H
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <algorithm>
#include <random>
#include<ctime>
#include<queue>
using namespace std;

template<class T>
void quick_new(T**& x,int size1,int size2){//this function won't delete x
    x=new T*[size1+2];
    for(int i=0;i<=size1+1;i++)x[i]=new T[size2+2];
}
class AncientSpiderClass{
public:
    bool Generate() {
        uniform_int_distribution<> distrib(0, 1000000000);//设置随机数范围，并为均匀分布
        vector<int>Q;
        for (int i = 0; i <= size1 + 1; i++) {
        for (int j = 0; j <= size2 + 1; j++)
            Mine[i][j] = false, mode[i][j] = 0, surround_mine_num[i][j] = false;
        }
        for (int i = 0; i < size1; i++) {
            for (int j = 0; j < size2; j++)
                Q.push_back(i * size2 + j);
        }
        if (Mine_num >= size1 * size2 - 9)return false;
        else {
            int j = size1 * size2;
            for (int i = 1; i <= Mine_num; i++) {
                int S = distrib(engine) % j;
                int M = Q[S];
                Q.erase(Q.begin() + S);
                int U = S / size2; S -= U * size2;
                Mine[U + 1][S + 1] = true;
                surround_mine_num[U][S]++; surround_mine_num[U + 1][S]++; surround_mine_num[U + 2][S]++;
                surround_mine_num[U][S + 1]++;  surround_mine_num[U + 2][S + 1]++;
                surround_mine_num[U][S + 2]++; surround_mine_num[U + 1][S + 2]++; surround_mine_num[U + 2][S + 2]++;
                j--;
            }
        }
        return true;
    }
    bool able(Point t){
        if(t.x>0&&t.x<=size1&&t.y>0&&t.y<=size2&&mode[t.x][t.y]!=1)return true;else return false;
    }
    void check(){
        int s=0;
        for(int i=1;i<=size1;i++)
            for(int j=1;j<=size2;j++)
                if(mode[i][j]==1)s++;
        if(s+Mine_num==size1*size2)win=true;
    }
    void dfs(int x,int y){
        queue<Point>Q;
        if(Mine[x][y]==true){lose=true;return;}
        Q.push(Point(x,y));
        while(!Q.empty()){
            Point tmp=Q.front();Q.pop();
            mode[tmp.x][tmp.y]=1;
            if(!surround_mine_num[tmp.x][tmp.y]){
                for(int i=0;i<8;i++){
                    if(able(Point(tmp.x+xx[i],tmp.y+yy[i])))mode[tmp.x+xx[i]][tmp.y+yy[i]]=1,Q.push(Point(tmp.x+xx[i],tmp.y+yy[i]));
                }
            }
        }
        check();
        return;
    }
};

void MineSweepingpaint(QPaintEvent* e,MineSweeping& s,QPainter& painter) {
    //
    for(int i=0;i<=s.size1;i++)painter.drawLine(s.baseX,s.baseY+i*s.grid_size,s.baseX+s.size2*s.grid_size,s.baseY+i*s.grid_size);
    for(int i=0;i<=s.size2;i++)painter.drawLine(s.baseX+i*s.grid_size,s.baseY,s.baseX+i*s.grid_size,s.baseY+s.size1*s.grid_size);
    QBrush brush1(QColorConstants::Svg::blue),brush2(QColorConstants::Svg::lightblue),brush3;
    QFont qfont;qfont.setPointSize(10);
    for(int i=1;i<=s.size1;i++)
        for(int j=1;j<=s.size2;j++){
            if(s.mode[i][j]==1){
                painter.setBrush(brush2);
                painter.fillRect(QRect(s.baseX+(i-1)*s.grid_size,s.baseY+(j-1)*s.grid_size,s.grid_size,s.grid_size),brush2);
                if(s.surround_mine_num[i][j]){
                    painter.setPen(Qt::black);
                    painter.setFont(qfont);
                    painter.drawText(QRect(s.baseX+(i-1)*s.grid_size,s.baseY+(j-1)*s.grid_size,s.grid_size,s.grid_size),Qt::AlignHCenter,QString::number(s.surround_mine_num[i][j]));
                }
            }
            else{
                painter.setBrush(brush1);
                painter.fillRect(QRect(s.baseX+(i-1)*s.grid_size,s.baseY+(j-1)*s.grid_size,s.grid_size,s.grid_size),brush1);
                if(s.mode[i][j]==3){
                    painter.setPen(Qt::black);
                    painter.setFont(qfont);
                    painter.drawText(QRect(s.baseX+(i-1)*s.grid_size,s.baseY+(j-1)*s.grid_size,s.grid_size,s.grid_size),Qt::AlignHCenter,"*");
                }
                else if(s.mode[i][j]==2){
                    painter.setPen(Qt::black);
                    painter.setFont(qfont);
                    painter.drawText(QRect(s.baseX+(i-1)*s.grid_size,s.baseY+(j-1)*s.grid_size,s.grid_size,s.grid_size),Qt::AlignHCenter,"?");
                }
            }
        }
    if(s.lose)painter.drawText(QRect(s.baseX+(s.size1+1)*s.grid_size,s.baseY+(s.size2+1)*s.grid_size,s.grid_size*10,s.grid_size*10),Qt::AlignHCenter,"You lose!");
    else if(s.win)painter.drawText(QRect(s.baseX+(s.size1+1)*s.grid_size,s.baseY+(s.size2+1)*s.grid_size,s.grid_size*10,s.grid_size*10),Qt::AlignHCenter,"You win!");
}
void MineSweepingmouse(QMouseEvent* e,MineSweeping& s){
    int MouseX=e->pos().x(),MouseY=e->pos().y();
    if(s.win||s.lose)return;
    MouseX-=s.baseX,MouseY-=s.baseY;
    if(MouseX<0||MouseY<0)return;
    MouseX/=s.grid_size;MouseY/=s.grid_size;
    if(MouseX>=s.size2||MouseY>=s.size1)return;
    MouseX++;MouseY++;
    if(e->button()==Qt::LeftButton){
        if(s.mode[MouseX][MouseY]%2==0)s.dfs(MouseX,MouseY);
        else return;
    }
    else if(e->button()==Qt::RightButton){
        if(s.mode[MouseX][MouseY]==0)s.mode[MouseX][MouseY]=3;
        else if(s.mode[MouseX][MouseY]==1)return;
        else if(s.mode[MouseX][MouseY]==2)s.mode[MouseX][MouseY]=0;
        else if(s.mode[MouseX][MouseY]==3)s.mode[MouseX][MouseY]=2;
    }
}
#endif // MINESWEEPINGCLASS_H

#endif // ANCIENTSPIDER_H
