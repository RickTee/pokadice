/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkPrefs.h
 * Author: rick
 *
 * Created on 03 February 2023, 11:32
 */

#ifndef RKPREFS_H
#define RKPREFS_H

#include <glib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <QString>
#include <QSettings>
#include <QVariant>
#include <QFile>

#define TRAVEL      1
#define NUMOFDICE   5
#define MAXPLAYERS  6
#define MAXHIGHSCORES 10
#define MAXLEN      81
#define FILE_NAME   "pokadice.cfg"
#define FILE_PATH   "/.config/Pokadice/"

#ifdef  __linux__
#define HOME_PATH   g_getenv("HOME")
#endif
#ifdef _WIN64  
#define HOME_PATH   g_getenv("APPDATA")
#endif

/* g_get_home_dir () */

class rkPrefs {
public:
    rkPrefs();
    rkPrefs(const rkPrefs& orig);
    static int instanceCount;
    virtual ~rkPrefs();
    int gameType;
    int numOfPlayers;
    int numOfPlayersCpy;
    QString *playerNames[MAXPLAYERS];
    int numOfHighscores;
    QString *highScoreNames[MAXHIGHSCORES];
    int highScoreScores[MAXHIGHSCORES];
    void savePrefs(void);
    void loadPrefs(void);
private:
    QString *fileName;
};

#endif /* RKPREFS_H */

