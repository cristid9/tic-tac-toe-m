#ifndef GAMEWIZARD_H
#define GAMEWIZARD_H

#include <QWidget>
#include <QMessageBox>
#include <QHBoxLayout>
#include "gamewindow.h"

namespace Ui {
class GameWizard;
}

class GameWizard : public QWidget
{
    Q_OBJECT

public:
    explicit GameWizard(QWidget *parent = 0);
    ~GameWizard();

private:
    Ui::GameWizard *ui;
    GameWindow *gameW;
    QString gameMode;
    QMessageBox *errorDialog;
    QHBoxLayout *player2;

private slots:
    void validate();
//    void unhide();
    void enableSinglePlayer();
    void enableMultiPlayer();

};

#endif // GAMEWIZARD_H
