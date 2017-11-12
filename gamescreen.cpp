#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QThread>
#include <QtWidgets>
#include "titlescreen.h"

GameScreen::GameScreen(QWidget *parent) : QWidget(parent), ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,580,620);

    QGraphicsView *gameView = ui->gameView;
    gameView->setScene(scene);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setSceneRect(scene->sceneRect());

    gameMap = new GameMap();
    scene->addItem(gameMap);



}

GameScreen::~GameScreen()
{
    delete ui;
}

/*Play 8 bit evil morty for the eventual death scene when we get there.
When all lives lost then stops other music and plays final music. But
for now I just have it playing when the map pops up*/
void GameScreen::playDeathMusic()
{
    finalDeathMusic->setMedia(QUrl("qrc:/Audio/FinalDeathMusic.mp3"));
    if (finalDeathMusic->state() == QMediaPlayer::PlayingState) {
        finalDeathMusic->setPosition(0);
    }
    else if (finalDeathMusic->state() == QMediaPlayer::StoppedState) {
        finalDeathMusic->play();
    }
}
