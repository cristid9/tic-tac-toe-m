#include "gamebot.h"
#include "board.h"
#include <climits>
#include <QDebug>
#include <cstdlib>

GameBot::GameBot(string mode)
{
    this->mode = mode;
}

pair<int, int> GameBot::nextMove(Board *board)
{
    pair<int, int> aux;
    if (mode == "Easy")
    {
         for (int i = 0; i < board->getSize(); i++)
        {
            for (int j = 0; j < board->getSize(); j++)
            {
                if (board->getTile(i, j) == -1)
                {
                    aux = make_pair(i, j);
                    return aux;
                }
            }
        }
    }
    else if (mode == "Medium")
    {
        qDebug() << "medium";
        return hardNextMove(board, Board::O_VAL, 0, 2).move;
    }
    else if (mode == "Hard")
    {
        return hardNextMove(board, Board::O_VAL, 0).move;
    }
    aux = make_pair(0, 0);
    return aux;
}

GameBot::BotMove GameBot::hardNextMove(Board *board,
                                       Board::TileValues turn, int depth,
                                       int depthLimit)
{
    Board::GameWinner rv = board->checkGameStatus();
    if (rv == Board::O_VAL)
    {
        return GameBot::BotMove(10);
    }
    else if (rv == Board::X_VAL)
    {
        return GameBot::BotMove(-10);
    }
    else if (rv == Board::DRAW)
    {
        return GameBot::BotMove(0);
    }

    if (depthLimit != -1 && depth == depthLimit)
    {
        return GameBot::BotMove(0);
    }

    GameBot::BotMove bestMove;

    bestMove.val  = (turn == Board::X_VAL) ? INT_MAX : INT_MIN;
    bestMove.move = make_pair(-1, -1);

    for (int x = 0; x < board->getSize(); x++)
    {
        for (int y = 0; y < board->getSize(); y++)
        {
            if (board->getTile(x, y) != Board::EMPTY)
            {
                continue;
            }
            board->setTile(x, y, turn);

            GameBot::BotMove move;
            move.move = make_pair(x, y);
            Board::TileValues nextTurn = (turn == Board::X_VAL) ?
                Board::O_VAL : Board::X_VAL;
            move.val  = hardNextMove(board, nextTurn, depth + 1, depthLimit).val;

            if (turn == Board::O_VAL)
            {
                if (move.val > bestMove.val)
                {
                    bestMove = move;
                }
            }
            else
            {
                if (move.val < bestMove.val)
                {
                    bestMove = move;
                }
            }

            board->setTile(x, y, Board::EMPTY);
        }
    }

    return bestMove;
}
