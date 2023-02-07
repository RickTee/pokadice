/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkPrefs.cpp
 * Author: rick
 * 
 * Created on 03 February 2023, 11:32
 */

#include "rkPrefs.h"

int rkPrefs::prefsCount=0;

rkPrefs::rkPrefs() {
    int i;
    this->prefsCount ++;
    this->fileName = new QString(HOME_PATH);
    this->fileName->append(FILE_PATH);
    this->fileName->append(FILE_NAME);
            
    //fileName = QApplication::applicationDirPath() + "/prefs.ini";
    for(i = 0; i < MAXPLAYERS; i++){
        this->playerNames[i] = NULL;
    }
    for(i = 0; i < MAXHIGHSCORES; i++){
        this->highScoreNames[i] = NULL;
        this->highScoreScores[i] = 0;
    }
    
    // Default settings
    this->gameType = TRAVEL;
    this->numOfPlayers = 1;
    this->numOfPlayersCpy = 0;
    this->numOfHighscores = 0;

    this->loadPrefs();
}

rkPrefs::~rkPrefs() {
    // Class is not derived from any Qt class which maybe why it required cleanup
    delete this;
}

void rkPrefs::savePrefs() {
    int i;

    QSettings settings(*this->fileName, QSettings::NativeFormat);
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

    if (QFile(*this->fileName).exists()) {
        QSettings settings(*this->fileName, QSettings::NativeFormat);
        settings.beginGroup("Game");
        this->gameType = settings.value("type", "").toInt();
        settings.endGroup();

        settings.beginGroup("PlayerNames");
        this->numOfPlayers = settings.beginReadArray("Players");
        for (i = 0; i < this->numOfPlayers; i++) {
            settings.setArrayIndex(i);
            // if this player name already exists delete the QString
            if(this->playerNames[i] != NULL) 
            {
                delete this->playerNames[i];
                this->playerNames[i] = NULL;
            }
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
    
    } else {
        this->playerNames[0] = new QString("Player 1");
        savePrefs();
    }
}
