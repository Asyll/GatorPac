#include "titlescreen.h"
#include "ui_titlescreen.h"


TitleScreen::TitleScreen(QWidget *parent) : QWidget(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);

    ui->logo->setPixmap(QPixmap(":/Images/gatorlogo.png"));
    ui->logo->setScaledContents( true );
    ui->backButton->setVisible(false);
    ui->howToText->setVisible(false);

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
}

// Goes back to title screen
void TitleScreen::on_backButton_clicked() {
    ui->backButton->setVisible(false);
    ui->logo->setVisible(true);
    ui->startBtn->setVisible(true);
    ui->howToButton->setVisible(true);
    ui->howToText->setVisible(false);
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
