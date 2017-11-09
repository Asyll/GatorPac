#include "titlescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TitleScreen window;
    window.show();
// no change
    return a.exec();
}
