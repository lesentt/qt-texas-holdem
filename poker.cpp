#include "poker.h"


Count Poker::getCount()
{
    return count;
}

Suit Poker::getSuit()
{
    return suit;
}

void Poker::setCount(Count c)
{
    count = c;
}

void Poker::setSuit(Suit s)
{
    suit = s;
}

QString Poker::SuitToString()
{
    switch(suit)
    {
    case spade:  return "Spade";
    case heart:  return "Heart";
    case club:   return "Club";
    case diamond:return "Diamond";
    default: return "none";
    }
}

QString Poker::CountToString()
{
    switch(count)
    {
    case two:  return "2";
    case three:  return "3";
    case four:  return "4";
    case five:  return "5";
    case six:  return "6";
    case seven:  return "7";
    case eight: return "8";
    case nine:  return "9";
    case ten: return"10";
    case j:return"J";
    case q:return"Q";
    case k:return"K";
    case a:return"A";
    default:return "none";
    }
}






