#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
protected:
    void paintEvent(QPaintEvent *e) override;
private slots:
    void Do(int u,const QString pic_root);
    void Undo(int u);
    void on_pushButton_00_pressed();

    void on_pushButton_00_released();

    void on_pushButton_01_pressed();

    void on_pushButton_01_released();

    void on_pushButton_02_pressed();

    void on_pushButton_02_released();

    void on_pushButton_03_pressed();

    void on_pushButton_03_released();

    void on_pushButton_04_pressed();

    void on_pushButton_04_released();

    void on_pushButton_05_pressed();

    void on_pushButton_05_released();

    void on_pushButton_06_pressed();

    void on_pushButton_06_released();

    void on_pushButton_07_released();

    void on_pushButton_07_pressed();

    void on_pushButton_08_pressed();

    void on_pushButton_08_released();

    void on_pushButton_09_pressed();

    void on_pushButton_09_released();

    void on_pushButton_10_pressed();

    void on_pushButton_10_released();

    void on_pushButton_11_pressed();

    void on_pushButton_11_released();

    void on_pushButton_12_pressed();

    void on_pushButton_12_released();

    void on_pushButton_13_pressed();

    void on_pushButton_13_released();

    void on_pushButton_14_pressed();

    void on_pushButton_14_released();

    void on_pushButton_15_pressed();

    void on_pushButton_15_released();

    void on_pushButton_16_pressed();

    void on_pushButton_16_released();

    void on_pushButton_17_pressed();

    void on_pushButton_17_released();

    void on_pushButton_18_pressed();

    void on_pushButton_18_released();

    void on_pushButton_19_pressed();

    void on_pushButton_19_released();

    void on_pushButton_20_pressed();

    void on_pushButton_20_released();

    void on_pushButton_21_pressed();

    void on_pushButton_21_released();

    void on_pushButton_22_pressed();

    void on_pushButton_22_released();

    void on_pushButton_23_pressed();

    void on_pushButton_23_released();

    void on_pushButton_24_pressed();

    void on_pushButton_24_released();

    void on_pushButton_25_pressed();

    void on_pushButton_25_released();

    void on_pushButton_26_pressed();

    void on_pushButton_26_released();

    void on_pushButton_27_pressed();

    void on_pushButton_27_released();

    void on_pushButton_28_pressed();

    void on_pushButton_28_released();

    void on_pushButton_29_pressed();

    void on_pushButton_29_released();

    void on_pushButton_30_pressed();

    void on_pushButton_30_released();

    void on_pushButton_31_pressed();

    void on_pushButton_31_released();


    void on_Return_clicked();

    void on_pushButton_clicked();

    void on_choice1_clicked();

    void on_choice2_clicked();

    void on_choice3_clicked();

private:
    Ui::Game *ui;
};

#endif // GAME_H
