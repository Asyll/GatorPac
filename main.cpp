#include "titlescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TitleScreen window;
    window.show();
// Bryan's change
    return a.exec();
}
