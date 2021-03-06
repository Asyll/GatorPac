#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMovie>
#include "gamescreen.h"


namespace Ui {
class TitleScreen;
}

class TitleScreen : public QWidget
{
    Q_OBJECT
public:
    explicit TitleScreen(QWidget *parent = 0);
    ~TitleScreen();

private:
    Ui::TitleScreen *ui;
    QMediaPlaylist *playlist;
    QMediaPlayer *titleMusic;

    void playBackgroundMusic();

private slots:
    void on_startBtn_clicked();
    void on_howToButton_clicked();
    void on_backButton_clicked();
};

#endif // TITLESCREEN_H


