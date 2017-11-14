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
    delete playlist;

    this->close();
    game->show();
}

// Play 8 bit crazy train for the title screen
void TitleScreen::playBackgroundMusic()
{
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/Audio/TitleScreenMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}
