#ifndef GAMEBOT_H
#define GAMEBOT_H

#include <string>
#include <utility>
#include "board.h"

using namespace std;



class GameBot
{
private:
    struct BotMove
    {
        BotMove() {}
        BotMove(int v) : val(v) {}

        int val;
        pair<int, int> move;
    };

    GameBot::BotMove GameBot::hardNextMove(Board *board,
                                           Board::TileValues turn, int depth,
                                           int depthLimit = -1);
public:
    string mode;
    GameBot(string mode);
    pair<int, int> nextMove(Board *board);
};

#endif // GAMEBOT_H
