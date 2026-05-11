#include "gaming.h"
#include "ui_gaming.h"
#include <algorithm>

int cs = 0;
int is_ai_action;
QIcon ap1;
QIcon ap2;
QIcon mp1;
QIcon mp2;
QIcon pu1;
QIcon pu2;
QIcon pu3;
QIcon pu4;
QIcon pu5;

Gaming::~Gaming()
{
    Player::allBet = 0;
    delete ui;
    delete banker;
    delete deck;
    delete refresh;
    delete gamers[0];
    delete gamers[1];
}

void Gaming::AIchoose()
{
    vector<Poker *> allCards = banker->getTablePoker();
    for (int i = 0; i < 2; ++i) {
        allCards.push_back(banker->getPlayers()[1]->getHandPoker()[i]);
    }
    banker->getPlayers()[1]->getChoosePoker() = game.getBestHand(allCards);
}

Gaming::Gaming(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gaming)
{
    setWindowIcon(QIcon(":/resource/start.png"));
    refresh = new QTimer(this);
    refresh->start(100);
    gamers.push_back(new Player(1, "player", 0, 10000));
    gamers.push_back(new Player(2, "AI", 1, 10000));
    deck = new Deck;
    banker = new Banker(*deck, gamers, this);
    banker->shullefDeck();
    ui->setupUi(this);
    ui->again->hide();
    ui->exit->hide();
    ui->end->hide();
    hidepoker();
    hideChoose();
    hideaction();
    SetButton_enable(0);
    ui->message->setText("请输入初始下注");
    ui->message->setStyleSheet("#message{color:blue;font-size:16px;font-weight: bold;}");
    connect(refresh, SIGNAL(timeout()), this, SLOT(updateNews()));
    connect(this, SIGNAL(finishfirstadd()), this, SLOT(dealpoker_gamers()));
    connect(this, SIGNAL(finishfirstdeal()), this, SLOT(playeraction()));
    connect(this, SIGNAL(finishaction()), this, SLOT(dealpoker_public()));
    connect(this, SIGNAL(deal_public_first()), this, SLOT(playeraction()));
    connect(this, SIGNAL(deal_public_second()), this, SLOT(playeraction()));
    connect(this, SIGNAL(deal_public_third()), this, SLOT(playeraction()));
    connect(this, SIGNAL(startchoose()), this, SLOT(mychoose()));
    connect(this, SIGNAL(finishChoose()), this, SLOT(Sure()));
    connect(this, SIGNAL(sure()), this, SLOT(showChoose()));
    connect(this, SIGNAL(again()), this, SLOT(mychoose()));
    connect(this, SIGNAL(getwinner()), this, SLOT(WINER()));
    connect(this, SIGNAL(end()), this, SLOT(endgame()));
}

