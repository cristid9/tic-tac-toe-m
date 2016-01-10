#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include "board.h"
#include "gamebot.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    QString name;
    QString opponent;
    QString mode;
    int gridSize;
    QList<QPushButton*> buttons;
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void setData(QString name, QString opponent,
                 QString mode, int gridSize);
private:
    struct Score
    {
        Score() : x(0), o(0) {}
        int getScore(Board::TileValues player);
        void incrementScore(Board::TileValues player);

        int x;
        int o;
    };

    Ui::GameWindow *ui;
    Board  *board;
    GameBot *bot;
    Score scoreManager;
    QWidget *parent;
    int getPos(int row, int column);
    void markWinner();
    void markDraw();
    void updateScore(Board::TileValues player, int newScore);

private slots:
    void clickHandler();
    void newGame();
    void showMainMenu();
};

#endif // GAMEWINDOW_H
