#ifndef DECK_H
#define DECK_H
#include"poker.h"
#include<vector>
#include <cstdlib>
#include <ctime>
#include <QWidget>
class Deck : public Poker
{
    Q_OBJECT
public:
    std::vector<Poker*>deck;
    Deck():Poker(Suit::heart,Count::three){
        for(int s=heart;s<=spade;s++)
        {
            for(int c=two;c<=a;c++)
            {
               deck.push_back(new Poker(static_cast<Suit>(s),static_cast<Count>(c)));
            }
        }
    }
    ~Deck(){
        for(Poker*poker:deck)
        {
            delete poker;
        }
    };
    void shullfe();//洗牌
    Poker* dealPoker();//发一张牌
    Poker& operator[](int index) {
        if (index < 0 || index >= deck.size()) {
            throw out_of_range("Index out of range");
        }
        return *deck[index];
    }//初始化牌堆
signals:
};

#endif // DECK_H
