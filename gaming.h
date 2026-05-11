#ifndef GAMING_H
#define GAMING_H
#include "banker.h"
#include "deck.h"
#include "game.h"
#include "player.h"
#include "QDebug"
#include "QMessageBox"
#include "QStandardItem"
#include "QString"
#include "QTimer"
#include <QListView>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>

namespace Ui {
class Gaming;
}

class Gaming : public QMainWindow
{
    Q_OBJECT
public:
    explicit Gaming(QWidget *parent = nullptr);
    vector<Player *> gamers;
    Banker *banker;
    Deck *deck;
    Game game;
    QListView *listView;
    QTimer *refresh;
    ~Gaming();
    void AIchoose();
    void hidepoker();
    void hideaction();
    void showaction();
    void nextstate();
    void SetButton_enable(int x);

signals:
    void finishfirstadd();
    void finishfirstdeal();
    void finishaction();
    void deal_public_first();
    void deal_public_second();
    void deal_public_third();
    void startchoose();
    void finishChoose();
    void sure();
    void again();
    void getwinner();
    void end();

private slots:
    void dealpoker_public();
    void on_input_returnPressed();
    void dealpoker_gamers();
    void playeraction();
    void on_bet_clicked();
    void on_follow_clicked();
    void on_raise_clicked();
    void on_check_clicked();
    void on_fold_clicked();
    void updateNews();
    void mychoose();
    void hideChoose();
    void showChoose();
    void Sure();
    void on_public1_clicked();
    void on_public2_clicked();
    void on_public3_clicked();
    void on_public4_clicked();
    void on_public5_clicked();
    void on_my_poker1_clicked();
    void on_my_poker2_clicked();
    void WINER();
    void endgame();
    void on_again_clicked();
    void on_exit_clicked();

private:
    Ui::Gaming *ui;
    bool trySelectCard(Poker *card, QPushButton *button);
};

#endif // GAMING_H
