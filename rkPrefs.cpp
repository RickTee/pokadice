/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   prefs.cpp
 * Author: rick
 * 
 * Created on 02 January 2023, 10:06
 */

#include <qt5/QtWidgets/qwidget.h>

#include "rkPrefs.h"

rkPrefs::rkPrefs(QWidget * parent) : QWidget(parent){
    int i;
    sprintf(this->fileName, "%s%s%s", HOME_PATH, FILE_PATH, FILE_NAME);
    //fileName = QApplication::applicationDirPath() + "/prefs.ini";
    for(i = 0; i < MAXPLAYERS; i++){
        this->playerNames[i] = NULL;
    }
    for(i = 0; i < MAXHIGHSCORES; i++){
        this->highScoreNames[i] = NULL;
    }
    // Default settings
    this->gameType = TRAVEL;
    this->numOfPlayers = 1;
    this->numOfPlayersCpy = 0;
    this->playerNames[0] = new QString("Player 1");
    this->numOfHighscores = 0;

    this->loadPrefs();
    //this->savePrefs();
}

//rkPrefs::rkPrefs(const rkPrefs& orig) {
//}

rkPrefs::~rkPrefs() {
}

// About
void rkPrefs::aboutDialog(void){
    this->dialog = new QDialog();
    this->dialog->setModal(true);
    QString *aboutString = new QString(APPLICATION"\n" DESCRIPTION"\n\n" "Author: " AUTHOR"\n" EMAIL"\n");
    
    this->dialog->setWindowTitle("About");
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->title = new QLabel("About");
    this->title->setAlignment(Qt::AlignCenter);
    this->message = new QLabel(*aboutString);
    this->message->setAlignment(Qt::AlignCenter);
    this->okButton = new QPushButton("Ok");
    this->newGameButton = new QPushButton("New Game");
    this->quitButton = new QPushButton("Quit Game");

    this->vBox->addWidget(this->title);
    this->vBox->addWidget(this->message);
    //this->vBox->addWidget(this->winnerScore);
    this->dialog->setLayout(this->vBox);
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->okButton);
    this->hBox->addWidget(this->newGameButton);
    this->hBox->addWidget(this->quitButton);

    connect(this->okButton, SIGNAL(clicked()), SLOT(slotExitDialog()));
    connect(this->newGameButton, SIGNAL(clicked()), SLOT(slotNewGame()));
    connect(this->quitButton, SIGNAL(clicked()), SLOT(slotQuitGame()));
    
    this->dialog->show();
}

//Game over
void rkPrefs::winnerDialog(QString *name, int score){
    this->dialog = new QDialog();
    //this->dialog->setWindowFlags("Qt::WA_DeleteOnClose");
    this->dialog->setModal(true);
    this->dialog->setWindowTitle("Game Over");
    
    this->wScore = new QString();
    this->wScore->setNum(score);
    this->winner = new QString("With a score of : ");
    this->winner->append(this->wScore);
    this->message = new QLabel(*this->winner);
    this->message->setAlignment(Qt::AlignCenter);
    this->winnerName = new QLabel(*name);
    this->winnerName->setAlignment(Qt::AlignCenter);
    this->winnerName->setStyleSheet("QLabel {color: red; font: 16px}");
        
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->hBox1 = new QHBoxLayout();
    this->title = new QLabel("Winner");
    this->title->setAlignment(Qt::AlignCenter);

    this->okButton = new QPushButton("Ok");
    this->newGameButton = new QPushButton("New Game");
    this->quitButton = new QPushButton("Quit Game");

    this->vBox->addWidget(this->title);
    this->vBox->addWidget(this->winnerName);
    this->vBox->addWidget(this->message);
    this->vBox->addLayout(this->hBox1);
    this->dialog->setLayout(this->vBox);
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->okButton);
    this->hBox->addWidget(this->newGameButton);
    this->hBox->addWidget(this->quitButton);

    connect(this->okButton, SIGNAL(clicked()), SLOT(slotExitDialog()));
    connect(this->newGameButton, SIGNAL(clicked()), SLOT(slotNewGame()));
    connect(this->quitButton, SIGNAL(clicked()), SLOT(slotQuitGame()));
    
    this->dialog->exec();
}

// Settings
void rkPrefs::settingsDialog(void){
    int i;
    this->dialog = new QDialog();
    this->dialog->setModal(true);
    this->dialog->setWindowTitle("Settings");
        
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->hBox1 = new QHBoxLayout();
    this->title = new QLabel("Settings");
    this->addPlayerButton = new QPushButton("Add Player");
    this->deletePlayerButton = new QPushButton("Delete Player");
    this->okButton = new QPushButton("Ok");
    this->cancelButton = new QPushButton("Cancel");
    
    this->vBox->addWidget(this->title);
    this->dialog->setLayout(this->vBox);
    
    for(i = 0; i < this->numOfPlayers; i++){
        this->playerEdit[i] = new QLineEdit(*this->playerNames[i]);
        this->vBox->addWidget(this->playerEdit[i]);
    }
    
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->addPlayerButton);
    this->hBox->addWidget(this->deletePlayerButton);
    this->vBox->addLayout(this->hBox1);
    this->hBox1->addWidget(this->okButton);
    this->hBox1->addWidget(this->cancelButton);
    
    connect(this->cancelButton, SIGNAL(clicked()), SLOT(slotSettingsCancelled()));
    connect(this->okButton, SIGNAL(clicked()), SLOT(slotSettingsDone()));
    connect(this->addPlayerButton, SIGNAL(clicked()), this, SLOT(slotAddPlayer()));
    connect(this->deletePlayerButton, SIGNAL(clicked()), SLOT(slotDeletePlayer()));
    
    this->dialog->show();
}

