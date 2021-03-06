                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         #include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QSize>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this,
            SLOT(newGame()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this,
            SLOT(showMainMenu()));

    this->parent = parent;
}

void GameWindow::setData(QString name, QString opponent,
             QString mode, int gridSize)
{
    this->name     = name;
    this->mode     = mode;
    this->opponent = opponent;
    this->gridSize = gridSize;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            QPushButton *button = new QPushButton();
            button->setMinimumWidth(60);
            button->setMinimumHeight(60);
            button->setText(" ");
            buttons.append(button);

            connect(button, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
            ui->gridLayout->addWidget(button, i, j);
            button->show();
        }
    }

    bot   = new GameBot(mode.toStdString());
    board = new Board(1, gridSize);

    ui->label->setText(name);
    ui->label_2->setText(opponent);
    ui->label_3->setText(QString("0"));
    ui->label_4->setText(QString("0"));
}

int GameWindow::getPos(int row, int column)
{
    return row * gridSize + column;
}

void GameWindow::clickHandler()
{
    // refactor this shit!
    if (board->checkGameStatus() != Board::RUNNING)
        return;

    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());

    int indexOfButton = ui->gridLayout->indexOf(buttonWidget);
    int buttonRow, buttonColumn, buttonRowSpan, buttonColumnSpan;

    ui->gridLayout->getItemPosition(indexOfButton, &buttonRow, &buttonColumn,
                                    &buttonRowSpan, &buttonColumnSpan);

    int pos = getPos(buttonRow, buttonColumn);
    if (buttons[pos]->text() == " ")
    {
        bool turn = board->getCurrentTurn();
        char buttonText = (turn == Board::X_VAL) ? 'x' : '0';

        buttons[pos]->setText(QString(buttonText));

        // there should be the check of the mode
        board->setTile(buttonRow, buttonColumn, turn);


        if (board->checkGameStatus() != Board::RUNNING
                && board->getWinner() != Board::DRAW)
        {
            markWinner();
            scoreManager.incrementScore(board->getWinner());
            updateScore(board->getWinner(),
                        scoreManager.getScore(board->getWinner()));
            return;
        }
        else if (board->checkGameStatus() != Board::RUNNING
                 && board->getWinner() == Board::DRAW)
        {

            markDraw();
            return;
        }

        // Another way to exploit the app, the zero sholdn't have
        // the name computer
        if (opponent == "computer")
        {
            pair<int, int> move = bot->nextMove(board);

            turn  = board->getCurrentTurn();
            buttonText = (turn == Board::X_VAL) ? 'x' : '0';

            pos   = getPos(move.first, move.second);
            buttons[pos]->setText(QString(buttonText));
            board->setTile(move.first , move.second, turn);
        }
    }

    // check for the winner here
     if (board->checkGameStatus() != Board::RUNNING
             && board->getWinner() != Board::DRAW)
     {
         scoreManager.incrementScore(board->getWinner());
         updateScore(board->getWinner(),
                     scoreManager.getScore(board->getWinner()));
         markWinner();
     }
     else if (board->checkGameStatus() != Board::RUNNING
              && board->getWinner() == Board::DRAW)
     {
         markDraw();
     }
}

void GameWindow::markWinner()
{
    for (int i = 0; i < board->getSize(); i++)
    {
        int x         = board->winningPos[i].first;
        int y         = board->winningPos[i].second;
        QString color = (board->getWinner() == Board::X_VAL) ? "green" : "red";

        buttons[getPos(x, y)]->setStyleSheet("background-color: " + color);
    }
}

void GameWindow::markDraw()
{
    for (int i = 0; i < board->getSize() * board->getSize(); i++)
    {
        buttons[i]->setStyleSheet("background-color: yellow");
    }
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::newGame()
{
    int boardSize = board->getSize();
    for (int i = 0; i < boardSize * boardSize; i++)
    {
        buttons[i]->setText(" ");
        buttons[i]->setStyleSheet("background-color: none");
    }

    delete board;

    board = new Board(true, boardSize);
}

void GameWindow::updateScore(Board::TileValues player, int newScore)
{
    char score[9];
    itoa(newScore, score, 10);
    if (player == Board::X_VAL)
    {
        ui->label_3->setText(QString(score));
    }
    else
    {
        ui->label_4->setText(QString(score));
    }
}

void GameWindow::showMainMenu()
{
    parent->show();
//    ~GameWindow();
    this->hide();
}

int GameWindow::Score::getScore(Board::TileValues player )
{
    if (player == Board::X_VAL)
        return x;
    return o;
}

void GameWindow::Score::incrementScore(Board::TileValues player)
{
    if (player == Board::X_VAL)
        x++;
    else
        o++;
}
