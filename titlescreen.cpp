#include "titlescreen.h"
#include "gamescreen.h"
#include "ui_titlescreen.h"

TitleScreen::TitleScreen(QWidget *parent) : QWidget(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);

    QLabel *logo = ui->logo;
    logo->setPixmap(QPixmap(":/Images/gatorlogo.png"));
    logo->setScaledContents( true );

    //connect(ui->startBtn, QPushButton::pressed(), this, startButtonHandle());
}

TitleScreen::~TitleScreen()
{
    delete ui;
}

void TitleScreen::on_startBtn_clicked()
{
    GameScreen *game = new GameScreen();

    this->close();
    game->show();
}
