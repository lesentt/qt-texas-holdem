#include "player.h"
#include "poker.h"
#include <iostream>

int Player::currentMaxBet = 0;
int Player::allBet = 0;

void Player::Action()
{
    std::cout << "请选择操作：1.下注 2.跟注 3.加注 4.过牌 5.全下 6.弃牌" << std::endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1: {
        int num;
        cin >> num;
        if (bet(num) == -1)
            Action();
        break;
    }
    case 2: {
        if (call() == -1)
            Action();
        break;
    }
    case 3: {
        int num;
        cout << "请输入加注金额：" << std::endl;
        cin >> num;
        if (raise(num) == -1)
            Action();
        break;
    }
    case 4: {
        if (check() == -1)
            Action();
        break;
    }
    case 5: {
        if (allIn() == -1)
            Action();
        break;
    }
    case 6: {
        if (fold() == -1)
            Action();
        break;
    }
    default: {
        std::cout << "操作无效" << std::endl;
        Action();
    }
    }
}

void Player::ShowchoosePoker()
{
}

int Player::setMoney(int x)
{
    return money = x;
}

bool &Player::get_iswin()
{
    return isWin;
}

bool Player::set_iswin(bool x)
{
    return isWin = x;
}

int &Player::getMoney()
{
    return money;
}

vector<Poker *> &Player::getHandPoker()
{
    return handPoker;
}

vector<Poker *> &Player::getChoosePoker()
{
    return choosePoker;
}

int &Player::getid()
{
    return id;
}

bool &Player::getIsAllIn()
{
    return isAllIn;
}

string Player::getName()
{
    return name;
}

bool &Player::getIsAlive()
{
    return isAlive;
}

bool &Player::getisAI()
{
    return isAI;
}

int &Player::getCurrentBet()
{
    return this->currentBet;
}

int &Player::gettotalBet()
{
    return this->totalBet;
}

void Player::set_isAlive(bool x)
{
    isAlive = x;
}

int Player::call()
{
    if (!isAllIn) {
        const int diff = currentMaxBet - currentBet;
        if (diff > 0 && diff <= money) {
            currentBet += diff;
            money -= diff;
            totalBet += diff;
            allBet += diff;
            if (isAI)
                cout << "电脑跟注" << endl;
            return 0;
        } else if (diff <= 0) {
            std::cout << "当前没有可跟注的下注" << std::endl;
            return -1;
        } else {
            std::cout << "筹码不足，无法跟注" << std::endl;
            return -2;
        }
    } else {
        std::cout << "已经全下" << std::endl;
        return -3;
    }
}

int Player::raise(int amount)
{
    if (!isAllIn) {
        const int targetBet = currentMaxBet + amount;
        const int diff = targetBet - currentBet;
        if (amount > 0 && diff <= money) {
            currentMaxBet = targetBet;
            currentBet += diff;
            money -= diff;
            totalBet += diff;
            allBet += diff;
            if (isAI)
                cout << "电脑加注 " << amount << endl;
            return 0;
        } else {
            std::cout << "加注不合法或筹码不足" << std::endl;
            return -1;
        }
    } else {
        std::cout << "已经全下" << std::endl;
        return -2;
    }
}

int Player::check()
{
    if ((currentMaxBet == 0) || (isAllIn == true)) {
        if (isAI)
            cout << "电脑过牌" << endl;
        return 0;
    } else {
        std::cout << "当前不能过牌" << std::endl;
        return -1;
    }
}

int Player::allIn()
{
    if (!isAllIn) {
        if (money <= 0) {
            std::cout << "筹码不足" << std::endl;
            return -1;
        }
        isAllIn = true;
        if (currentBet + money > currentMaxBet) {
            currentMaxBet = currentBet + money;
        }
        currentBet += money;
        allBet += money;
        totalBet += money;
        money = 0;
        if (isAI)
            cout << "电脑全下" << endl;
        return 0;
    } else {
        std::cout << "已经全下" << std::endl;
        return -1;
    }
}

int Player::bet(int amount)
{
    if (!isAllIn) {
        if (amount > money) {
            std::cout << "筹码不足" << std::endl;
            return -1;
        }
        if (currentMaxBet == 0) {
            currentMaxBet = amount;
            currentBet += amount;
            totalBet += amount;
            money -= amount;
            allBet += amount;
            if (isAI)
                cout << "电脑下注 " << amount << endl;
            return 0;
        } else {
            std::cout << "当前不能下注" << std::endl;
            return -2;
        }
    } else {
        std::cout << "已经全下" << std::endl;
        return -3;
    }
}

int Player::fold()
{
    if (!isAllIn) {
        set_isAlive(false);
        currentBet = 0;
        totalBet = 0;
        if (isAI)
            cout << "电脑弃牌" << endl;
        return 0;
    } else {
        std::cout << "已经全下" << std::endl;
        return -1;
    }
}
