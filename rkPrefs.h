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
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "version.h"

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
enum _Attributes {
    GAME_TYPE, NUM_OF_PLAYERS, PLAYER_NAMES, NUM_OF_HIGHSCORES,
    HIGH_SCORE_NAMES, HIGH_SCORE_SCORES
};

struct _Msg {
    int gameType;
    int numOfDice;
    int numOfPlayers;
    QString **playerNames;
    int numOfHighscores;
    QString **highScoreNames;
    int *highScoreScores;
};

class rkPrefs : public QWidget{
    Q_OBJECT
public:
    rkPrefs(QWidget * parent = 0);
    rkPrefs(const rkPrefs& orig);
    virtual ~rkPrefs();
    int gameType;
    int numOfPlayers;
    int numOfPlayersCpy;
    QString *playerNames[MAXPLAYERS];
    int numOfHighscores;
    QString *highScoreNames[MAXHIGHSCORES];
    int highScoreScores[MAXHIGHSCORES];
    QDialog     *dialog;
    QVBoxLayout *vBox;
    QHBoxLayout *hBox;
    QHBoxLayout *hBox1;
    QLabel *title;
    QLabel *message;
    QLabel *winnerScore;
    QLabel *winnerName;
    QString *winner;
    QString *wScore;
    QPushButton *addPlayerButton;
    QPushButton *deletePlayerButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *newGameButton;
    QPushButton *quitButton;
    QPushButton *resetScoreButton;
    QLineEdit *playerEdit[MAXPLAYERS];
    void    setMessage(QString);
    void    setAtribute(int att, _Msg *msg);
    void    getAtribute(int att, _Msg *msg);
    void    savePrefs(void);
    void    loadPrefs(void);
    void    aboutDialog(void);
    void    winnerDialog(QString *name, int score);
    void    settingsDialog(void);

private:
    char fileName[512];
    
public slots:
    void slotExitDialog(void);
    void slotSettingsDone(void);
    void slotSettingsCancelled(void);
    void slotAddPlayer(void);
    void slotDeletePlayer(void);
    void slotQuitGame(void);
    void slotNewGame(void);

signals:
    void sigNewGame(void);
    void sigQuitGame(void);
};

#endif /* PREFS_H */

