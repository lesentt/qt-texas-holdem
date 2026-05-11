#include"banker.h"
#include"player.h"
#include"poker.h"
#include"deck.h"
#include<iostream>
Deck &Banker::getdeck()
{
    return deck;
}

vector<Player*> &Banker::getPlayers()
{
    return players;
}

vector<Poker*> &Banker::getTablePoker()
{
    return tablePoker;
}

int &Banker::getCurrentstate()
{
    return currentstate;
}

void Banker::shullefDeck()
{
    deck.shullfe();
}

void Banker::DealPokertoPlayers()//给还在场的玩家发两张牌
{
    for(int i=0;i<players.size();i++)
    {
        if(players[i]->getIsAlive()==true)
        {
            for(int j=0;j<2;j++)
            {
                Poker *a=deck.dealPoker();
                players[i]->getHandPoker().push_back(a);
            }
        }
    }


}

void Banker::DealPokertoTable()//发公告牌
{
    switch(currentstate)
    {
    case 2:{
        for(int i=0;i<3;i++)
        {
            tablePoker.push_back(deck.dealPoker());
        }
        cout<<"庄家已发三张牌到公共区"<<endl;
        break;
    }
    case 3:{
        tablePoker.push_back(deck.dealPoker());
        cout<<"庄家已发一张牌到公共区"<<endl;
        break;

    case 4: {
        tablePoker.push_back(deck.dealPoker());
        cout<<"庄家已发一张牌到公共区"<<endl;
        break;
    }
    default:
        break;
    }
    }
}

void Banker::setCurrentstate(int x)
{
    currentstate=x;
    players[0]->currentMaxBet=0;
    players[0]->getCurrentBet()=0;
}
