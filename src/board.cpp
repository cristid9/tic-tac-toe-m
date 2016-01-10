#include "board.h"
#include <QDebug>

Board::Board(bool first, int boardSize)
{
    currentTurn     = first;
    isFinished      = false;
    this->boardSize = boardSize;
    emptyTiles      = boardSize * boardSize;
    winner          = Board::DRAW;

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            tiles[i][j] = -1;
        }
    }
}

int Board::getSize()
{
    return boardSize;
}

void Board::setTile(int x, int y, int turn)
{
    tiles[x][y] = turn;
    if (turn == -1)
        emptyTiles++;
    else
        emptyTiles--;
    currentTurn = (turn == Board::O_VAL)
            ? Board::X_VAL : Board::O_VAL;
}

int Board::getTile(int x, int y)
{
    return tiles[x][y];
}

bool Board::getCurrentTurn()
{
    return currentTurn;
}

Board::TileValues Board::getWinner()
{
    return (Board::TileValues)winner;
}

Board::GameWinner Board::checkGameStatus()
{
    // Check each line.
    for (int i = 0; i < boardSize; i++)
    {
        if (tiles[i][0] == Board::EMPTY)
            continue;

        winningPos[0] = make_pair(i, 0);
        int j;
        for (j = 1; j < boardSize; j++)
        {
            winningPos[j] = make_pair(i, j);
            if (tiles[i][j] != tiles[i][0])
            {
                break;
            }

        }

        if (j == boardSize)
        {
            winner = tiles[i][0];
            return (Board::GameWinner)tiles[i][0];
        }
    }

    // Check for each column.
    for (int j = 0; j < boardSize; j++)
    {
        if (tiles[0][j] == Board::EMPTY)
            continue;

        winningPos[0] =  make_pair(0, j);
        int i;
        for (i = 1; i < boardSize; i++)
        {
            winningPos[i] = make_pair(i, j);
            if (tiles[i][j] != tiles[0][j])
            {
                break;
            }
        }

        if (i == boardSize)
        {
            winner = tiles[0][j];
            return (Board::GameWinner)tiles[0][j];
        }
    }

    // Check for the main diagonal.
    if (tiles[0][0] != Board::EMPTY)
    {
        winningPos[0] = make_pair(0, 0);
        int i;
        for (i = 1; i < boardSize; i++)
        {
            winningPos[i] = make_pair(i, i);
            if (tiles[i][i] != tiles[0][0])
            {
                break;
            }
        }

        if (i == boardSize)
        {
            winner = tiles[0][0];
            return (Board::GameWinner)tiles[0][0];
        }
    }

    // Check for the secondary diagonal.
    if (tiles[boardSize - 1][0] != Board::EMPTY)
    {
        winningPos[0] = make_pair(boardSize - 1, 0);
        int i;
        for (i = 1; i < boardSize; i++)
        {
            winningPos[i] = make_pair(boardSize - (i + 1), i);
            if (tiles[boardSize - (i + 1)][i] != tiles[boardSize - 1][0])
            {
                break;
            }
        }

        if (i == boardSize)
        {
            winner = tiles[boardSize - 1][0];
            return (Board::GameWinner)tiles[boardSize - 1][0];
        }
    }

    if (!emptyTiles)
    {
        winner = Board::DRAW;
        return Board::DRAW;
    }

    return Board::RUNNING;
}

