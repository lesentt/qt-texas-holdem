#ifndef GAME_H
#define GAME_H
#include "banker.h"
#include "player.h"
#include "poker.h"
#include <QWidget>
#include <algorithm>
#include <unordered_map>
#include <vector>

class Game
{
public:
    Game() {};
    void endGame(vector<Player *> &player);
    bool isFlush(vector<Poker *> &Poker);
    bool isStraight(vector<Poker *> &Poker);
    unordered_map<int, int> getFrequency(vector<Poker *> &Poker);
    int getType(vector<Poker *> &Poker);
    int getWiner(vector<Player *> &player);
    int comparePokers(Player *player1, Player *player2);
    int compareHands(const vector<Poker *> &hand1, const vector<Poker *> &hand2);
    vector<Poker *> getBestHand(const vector<Poker *> &cards);
signals:
};

#endif // GAME_H
