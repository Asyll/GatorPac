#include "titlescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TitleScreen window;
    window.show();
//change
    return a.exec();
}
