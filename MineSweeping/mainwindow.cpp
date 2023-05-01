#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MineSweepingClass.h"

MineSweeping A(9,9,10);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    A.Generate();
}

int mouseX=0,mouseY=0;

void MainWindow::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    // 在鼠标位置的右下方画一个 100x100 的圆形
    MineSweepingpaint(e,A,painter);
    //painter.drawEllipse(mouseX, mouseY, 100, 100);
}

void MainWindow::mousePressEvent(QMouseEvent* e) {
    // 记录鼠标位置，然后触发重绘
    MineSweepingmouse(e,A);
    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

