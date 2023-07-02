#include "BaseClass.h"
#include "ui_minesweepinggame.h"
#include <QPainter>
#include <QPixmap>
#include<iostream>
#include<QDebug>
#include<fstream>
#include <QMessageBox>
#include <QFileDialog>

int MineSweepingGame_update_needed=1;//当其为1的时候，将需要重新加载;
MineSweeping A;

MineSweepingGame::MineSweepingGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MineSweepingGame)
{
    ui->setupUi(this);

}
void MineSweepingGame_update(){
    int x=(Random_Engine()%20)+9;int y=(Random_Engine()%20)+9;int z=(Random_Engine()%15+10)*x*y/100;
    A=MineSweeping(x,y,z);A.Generate();
}
void MineSweepingGame::paintEvent(QPaintEvent* e) {
    if(MineSweepingGame_update_needed)MineSweepingGame_update_needed=0,MineSweepingGame_update();
    if(A.win){
        ui->label_2->setVisible(true);ui->label_2->setText("You Win!");A.over_action();
    }
    else if(A.lose){
        ui->label_2->setVisible(true);ui->label_2->setText("You Lose!");A.over_action();
    }
    QPainter painter(this);
    ui->lcdNumber->display(A.mine_left);
    QPixmap pic;
    qDebug("1.jpg");
    qDebug()<<pic.load("resour1.jpg");
    //QString filePath = QFileDialog::getExistingDirectory(this,"");
    //qDebug()<<filePath;
    ifstream inFile;
    inFile.open("12.txt", ios::in);
        //pic = pic.scaled(this->width(),this->height());
    qDebug()<<inFile.is_open();
    inFile.close();
    painter.drawPixmap(0,0,this->width(),this->height(),pic);
    MineSweepingpaint(e,A,painter);
    //painter.drawEllipse(mouseX, mouseY, 100, 100);

}

void MineSweepingGame::mousePressEvent(QMouseEvent* e) {
    // 记录鼠标位置，然后触发重绘
    MineSweepingmouse(e,A);
    repaint();
}

MineSweepingGame::~MineSweepingGame()
{
    delete ui;
}

void MineSweepingGame::on_pushButton_clicked()
{
    MineSweepingGame_update_needed=1;
    if(A.win){
        Now_player.MAP.users[Now_player.MAP.now_user].add_money(1000);
    }
    BaseClass::Logic(3,6);

}