void rkPrefs::slotAddPlayer(void){
    QString *num;
    //if(!(this->playerNames[this->numOfPlayers])) {
        this->playerNames[this->numOfPlayers] = new QString("Player");
        num = new QString();
        num->setNum(this->numOfPlayers + 1);
        this->playerNames[this->numOfPlayers]->append(num);
        this->playerEdit[this->numOfPlayers] = new QLineEdit(*this->playerNames[this->numOfPlayers]);
        this->vBox->insertWidget(this->numOfPlayers + 1, this->playerEdit[this->numOfPlayers]);
    //}
    
    // Problem: if user hits cancel after pressing add player numOfPlayers is still incremented
    this->numOfPlayers++;
    if(this->numOfPlayers > MAXPLAYERS) this->numOfPlayers = MAXPLAYERS;
}

void rkPrefs::slotDeletePlayer(void){
    if(this->numOfPlayers > 1) {
        //Remove the Edit box and decrement player count
        this->vBox->removeWidget(this->playerEdit[this->numOfPlayers]);
        this->numOfPlayers--;
        this->playerEdit[this->numOfPlayers]->hide();
        this->dialog->hide();
        this->dialog->show();
    }
}

void rkPrefs::slotSettingsDone(void){
    int i;
    for(i = 0; i < this->numOfPlayers; i++){
        this->playerNames[i] = new QString(this->playerEdit[i]->text());
    }
    this->savePrefs();
    this->dialog->close();
    emit sigNewGame();
}

void rkPrefs::slotNewGame(void){
    this->dialog->close();
    emit sigNewGame();
}

void rkPrefs::slotQuitGame(void){
    this->dialog->close();
    emit sigQuitGame();
}
// User pressed cancel
void rkPrefs::slotSettingsCancelled(void){
    this->numOfPlayers = this->numOfPlayersCpy;
    slotExitDialog();
}

void rkPrefs::slotExitDialog(void){
    std::cout << "slotExitDialog this->numOfPlayers " << this->numOfPlayers << "\n";
    std::cout << "slotExitDialog this->numOfPlayersCpy " << this->numOfPlayersCpy << "\n";
    this->dialog->close();
}

void rkPrefs::getAtribute(int att, _Msg *msg) {
    switch (att) {
        case GAME_TYPE: msg->gameType = this->gameType;
            break;
        case NUM_OF_PLAYERS: msg->numOfPlayers = this->numOfPlayers;
            break;
        case PLAYER_NAMES: msg->playerNames = this->playerNames;
            break;

    }

}

void rkPrefs::savePrefs() {
    int i;

    QSettings settings(this->fileName, QSettings::NativeFormat);
    settings.beginGroup("Game");
    settings.setValue("Type", this->gameType);
    settings.endGroup();

    settings.beginGroup("PlayerNames");
    settings.beginWriteArray("Players");
    for (i = 0; i < this->numOfPlayers; i++) {
        settings.setArrayIndex(i);
        settings.setValue("Name", *this->playerNames[i]);
    }
    settings.endArray();
    settings.endGroup();
    
    settings.beginGroup("HighScoreNames");
    settings.beginWriteArray("HighScores");
    for (i = 0; i < this->numOfHighscores; i++) {
        settings.setArrayIndex(i);
        settings.setValue("Name", *this->highScoreNames[i]);
        settings.setValue("Score", this->highScoreScores[i]);
    }
    settings.endArray();
    settings.endGroup();
}

void rkPrefs::loadPrefs() {
    int i;

    if (QFile(fileName).exists()) {
        QSettings settings(this->fileName, QSettings::NativeFormat);
        settings.beginGroup("Game");
        this->gameType = settings.value("type", "").toInt();
        settings.endGroup();

        settings.beginGroup("PlayerNames");
        this->numOfPlayers = settings.beginReadArray("Players");
        for (i = 0; i < this->numOfPlayers; i++) {
            settings.setArrayIndex(i);
            this->playerNames[i] = new QString(settings.value("Name").toString());
        }
        settings.endArray();
        settings.endGroup();
        
        settings.beginGroup("HighScoreNames");
        settings.beginReadArray("HighScores");
        for (i = 0; i < this->numOfHighscores; i++) {
            settings.setArrayIndex(i);
            this->highScoreNames[i] = new QString(settings.value("Name").toString());
            this->highScoreScores[i] = settings.value("Score").toInt();
        }
        settings.endArray();
        settings.endGroup();
    
    } else savePrefs();
}