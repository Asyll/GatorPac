#include "titlescreen.h"
#include <QApplication>

//main method for game
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TitleScreen window;
    window.show();

    return a.exec();
}
