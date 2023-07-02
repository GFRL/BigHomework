#include "BaseClass.h"
#include <QApplication>
MainWindow* BaseClass::w=NULL;
Hello* BaseClass::HELLO=NULL;
StartMenu* BaseClass::STARTMENU=NULL;
Game* BaseClass::GAME=NULL;
Sell* BaseClass::SELL=NULL;
Result* BaseClass::RESULT=NULL;
MineSweepingGame* BaseClass::MINESWEEPINGGAME=NULL;
//Nogo* BaseClass::NOGO=NULL;
std::map<int,QMainWindow*> BaseClass::WINDOWS=std::map<int,QMainWindow*>();
std::default_random_engine Random_Engine(1945);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow W;
    Hello h;
    StartMenu S;
    Game G;
    Sell SE;
    Result R;
    MineSweepingGame M;
    //Nogo N;
    BaseClass::w=&W;
    BaseClass::HELLO=&h;
    BaseClass::STARTMENU=&S;
    BaseClass::GAME=&G;
    BaseClass::SELL=&SE;
    BaseClass::RESULT=&R;
    BaseClass::MINESWEEPINGGAME=&M;
    //BaseClass::NOGO=&N;
    BaseClass::init_WINDOWS();
    W.show();
    return a.exec();
}
