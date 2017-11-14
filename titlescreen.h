#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class TitleScreen;
}

class TitleScreen : public QWidget
{
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = 0);
    ~TitleScreen();

private slots:
    void on_startBtn_clicked();

private:
    Ui::TitleScreen *ui;

    QMediaPlaylist * playlist = new QMediaPlaylist();
    void playBackgroundMusic();
};

#endif // TITLESCREEN_H
