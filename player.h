#ifndef PLAYER_H
#define PLAYER_H
#include<string>
#include<vector>
#include"poker.h"
#include <QWidget>
#include"QString"

class Player : public QWidget
{
    int id;
    string name;
    int money=0;
    bool isAI;
    vector<Poker*> handPoker;
    vector<Poker*> choosePoker;
    bool isAlive;//是否出局
    int currentBet=0;//当前下注金额
    int totalBet=0;//总共下注金额
    bool isAllIn;//是否全下
    bool isWin;
    Q_OBJECT
public:
    static int currentMaxBet;//当前回合最大下注数
    static int allBet;//底池大小
    Player(int id,string name,bool isAi,int money,QWidget *parent=nullptr):id(id),name(name),money(money),isAI(isAi),QWidget(parent){
        isAlive=true;
        isAllIn=false;
        isWin=false;
        currentBet=0;
        totalBet=0;
    }
        ~Player(){};
        bool &getisAI();
        int &getCurrentBet();
        int &gettotalBet();
        bool &getIsAlive();
        bool &getIsAllIn();
        bool &get_iswin();
        bool set_iswin(bool x);
        string getName();
        int &getMoney();
        int setMoney(int x);
        int &getid();
        vector<Poker*> &getHandPoker();
        vector<Poker*> &getChoosePoker();
        void set_isAlive(bool x);
        int bet(int amount);//玩家下注
        int call();//玩家跟注。
        int raise(int amount);//玩家加注。
        int check();//玩家过牌。
        int allIn();//玩家全下
        int fold();//玩家弃牌
        void Action();
        void ShowHandPoker();
        void ShowchoosePoker();
signals:
};

#endif // PLAYER_H
