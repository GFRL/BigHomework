#ifndef SELL_H
#define SELL_H
#include "bubbletipswidget.h"
#include <QMainWindow>
#include <qlistwidget.h>
namespace Ui {
class Sell;
}

class Sell : public QMainWindow
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *e) override;

public:
    BubbleTipsWidget* tipss=NULL;
    int mode[3];int goal_money;int previous_page;
    void set_sell(int previous_pages,int modes,int who_to_sell,int who_to_buy,int goal_money=0){
        mode[0]=0;mode[1]=who_to_sell,mode[2]=who_to_buy;previous_page=previous_pages;
    }
    explicit Sell(QWidget *parent = nullptr);
    ~Sell();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Sell *ui;
};

#endif // SELL_H
