#include "titlescreen.h"
#include <QApplication>

/*   ________    ________________________ __________        __________  _____  _________
 *  /  _____/   /  _  \__    ___/\_____  \\______   \       \______   \/  _  \ \_   ___ \
 * /   \  ___  /  /_\  \|    |    /   _   \|       _/        |     ___/  /_\  \/    \  \/
 * \    \_\  \/    |    \    |   /   /_\   \    |   \        |    |  /    |    \     \____
 *  \______  /\____|__  /____|   \_______  /____|_  /        |____|  \____|__  /\______  /
 *         \/         \/                 \/       \/                         \/        \/
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TitleScreen window;
    window.show();

    return a.exec();
}
