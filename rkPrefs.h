/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   prefs.h
 * Author: rick
 *
 * Created on 02 January 2023, 10:06
 */

#ifndef PREFS_H
#define PREFS_H

#include <glib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <QString>
#include <QSettings>
#include <QFile>

#define TRAVEL      1
#define MAXPLAYERS  6
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
enum _Attributes { GAME_TYPE, NUM_OF_PLAYERS, PLAYER_NAMES, NUM_OF_HIGHSCORES,
HIGH_SCORE_NAMES, HIGH_SCORE_SCORES };

struct _Msg
{
    int     gameType;
    int     numOfPlayers;
    QString **playerNames;
    int     numOfHighscores;
    QString **highScoreNames;
    int     *highScoreScores;
};

class rkPrefs {
public:
    rkPrefs();
    rkPrefs(const rkPrefs& orig);
    virtual ~rkPrefs();
    int     gameType;
    int     numOfPlayers;
    QString *playerNames[MAXPLAYERS];
    int     numOfHighscores;
    QString *highScoreNames[MAXPLAYERS];
    int     highScoreScores[MAXPLAYERS];
    void    setAtribute(int att, _Msg *msg);
    void    getAtribute(int att, _Msg *msg);
    void    savePrefs(void);
    void    loadPrefs(void);
    
private:
    char    fileName[512];
};

#endif /* PREFS_H */

