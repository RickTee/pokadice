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

class rkPrefs {
public:
    rkPrefs();
    rkPrefs(const rkPrefs& orig);
    virtual ~rkPrefs();
    
public:
    int     gameType;
    int     numOfPlayers;
    char    playerNames[MAXPLAYERS][MAXLEN];
    char    fileName[512];
    int     numOfHighscores;
    char    highScoreNames[MAXPLAYERS][MAXLEN];
    int     highScoreScores[MAXPLAYERS];
    int     highScoreRanks[MAXPLAYERS];

    void savePrefs(void);
    void loadPrefs(void);
};

#endif /* PREFS_H */

