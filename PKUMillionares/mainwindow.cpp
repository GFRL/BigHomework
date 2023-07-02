#include "BaseClass.h"
#include "./ui_mainwindow.h"
#include "QMouseEvent"
BubbleTipsWidget* tipps[100];
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);tipps[1]=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    BaseClass::Logic(1,0);
}
void MainWindow::mousePressEvent(QMouseEvent* e){}

void MainWindow::on_pushButton_00_pressed()
{
    if(tipps[1]==NULL)tipps[1]=new BubbleTipsWidget(this);
    QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tipps[1]->setContentFont(f);

        //tipps[1]->setBackColor(48, 49, 51, 240);
        tipps[1]->setDirect(DIRECT::DIRECT_TOP, 0.8);
        tipps[1]->setContent(tr("1823128301239012"),
                         QColor(Qt::white));
    //Now_player.MAP.get_House(0)->get_tips(tipps[1]);
    tipps[1]->show();
}