void Gaming::updateNews()
{
    listView = findChild<QListView *>("listView");
    if (listView) {
        listView->setStyleSheet("QListView { background-color: rgba(34, 177, 76, 50); }");
        QStandardItemModel *model = new QStandardItemModel(this);
        QStandardItem *item1 = new QStandardItem(QString("当前阶段：%1").arg(banker->getCurrentstate()));
        QStandardItem *item2 = new QStandardItem(QString("剩余筹码：%1").arg(gamers[0]->getMoney()));
        QStandardItem *item3 = new QStandardItem(QString("本局下注：%1").arg(gamers[0]->gettotalBet()));
        QStandardItem *item4 = new QStandardItem(QString("底池大小：%1").arg(gamers[0]->allBet));
        model->appendRow(item1);
        model->appendRow(item2);
        model->appendRow(item3);
        model->appendRow(item4);
        listView->setModel(model);
        QFont font("Arial", 10);
        font.setBold(1);
        listView->setFont(font);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void Gaming::mychoose()
{
    ui->history->appendPlainText("请选择 5 张牌");
    cs = 0;
    banker->getPlayers()[0]->getChoosePoker().clear();
    banker->getPlayers()[1]->getChoosePoker().clear();
    AIchoose();
    SetButton_enable(1);
    ui->ai_poker1->setEnabled(0);
    ui->ai_poker2->setEnabled(0);
}

void Gaming::hideChoose()
{
    ui->ai_choose1->hide();
    ui->ai_choose2->hide();
    ui->ai_choose3->hide();
    ui->ai_choose4->hide();
    ui->ai_choose5->hide();
    ui->ai_label->hide();
    ui->my_label->hide();
}

void Gaming::showChoose()
{
    ui->ai_choose1->setIcon(gamers[1]->getChoosePoker()[0]->pix);
    ui->ai_choose2->setIcon(gamers[1]->getChoosePoker()[1]->pix);
    ui->ai_choose3->setIcon(gamers[1]->getChoosePoker()[2]->pix);
    ui->ai_choose4->setIcon(gamers[1]->getChoosePoker()[3]->pix);
    ui->ai_choose5->setIcon(gamers[1]->getChoosePoker()[4]->pix);
    ui->public1->setIcon(banker->getPlayers()[0]->getChoosePoker()[0]->pix);
    ui->public2->setIcon(banker->getPlayers()[0]->getChoosePoker()[1]->pix);
    ui->public3->setIcon(banker->getPlayers()[0]->getChoosePoker()[2]->pix);
    ui->public4->setIcon(banker->getPlayers()[0]->getChoosePoker()[3]->pix);
    ui->public5->setIcon(banker->getPlayers()[0]->getChoosePoker()[4]->pix);
    ui->my_poker1->hide();
    ui->my_poker2->hide();
    ui->ai_poker1->hide();
    ui->ai_poker2->hide();
    ui->ai_choose1->show();
    ui->ai_choose2->show();
    ui->ai_choose3->show();
    ui->ai_choose4->show();
    ui->ai_choose5->show();
    ui->ai_label->show();
    ui->my_label->show();
    emit getwinner();
}

void Gaming::Sure()
{
    QMessageBox::information(this, "确认", "确认选择这五张牌吗？");
    int reply = QMessageBox::question(this, "确认", "请再次确认",
                                      QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit sure();
    }
    if (reply == QMessageBox::No) {
        emit again();
    }
}

void Gaming::hidepoker()
{
    ui->ai_poker1->hide();
    ui->ai_poker2->hide();
    ui->my_poker1->hide();
    ui->my_poker2->hide();
    ui->public1->hide();
    ui->public2->hide();
    ui->public3->hide();
    ui->public4->hide();
    ui->public5->hide();
}

void Gaming::hideaction()
{
    ui->allin->hide();
    ui->bet->hide();
    ui->check->hide();
    ui->fold->hide();
    ui->follow->hide();
    ui->raise->hide();
}

void Gaming::showaction()
{
    ui->bet->show();
    ui->check->show();
    ui->fold->show();
    ui->follow->show();
    ui->raise->show();
}

void Gaming::nextstate()
{
    banker->getCurrentstate()++;
    Player::currentMaxBet = 0;
    for (auto *gamer : gamers) {
        gamer->getCurrentBet() = 0;
    }
    is_ai_action = 0;
}

void Gaming::SetButton_enable(int x)
{
    ui->ai_poker1->setEnabled(x);
    ui->ai_poker2->setEnabled(x);
    ui->my_poker1->setEnabled(x);
    ui->my_poker2->setEnabled(x);
    ui->public1->setEnabled(x);
    ui->public2->setEnabled(x);
    ui->public3->setEnabled(x);
    ui->public4->setEnabled(x);
    ui->public5->setEnabled(x);
}

bool Gaming::trySelectCard(Poker *card, QPushButton *button)
{
    auto &chosen = banker->getPlayers()[0]->getChoosePoker();
    if (std::find(chosen.begin(), chosen.end(), card) != chosen.end()) {
        ui->history->appendPlainText("这张牌已经选过了");
        return false;
    }

    chosen.push_back(card);
    button->setEnabled(false);
    cs++;
    ui->history->appendPlainText("已选择一张牌");
    if (cs == 5) {
        emit finishChoose();
    }
    return true;
}

void Gaming::dealpoker_public()
{
    ui->input->hide();
    ui->message->hide();
    nextstate();
    banker->DealPokertoTable();
    qDebug() << "发放公共牌";
    int n = banker->getCurrentstate();
    if (n == 2) {
        pu1.addPixmap(banker->getTablePoker()[0]->pix, QIcon::Disabled);
        pu2.addPixmap(banker->getTablePoker()[1]->pix, QIcon::Disabled);
        pu3.addPixmap(banker->getTablePoker()[2]->pix, QIcon::Disabled);
        ui->history->appendPlainText("翻牌圈：已发出 3 张公共牌");
        ui->public1->setIcon(pu1);
        ui->public2->setIcon(pu2);
        ui->public3->setIcon(pu3);
        ui->public1->show();
        ui->public2->show();
        ui->public3->show();
        emit deal_public_first();
    }
    if (n == 3) {
        pu4.addPixmap(banker->getTablePoker()[3]->pix, QIcon::Disabled);
        ui->history->appendPlainText("转牌圈：已发出第 4 张公共牌");
        ui->public4->setIcon(pu4);
        ui->public4->show();
        emit deal_public_second();
    }
    if (n == 4) {
        pu5.addPixmap(banker->getTablePoker()[4]->pix, QIcon::Disabled);
        ui->history->appendPlainText("河牌圈：已发出第 5 张公共牌");
        ui->public5->setIcon(pu5);
        ui->public5->show();
        emit deal_public_third();
    }
    if (n == 5) {
        ui->history->appendPlainText("请从 7 张牌中选择最好的 5 张");
        hideaction();
        emit startchoose();
    }
}

void Gaming::on_input_returnPressed()
{
    if (banker->getCurrentstate() == 0) {
        banker->getPlayers()[0]->getMoney() -= ui->input->text().toInt();
        banker->getPlayers()[1]->getMoney() -= 2 * ui->input->text().toInt();
        banker->getPlayers()[0]->allBet += 3 * ui->input->text().toInt();
        ui->input->hide();
        ui->message->hide();
        updateNews();
        ui->history->appendPlainText("玩家下注 " + QString::number(ui->input->text().toInt()));
        ui->history->appendPlainText("电脑下注 " + QString::number(2 * ui->input->text().toInt()));
        ui->input->clear();
        emit finishfirstadd();
    }
}

void Gaming::dealpoker_gamers()
{
    nextstate();
    banker->DealPokertoPlayers();
    mp1.addPixmap(banker->getPlayers()[0]->getHandPoker()[0]->pix, QIcon::Disabled);
    mp2.addPixmap(banker->getPlayers()[0]->getHandPoker()[1]->pix, QIcon::Disabled);
    ap1.addPixmap(QPixmap(":/resource/Background.png"), QIcon::Disabled);
    ap2.addPixmap(QPixmap(":/resource/Background.png"), QIcon::Disabled);
    ui->my_poker1->setIcon(mp1);
    ui->my_poker2->setIcon(mp2);
    ui->ai_poker1->setIcon(ap1);
    ui->ai_poker2->setIcon(ap2);
    ui->my_poker1->show();
    ui->my_poker2->show();
    ui->ai_poker1->show();
    ui->ai_poker2->show();
    ui->history->appendPlainText("已向双方发出 2 张手牌");
    emit finishfirstdeal();
}

void Gaming::playeraction()
{
    showaction();
}

void Gaming::on_bet_clicked()
{
    ui->input->show();
    int value = ui->input->text().toInt();
    if (value == 0)
        return;
    int ok = 0;
    int res = 0;
    res = banker->getPlayers()[0]->bet(value);
    if (res == 0) {
        ui->history->appendPlainText("玩家下注 " + QString::number(value));
        ui->history->appendPlainText("电脑跟注 " + QString::number(value));
        ok = 1;
        banker->getPlayers()[1]->call();
    }
    if (res == -1) {
        ui->history->appendPlainText("筹码不足");
        playeraction();
    }
    if (res == -2) {
        ui->history->appendPlainText("当前不能下注");
        playeraction();
    }
    if (ok)
        emit finishaction();

    ui->input->clear();
}

void Gaming::on_follow_clicked()
{
    int value = ((banker->getPlayers()[1]->getMoney()) / 4);
    int res = 0;
    int ok = 0;
    res = banker->getPlayers()[0]->call();
    if (res == 0) {
        ui->history->appendPlainText("玩家跟注 " + QString::number(value));
        ok = 1;
    }
    if (res == -1) {
        ui->history->appendPlainText("当前没有可跟注的下注");
        playeraction();
    }
    if (res == -2) {
        ui->history->appendPlainText("筹码不足，无法跟注");
        playeraction();
    }
    if (ok)
        emit finishaction();
    ui->input->clear();
}

void Gaming::on_raise_clicked()
{
    int value = ui->input->text().toInt();
    ui->input->show();
    if (value == 0)
        return;
    int res = 0;
    int ok = 0;
    res = banker->getPlayers()[0]->raise(value);
    if (res == 0) {
        ui->history->appendPlainText("玩家加注 " + QString::number(value));
        if (!is_ai_action) {
            ui->history->appendPlainText("电脑跟注 " + QString::number(value));
            banker->getPlayers()[1]->call();
        }
        ok = 1;
    }
    if (res == -1) {
        ui->history->appendPlainText("加注不合法或筹码不足");
        playeraction();
    }
    if (ok)
        emit finishaction();
    ui->input->clear();
}

void Gaming::on_check_clicked()
{
    ui->input->show();
    int res = 0;
    int value = ((banker->getPlayers()[1]->getMoney()) / 5);
    res = banker->getPlayers()[0]->check();
    if (res == 0) {
        ui->history->appendPlainText("玩家过牌");
        ui->history->appendPlainText("电脑下注 " + QString::number(value));
        banker->getPlayers()[1]->bet(value);
        is_ai_action = 1;
        playeraction();
    }
    if (res == -1) {
        ui->history->appendPlainText("当前不能过牌");
        playeraction();
    }
    ui->input->clear();
}

void Gaming::on_fold_clicked()
{
    emit end();
    ui->history->appendPlainText("玩家弃牌，对手获胜，赢得 " + QString::number(banker->getPlayers()[0]->allBet));
    gamers[1]->getMoney() += banker->getPlayers()[0]->allBet;
}

void Gaming::on_public1_clicked()
{
    if (cs < 5) {
        trySelectCard(banker->getTablePoker()[0], ui->public1);
    }
}

void Gaming::on_public2_clicked()
{
    if (cs < 5) {
        trySelectCard(banker->getTablePoker()[1], ui->public2);
    }
}

void Gaming::on_public3_clicked()
{
    if (cs < 5) {
        trySelectCard(banker->getTablePoker()[2], ui->public3);
    }
}

void Gaming::on_public4_clicked()
{
    if (cs < 5) {
        trySelectCard(banker->getTablePoker()[3], ui->public4);
    }
}

void Gaming::on_public5_clicked()
{
    if (cs < 5) {
        trySelectCard(banker->getTablePoker()[4], ui->public5);
    }
}

void Gaming::on_my_poker1_clicked()
{
    if (cs < 5) {
        trySelectCard(banker->getPlayers()[0]->getHandPoker()[0], ui->my_poker1);
    }
}

void Gaming::on_my_poker2_clicked()
{
    if (cs < 5) {
        trySelectCard(banker->getPlayers()[0]->getHandPoker()[1], ui->my_poker2);
    }
}

void Gaming::WINER()
{
    game.getWiner(banker->getPlayers());
    game.endGame(banker->getPlayers());
    if (banker->getPlayers()[0]->get_iswin()) {
        if (!banker->getPlayers()[1]->get_iswin()) {
            ui->history->appendPlainText("玩家获胜，赢得 " + QString::number(banker->getPlayers()[0]->allBet));
        } else {
            ui->history->appendPlainText("平局，玩家获得 " + QString::number(banker->getPlayers()[0]->allBet / 2));
        }
    } else {
        ui->history->appendPlainText("玩家落败，输掉 " + QString::number(banker->getPlayers()[0]->allBet));
    }
    emit end();
}

void Gaming::endgame()
{
    ui->end->show();
    ui->again->show();
    ui->exit->show();
}

void Gaming::on_again_clicked()
{
    Gaming *s = new Gaming;
    s->show();
    close();
    deleteLater();
}

void Gaming::on_exit_clicked()
{
    close();
    deleteLater();
}
