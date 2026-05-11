#ifndef POKER_H
#define POKER_H
#include <QWidget>
#include"QPainter"
#include"QPixmap"
#include"qstring.h"
#include"QPushButton"
using namespace std;

enum Suit
{  heart,//红桃
  diamond,//方块
  club,//梅花
  spade//黑桃
};

enum Count
{
    two=2,three,four,five,six,seven,eight,nine,ten,j,q,k,a
};


class Poker : public QWidget
{
    Suit suit;//花色
    Count count;//点数
    Q_OBJECT
public:
    Poker(Suit suit,Count count,QWidget *parent = nullptr):suit(suit),count(count),QWidget(parent){
        QString path=":/resource/"+SuitToString()+CountToString()+".png";
        pix.load(path);
    };
    QPixmap pix;
    Suit getSuit();
    Count getCount();
    void setSuit(Suit suit);
    void setCount(Count count);
    QString SuitToString();
    QString CountToString();
    ~Poker(){};
signals:
};
#endif // POKER_H
