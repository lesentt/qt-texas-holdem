#include "startgame.h"
#include "ui_startgame.h"
#include "QWidget"
#include"gaming.h"


StartGame::StartGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartGame)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resource/start.png"));
}

StartGame::~StartGame()
{
    delete ui;
}


void StartGame::on_start_clicked()
{ Gaming* s=new Gaming;
    s->show();
    this->close();
}


void StartGame::on_exit_clicked()
{

    this->close();
}

