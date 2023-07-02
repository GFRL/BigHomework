#ifndef RESULT_H
#define RESULT_H

#include <QMainWindow>

namespace Ui {
class Result;
}

class Result : public QMainWindow
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = nullptr);
    ~Result();
protected:
    void paintEvent(QPaintEvent* e)override;
private slots:
    void on_pushButton_clicked();

private:
    Ui::Result *ui;
};

#endif // RESULT_H
