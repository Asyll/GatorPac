#include "titlescreen.h"
#include "ui_titlescreen.h"


TitleScreen::TitleScreen(QWidget *parent) : QWidget(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);

    ui->logo->setPixmap(QPixmap(":/Images/gatorlogo.png"));
    ui->logo->setScaledContents( true );

    playBackgroundMusic();
}

TitleScreen::~TitleScreen()
{
    delete ui;
    delete playlist;
    delete titleMusic;
}

// Starts the game
void TitleScreen::on_startBtn_clicked()
{
    GameScreen *game = new GameScreen();
    titleMusic->stop();

    this->close();
    game->show();
}

void TitleScreen::playBackgroundMusic()
{
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/Audio/TitleScreenMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    titleMusic = new QMediaPlayer();
    titleMusic->setPlaylist(playlist);
    titleMusic->play();
}
