#include "titlescreen.h"
#include "gamescreen.h"
#include "ui_titlescreen.h"
#include <QMediaPlayer>
#include <Qmovie>

//sets up the title screen for the game

TitleScreen::TitleScreen(QWidget *parent) : QWidget(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);

    //displays the animation for the gatorpac title screen
    //QMovie *animation = new QMovie(":/Images/AnimatedTitle.gif");
    QLabel *logo = ui->logo;
    //logo->setMovie(animation);
    ui->logo->setPixmap(QPixmap(":/Images/gatorlogo.png"));
    ui->logo->setScaledContents( true );
    //animation->start();

    playBackgroundMusic();

}

//?
TitleScreen::~TitleScreen()
{
    delete ui;
}

//implements the start button
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
