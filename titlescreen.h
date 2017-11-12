#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QWidget>
#include <QMediaPlayer>

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

    QMediaPlayer * introMusic = new QMediaPlayer();
    void playBackgroundMusic();
};

#endif // TITLESCREEN_H
