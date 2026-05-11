#ifndef STARTGAME_H
#define STARTGAME_H
#include"gaming.h"
#include <QMainWindow>

namespace Ui {
class StartGame;
}

class StartGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartGame(QWidget *parent = nullptr);
    ~StartGame();


private slots:
    void on_start_clicked();
    void on_exit_clicked();

private:
    Ui::StartGame *ui;
};

#endif // STARTGAME_H
