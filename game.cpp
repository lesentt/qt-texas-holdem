#include "game.h"
#include "player.h"
#include "poker.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace {

struct HandRank {
    int type;
    std::vector<int> tieBreakers;
};

std::vector<int> getSortedRanksDesc(std::vector<Poker *> poker)
{
    std::vector<int> ranks;
    ranks.reserve(poker.size());
    for (auto *card : poker) {
        ranks.push_back(card->getCount());
    }
    std::sort(ranks.begin(), ranks.end(), std::greater<int>());
    return ranks;
}

bool isStraightRanks(std::vector<Poker *> poker, int &highCard)
{
    std::vector<int> ranks;
    ranks.reserve(poker.size());
    for (auto *card : poker) {
        ranks.push_back(card->getCount());
    }

    std::sort(ranks.begin(), ranks.end());
    ranks.erase(std::unique(ranks.begin(), ranks.end()), ranks.end());
    if (ranks.size() != 5) {
        return false;
    }

    if (ranks == std::vector<int>{2, 3, 4, 5, 14}) {
        highCard = 5;
        return true;
    }

    for (int i = 1; i < 5; ++i) {
        if (ranks[i] != ranks[i - 1] + 1) {
            return false;
        }
    }

    highCard = ranks.back();
    return true;
}

HandRank evaluateHand(std::vector<Poker *> poker)
{
    std::unordered_map<int, int> freq;
    for (auto *card : poker) {
        freq[card->getCount()]++;
    }

    bool flush = true;
    for (size_t i = 1; i < poker.size(); ++i) {
        if (poker[i]->getSuit() != poker[0]->getSuit()) {
            flush = false;
            break;
        }
    }

    int straightHigh = 0;
    const bool straight = isStraightRanks(poker, straightHigh);

    std::vector<std::pair<int, int>> groups;
    groups.reserve(freq.size());
    for (const auto &[rank, count] : freq) {
        groups.push_back({count, rank});
    }
    std::sort(groups.begin(), groups.end(), [](const auto &lhs, const auto &rhs) {
        if (lhs.first != rhs.first) {
            return lhs.first > rhs.first;
        }
        return lhs.second > rhs.second;
    });

    if (straight && flush) {
        return {straightHigh == 14 ? 0 : 1, {straightHigh}};
    }
    if (groups[0].first == 4) {
        return {2, {groups[0].second, groups[1].second}};
    }
    if (groups[0].first == 3 && groups[1].first == 2) {
        return {3, {groups[0].second, groups[1].second}};
    }
    if (flush) {
        return {4, getSortedRanksDesc(poker)};
    }
    if (straight) {
        return {5, {straightHigh}};
    }
    if (groups[0].first == 3) {
        std::vector<int> tieBreakers = {groups[0].second};
        for (size_t i = 1; i < groups.size(); ++i) {
            tieBreakers.push_back(groups[i].second);
        }
        return {6, tieBreakers};
    }
    if (groups[0].first == 2 && groups[1].first == 2) {
        const int highPair = std::max(groups[0].second, groups[1].second);
        const int lowPair = std::min(groups[0].second, groups[1].second);
        return {7, {highPair, lowPair, groups[2].second}};
    }
    if (groups[0].first == 2) {
        std::vector<int> tieBreakers = {groups[0].second};
        for (size_t i = 1; i < groups.size(); ++i) {
            tieBreakers.push_back(groups[i].second);
        }
        return {8, tieBreakers};
    }
    return {9, getSortedRanksDesc(poker)};
}

int compareHandRanks(const HandRank &lhs, const HandRank &rhs)
{
    if (lhs.type != rhs.type) {
        return lhs.type < rhs.type ? 1 : 2;
    }

    const size_t maxSize = std::max(lhs.tieBreakers.size(), rhs.tieBreakers.size());
    for (size_t i = 0; i < maxSize; ++i) {
        const int left = i < lhs.tieBreakers.size() ? lhs.tieBreakers[i] : 0;
        const int right = i < rhs.tieBreakers.size() ? rhs.tieBreakers[i] : 0;
        if (left != right) {
            return left > right ? 1 : 2;
        }
    }

    return 0;
}

} // namespace

bool cmp(Poker *&a, Poker *&b)
{
    return a->getCount() < b->getCount();
}

bool Game::isFlush(vector<Poker *> &poker)
{
    for (int i = 1; i < poker.size(); i++) {
        if (poker[i]->getSuit() != poker[0]->getSuit()) {
            return false;
        }
    }
    return true;
}

bool Game::isStraight(vector<Poker *> &poker)
{
    int highCard = 0;
    return isStraightRanks(poker, highCard);
}

unordered_map<int, int> Game::getFrequency(vector<Poker *> &poker)
{
    unordered_map<int, int> freq;
    for (auto &i : poker) {
        freq[i->getCount()]++;
    }
    return freq;
}

int Game::getType(vector<Poker *> &Poker)
{
    return evaluateHand(Poker).type;
}

int Game::comparePokers(Player *player1, Player *player2)
{
    qDebug() << player1->getName();
    return compareHands(player1->getChoosePoker(), player2->getChoosePoker());
}

int Game::compareHands(const vector<Poker *> &hand1, const vector<Poker *> &hand2)
{
    return compareHandRanks(evaluateHand(hand1), evaluateHand(hand2));
}

vector<Poker *> Game::getBestHand(const vector<Poker *> &cards)
{
    if (cards.size() <= 5) {
        return cards;
    }

    vector<Poker *> bestHand;
    for (size_t a = 0; a < cards.size() - 4; ++a) {
        for (size_t b = a + 1; b < cards.size() - 3; ++b) {
            for (size_t c = b + 1; c < cards.size() - 2; ++c) {
                for (size_t d = c + 1; d < cards.size() - 1; ++d) {
                    for (size_t e = d + 1; e < cards.size(); ++e) {
                        vector<Poker *> current = {
                            cards[a], cards[b], cards[c], cards[d], cards[e]
                        };
                        if (bestHand.empty() || compareHands(current, bestHand) == 1) {
                            bestHand = current;
                        }
                    }
                }
            }
        }
    }
    return bestHand;
}

int Game::getWiner(vector<Player *> &player)
{
    vector<Player *> wait;
    for (int i = 0; i < player.size(); i++) {
        if (player[i]->getIsAlive()) {
            wait.push_back(player[i]);
        }
    }
    if (wait.empty()) {
        return -1;
    }

    Player *winner = wait[0];
    for (int i = 1; i < wait.size(); i++) {
        if (comparePokers(wait[i], winner) == 1) {
            winner = wait[i];
        }
    }

    for (auto &currentPlayer : player) {
        if (comparePokers(currentPlayer, winner) == 0) {
            currentPlayer->set_iswin(true);
        }
    }
    return 0;
}

void Game::endGame(vector<Player *> &player)
{
    int num = 0;
    for (auto &currentPlayer : player) {
        if (currentPlayer->get_iswin()) {
            num++;
        }
    }
    if (num == 0) {
        return;
    }

    for (auto &win : player) {
        if (win->get_iswin()) {
            win->setMoney(win->getMoney() + (win->allBet / num));
        }
    }
}
