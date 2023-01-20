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

#include "rkPrefs.h"

rkPrefs::rkPrefs() {
    sprintf(this->fileName, "%s%s%s", HOME_PATH, FILE_PATH, FILE_NAME);
    //fileName = QApplication::applicationDirPath() + "/prefs.ini";
    // Default settings
    this->gameType = TRAVEL;
    this->numOfPlayers = 1;
    this->playerNames[0] = new QString("Player 1");
    this->numOfHighscores = 0;

    this->loadPrefs();
    //this->savePrefs();
}

//rkPrefs::rkPrefs(const rkPrefs& orig) {
//}

rkPrefs::~rkPrefs() {
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