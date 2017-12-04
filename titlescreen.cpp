#include "titlescreen.h"
#include "ui_titlescreen.h"


TitleScreen::TitleScreen(QWidget *parent) : QWidget(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);

    ui->logo->setPixmap(QPixmap(":/Images/gatorlogo.png"));
    ui->logo->setScaledContents( true );

    QMovie *wasdAnimation = new QMovie(":/Images/wasdAnimated.gif");
    ui->wasdImg->setMovie(wasdAnimation);
    ui->wasdImg->setScaledContents( true );
    wasdAnimation->start();

    ui->backButton->setVisible(false);
    ui->howToText->setVisible(false);
    ui->wasdImg->setVisible(false);
    ui->gatorIcon->setVisible(false);
    ui->fsuIcon->setVisible(false);
    ui->georgiaIcon->setVisible(false);
    ui->lsuIcon->setVisible(false);
    ui->kentuckyIcon->setVisible(false);
    ui->pacmanTitle->setVisible(false);
    ui->blinkyTitle->setVisible(false);
    ui->pinkyTitle->setVisible(false);
    ui->inkyTitle->setVisible(false);
    ui->clydeTitle->setVisible(false);


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

// Shows How To Play screen
void TitleScreen::on_howToButton_clicked() {
    ui->backButton->setVisible(true);
    ui->logo->setVisible(false);
    ui->startBtn->setVisible(false);
    ui->howToButton->setVisible(false);
    ui->howToText->setVisible(true);
    ui->wasdImg->setVisible(true);
    ui->gatorIcon->setVisible(true);
    ui->fsuIcon->setVisible(true);
    ui->georgiaIcon->setVisible(true);
    ui->lsuIcon->setVisible(true);
    ui->kentuckyIcon->setVisible(true);
    ui->pacmanTitle->setVisible(true);
    ui->blinkyTitle->setVisible(true);
    ui->pinkyTitle->setVisible(true);
    ui->inkyTitle->setVisible(true);
    ui->clydeTitle->setVisible(true);
}

// Goes back to title screen
void TitleScreen::on_backButton_clicked() {
    ui->backButton->setVisible(false);
    ui->logo->setVisible(true);
    ui->startBtn->setVisible(true);
    ui->howToButton->setVisible(true);
    ui->howToText->setVisible(false);
    ui->wasdImg->setVisible(false);
    ui->gatorIcon->setVisible(false);
    ui->fsuIcon->setVisible(false);
    ui->georgiaIcon->setVisible(false);
    ui->lsuIcon->setVisible(false);
    ui->kentuckyIcon->setVisible(false);
    ui->pacmanTitle->setVisible(false);
    ui->blinkyTitle->setVisible(false);
    ui->pinkyTitle->setVisible(false);
    ui->inkyTitle->setVisible(false);
    ui->clydeTitle->setVisible(false);
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
