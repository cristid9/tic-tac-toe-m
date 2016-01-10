#include "gamewizard.h"
#include "gamewindow.h"
#include "ui_gamewizard.h"
#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>

GameWizard::GameWizard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWizard)
{
    ui->setupUi(this);
    gameMode = "computer";
    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(validate()));
    connect(ui->radioButton_4, SIGNAL(clicked(bool)),
            this, SLOT(enableSinglePlayer()));
    connect(ui->radioButton_5, SIGNAL(clicked(bool)),
            this, SLOT(enableMultiPlayer()));
}

void GameWizard::validate()
{
    errorDialog = new QMessageBox();

    bool difficultyLevel = false;
    QString diffciulty  = "";
    if (ui->radioButton->isChecked())
    {
        difficultyLevel = true;
        diffciulty      = ui->radioButton->text();
    }

    if (ui->radioButton_2->isChecked())
    {
        difficultyLevel = true;
        diffciulty      = ui->radioButton_2->text();
    }

    if (ui->radioButton_3->isChecked())
    {
        difficultyLevel = true;
        diffciulty      = ui->radioButton_3->text();
    }

    if (!difficultyLevel && ui->radioButton_4->isChecked())
    {
        errorDialog->setText("You haven't chose the difficulty level!");
        errorDialog->open();
        return;
    }

    QString opponentName = "computer";
    QLayout *row1 = ui->verticalLayout->itemAt(0)->layout();
    QString name = ((QLineEdit*)(row1->itemAt(1)->widget()))->text();

    if (name == "")
    {
        errorDialog->setText("You haven't filled the name");
        errorDialog->open();
        return;
    }

    if (gameMode == "human")
    {
        QLayout *row2 = ui->verticalLayout->itemAt(1)->layout();
        opponentName = ((QLineEdit*)(row2->itemAt(1)->widget()))->text();

        if (opponentName == "")
        {
            errorDialog->setText("You haven't filled the name for the second player");
            errorDialog->open();
            return;
        }

        enableSinglePlayer();
        ui->radioButton_4->setChecked(true);
    }

    gameW = new GameWindow(this);
    gameW->setData(name, opponentName,
                   diffciulty, 3);
    gameW->show();

    this->hide();
}

void GameWizard::enableMultiPlayer()
{
    if (gameMode == "computer")
    {
        qDebug() << "bag pl";
        gameMode = "human";
        player2   = new QHBoxLayout();
        QLabel *player2Label   = new QLabel("Nume 2 (0)");
        QLineEdit *player2Name = new QLineEdit();

        player2->addWidget(player2Label);
        player2->addWidget(player2Name);
        ui->verticalLayout->addLayout(player2);
        ui->groupBox->hide();
    }
}

void GameWizard::enableSinglePlayer()
{
    if (gameMode == "human")
    {
        gameMode = "computer";
        ui->verticalLayout->removeItem(player2);
        delete player2->takeAt(0)->widget();
        delete player2->takeAt(0)->widget();
        delete player2;
        ui->groupBox->show();
    }
}

GameWizard::~GameWizard()
{
    delete ui;
}
