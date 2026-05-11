#ifndef BANKER_H
#define BANKER_H
#include"deck.h"
#include"player.h"
#include"poker.h"
#include <QWidget>

class Banker : public QWidget
{
    Deck &deck;//牌堆
    std::vector<Player*> &players;//参加的玩家
    std::vector<Poker*> tablePoker;//公告牌
    int currentstate=0;//当前游戏状态
    Q_OBJECT
public:
    Banker(Deck &d,vector<Player*> &gamers,QWidget *parent):deck(d),players(gamers),currentstate(0),QWidget(parent){};
    ~Banker(){};
    Deck &getdeck();
    vector<Player*> &getPlayers();
    vector<Poker*> &getTablePoker() ;
    int &getCurrentstate() ;
    void shullefDeck();//洗牌
    void DealPokertoPlayers();//给玩家发牌
    void DealPokertoTable();//发公共牌
    void setCurrentstate(int x);//设置游戏状态
signals:
};
#endif // BANKER_H
