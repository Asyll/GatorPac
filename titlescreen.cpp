#include "titlescreen.h"
#include "gamescreen.h"
#include "ui_titlescreen.h"
#include <QMediaPlayer>

TitleScreen::TitleScreen(QWidget *parent) : QWidget(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);

    QLabel *logo = ui->logo;
    logo->setPixmap(QPixmap(":/Images/gatorlogo.png"));
    logo->setScaledContents( true );

    playBackgroundMusic();

}

TitleScreen::~TitleScreen()
{
    delete ui;
}

void TitleScreen::on_startBtn_clicked()
{
    GameScreen *game = new GameScreen();
    introMusic->stop();

    this->close();
    game->show();
}

// Play 8 bit crazy train for the title screen
void TitleScreen::playBackgroundMusic()
{
    introMusic->setMedia(QUrl("qrc:/Audio/TitleScreenMusic.mp3"));
    if (introMusic->state() == QMediaPlayer::PlayingState) {
        introMusic->setPosition(0);
    }
    else if (introMusic->state() == QMediaPlayer::StoppedState) {
        introMusic->play();
    }
}
