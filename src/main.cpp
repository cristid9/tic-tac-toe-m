#include "mainwindow.h"
#include "gamewizard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWizard wizard;
    wizard.show();

    return a.exec();
}
