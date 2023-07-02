#ifndef HELLO_COPY_H
#define HELLO_COPY_H

#include <QMainWindow>
#include <filesystem>
#include<queue>
#include<QListWidget>
#include<fstream>

namespace Ui {
class Hello;
}

class Hello : public QMainWindow
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

public:
    void init();
    explicit Hello(QWidget *parent = nullptr);
    ~Hello();

private slots:

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::Hello *ui;
};

#endif // HELLO_COPY_H
