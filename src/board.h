#ifndef BOARD_H
#define BOARD_H

#include <utility>

using std::pair;
using std::make_pair;

class Board
{
private:
    int tiles[4][4];
    int emptyTiles;
    int boardSize;
    int winner;

public:
    enum GameWinner
    {
        X_WIN   = 1,
        O_WIN   = 0,
        DRAW    = -1,
        RUNNING = 2
    };

    enum TileValues
    {
        X_VAL = 1,
        O_VAL = 0,
        EMPTY = -1
    };

    bool isFinished;
    pair<int, int> winningPos[4];
    bool currentTurn;
    bool getCurrentTurn();
    GameWinner checkGameStatus();
    TileValues getWinner();
    int getTile(int row, int column);
    int getSize();
    void setTile(int x, int y, int turn);

    Board(bool first, int boardSize);
};

#endif // BOARD_H
