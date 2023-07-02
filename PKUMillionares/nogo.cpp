#include "nogo.h"
#include "ui_nogo.h"

Nogo::Nogo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Nogo)
{
    ui->setupUi(this);
}

Nogo::~Nogo()
{
    delete ui;
}
