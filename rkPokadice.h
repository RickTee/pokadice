/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkPokadice.h
 * Author: rick
 *
 * Created on 20 December 2022, 14:20
 */

#ifndef RKPOKADICE_H
#define RKPOKADICE_H

#include <QApplication>
#include <QWidget>
#include <QBoxLayout>
#include <QTabWidget>
#include <QMenuBar>
#include <QPushButton>
#include "rkDiceControl.h"
#include "rkScorecard.h"
#include "rkDialog.h"
#include "rkDialog.h"

#define TEST 1 // Creates a button for testing

class rkPokadice : public QWidget {
    Q_OBJECT
public:
    rkPokadice(QWidget * parent = 0);
    //rkDice(const rkPokadice& orig);
    virtual ~rkPokadice();
private:
    QVBoxLayout *vBox;
    rkDiceControl *diceControl;
    rkScorecard *scorecard[MAXPLAYERS];
    QTabWidget *scoreTabs;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *settingsMenu;
    QMenu *helpMenu;
    QAction *newGame;
    QAction *quitGame;
    QAction *preferences;
    QAction *about;
    rkPrefs *prefs;
    rkDialog *dialog;
    int currentPlayer;
    QPushButton *testButton;
    void addScorecards(void);
    void removeScorcards(void);
    void endGame(void);

    void buildMenu(void);
    void randomize(void);
public slots:
    void slotSetScore(void); // Tell the current players scorecard to display possible scores
    void slotEndTurn(void);
private slots:
    void slotNewGame(void); // Reset scorecards and dice.
    void slotQuitGame(void);
    void slotPrefs(void);
    void slotAbout(void);
    void slotTestGame(void);
    void slotCloseDialog(void);
signals:
    void sigGameOver(void);
    void sigExit(void); // User wants to quit.
};

#endif /* RKPOKADICE_H */
