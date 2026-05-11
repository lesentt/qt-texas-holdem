#include "deck.h"
#include<iostream>

void Deck::shullfe()
{
    {  srand(static_cast<unsigned int>(time(0)));
        for(int i=0;i<deck.size();i++)
        {
            int j=rand()%(deck.size());
            swap(deck[i],deck[j]);
        }
    }
}

Poker* Deck::dealPoker() {
    if (deck.empty()) {
        std::cerr << "Deck is empty" << std::endl;
        throw std::out_of_range("Deck is empty");
    }
    Poker* poker = deck.back();
    deck.pop_back();
    return poker;
}
