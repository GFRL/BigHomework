#include "startmenu.h"
#include "ui_startmenu.h"
#include "BaseClass.h"
StartMenu::StartMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu()
{
    delete ui;
}
void StartMenu::paintEvent(QPaintEvent *e){
    ui->label->setText("Welcome "+QString::fromStdString(Now_player.Name));
}
void StartMenu::mousePressEvent(QMouseEvent *e){
}
void StartMenu::on_pushButton_clicked()
{
    qDebug()<<"Continue!";
    BaseClass::Logic(3,2);
}


void StartMenu::on_startButton_clicked()
{
    qDebug()<<"START!";
    Now_player.init();Now_player.self_Write();
    BaseClass::Logic(3,2);
}


void StartMenu::on_returnButton_clicked()
{
     BaseClass::Logic(1,2);
}

