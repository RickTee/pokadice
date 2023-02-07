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

#ifndef RKDIALOGS_H
#define RKDIALOGS_H

#include <glib.h>
#include <iostream>
#include <fstream>
#include <QString>
#include <QSettings>
#include <QFile>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "rkPrefs.h"
#include "version.h"

class rkDialog : public QDialog {
    Q_OBJECT
public:
    // About dialog
    rkDialog(QWidget * parent = 0);
    // Game over dialog
    rkDialog(QString *name, int score, QWidget * parent = 0);
    // Settings dialog
    rkDialog(rkPrefs *prfs, QWidget * parent = 0);
    virtual ~rkDialog();
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
    rkPrefs *prefs;
    void aboutDialog(void);
    void winnerDialog(QString *name, int score);
    void settingsDialog(void);
private:
    char fileName[512];
private slots:
    void slotAddPlayer(void);
    void slotDeletePlayer(void);
    void slotExitDialog(void);
    void slotSettingsDone();
    void slotSettingsCancelled(void);
public slots:
    void slotPrefsQuitGame(void);
    void slotPrefsNewGame(void);

signals:
    void sigNewGame(void);
    void sigQuitGame(void);
    void sigDialogDone(void);
};

#endif /* RKDIALOGS_H */

