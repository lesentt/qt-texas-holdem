
#include <QApplication>
#include"startgame.h"
#include"gaming.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartGame w;
    w.show();
    return a.exec();
}
