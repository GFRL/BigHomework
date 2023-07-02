#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>

namespace Ui {
class StartMenu;
}

class StartMenu : public QMainWindow
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

private slots:
    void on_pushButton_clicked();

    void on_startButton_clicked();

    void on_returnButton_clicked();

private:
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
