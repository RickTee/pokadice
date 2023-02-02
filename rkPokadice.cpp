/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkPokadice.cpp
 * Author: rick
 * 
 * Created on 20 December 2022, 14:20
 */
#include <stdio.h>
#include <qt5/QtWidgets/qlayout.h>
#include <qt5/QtWidgets/qmenubar.h>
#include "rkPokadice.h"

rkPokadice::rkPokadice(QWidget * parent) : QWidget(parent) {
    randomize();
    this->setWindowTitle("Pokadiceingtonville");
    buildMenu();
    this->prefs = new rkPrefs();
    this->vBox = new QVBoxLayout(this);
    this->vBox->setMargin(0);
    this->diceControl = new rkDiceControl(5);
    this->scoreTabs = new QTabWidget();
    this->vBox->addWidget(this->menuBar);
    this->vBox->addWidget(this->diceControl);
    this->vBox->addWidget(this->scoreTabs);
    this->currentPlayer = 0;
    
    if(TEST) {
        this->testButton = new QPushButton("Test");
        this->vBox->addWidget(this->testButton);
        connect(this->testButton, SIGNAL(clicked()), this, SLOT(slotTestGame()));
    }
    addScorecards();
    
    connect(this->diceControl, SIGNAL(diceRolled()), this, SLOT(slotSetScore()));
}

//rkPokadice::rkPokadice(const rkPokadice& orig) {
//}

rkPokadice::~rkPokadice() {
}

void rkPokadice::buildMenu() {
    this->menuBar = new QMenuBar();
    // File menu
    this->fileMenu = new QMenu("File");
    this->newGame = new QAction(QIcon("icons/new-game.png"), "&New Game");
    this->fileMenu->addAction(this->newGame);
    this->fileMenu->addSeparator();
    this->quitGame = new QAction(QIcon("icons/exit.png"), "&Quit");
    this->fileMenu->addAction(this->quitGame);
    this->menuBar->addMenu(this->fileMenu);
    // Settings menu
    this->settingsMenu = new QMenu("Settings");
    this->preferences = new QAction(QIcon("icons/prefs.png"), "&Preferences");
    this->settingsMenu->addAction(this->preferences);
    this->menuBar->addMenu(this->settingsMenu);
    //Help menu
    this->helpMenu = new QMenu("Help");
    this->about = new QAction(QIcon("icons/help-about.png"), "About");
    this->helpMenu->addAction(this->about);
    this->menuBar->addMenu(this->helpMenu);

    connect(this->newGame, SIGNAL(triggered()), this, SLOT(slotNewGame()));
    connect(this->quitGame, SIGNAL(triggered()), this, SLOT(slotQuitGame()));
    connect(this->preferences, SIGNAL(triggered()), this, SLOT(slotPrefs()));
    connect(this->about, SIGNAL(triggered()), this, SLOT(slotAbout()));
}

void rkPokadice::addScorecards() {
    int i;
    for (i = 0; i < this->prefs->numOfPlayers; i++) {
        this->scorecard[i] = new rkScorecard();
        connect(this->scorecard[i], SIGNAL(sigTurnDone()), this, SLOT(slotEndTurn()));
        this->scoreTabs->addTab(this->scorecard[i], *this->prefs->playerNames[i]);
    }
}

void rkPokadice::removeScorcards() {
    this->scoreTabs->clear();
    // Seems there is not need to delete the tab pages, run a profile to make sure
    //for(i = 0; i < this->prefs->numOfPlayers; i++){
        //if(this->scorecard[i]) delete this->scorecard[i];
    //}
}

void rkPokadice::slotNewGame() {
    
    this->diceControl->diceReset();
    // Remove the old score cards
    this->removeScorcards();
    this->addScorecards();
}

void rkPokadice::slotQuitGame() {
    // Clean up and exit
    close();
}

void rkPokadice::slotPrefs() {
    this->prefs->numOfPlayersCpy = this->prefs->numOfPlayers;
    this->prefs->settingsDialog();
    connect(this->prefs, SIGNAL(sigNewGame()), this, SLOT(slotNewGame()));
    
}

void rkPokadice::slotAbout() {
    this->prefs->aboutDialog();
    connect(this->prefs, SIGNAL(sigQuitGame()), this, SLOT(slotQuitGame()));
    connect(this->prefs, SIGNAL(sigNewGame()), this, SLOT(slotNewGame()));
}

void rkPokadice::slotSetScore() {
    // Display the current players score card (tab)
    this->scoreTabs->setCurrentIndex(this->currentPlayer);
    // Set possible scores and activate score buttons
    this->scorecard[this->currentPlayer]->setScore(this->diceControl->diceValues);
}

void rkPokadice::slotEndTurn(void) {
    int i, flag = 0;
    //Msg msg;

    this->diceControl->diceReset();
    // Next player
    this->currentPlayer++;
    if (this->currentPlayer >= this->prefs->numOfPlayers) this->currentPlayer = 0;
    // Check if game is over
    for (i = 0; i<this->prefs->numOfPlayers; i++) {
        if (this->scorecard[i]->isScorecardFull()) {
            flag++;
        }
    }
    // If all score cards are full then end the game
    if (flag == this->prefs->numOfPlayers) {
        endGame();
    }
}

void rkPokadice::endGame(void) {
    int i, highscore = 0, score = 0, idx = 0;
    /* Get the number of active players */
    for (i = 0; i<this->prefs->numOfPlayers; i++) {
        score = this->scorecard[i]->getScore();
        if (score > highscore) {
            highscore = score;
            idx = i;
        }
    }

    this->prefs->winnerDialog(this->prefs->playerNames[idx], this->scorecard[idx]->getScore());

    connect(this->prefs, SIGNAL(sigQuitGame()), this, SLOT(slotQuitGame()));
    connect(this->prefs, SIGNAL(sigNewGame()), this, SLOT(slotNewGame()));
}

// Seed random number.
void rkPokadice::randomize(void) {
    unsigned int stime;
    time_t ltime;

    ltime = time(NULL);
    // Make small time difference of greater significance
    // to prevent repeating random sequences.
    ltime = ltime << 21;
    stime = (unsigned) ltime / 2;
    srand(stime);
}

void rkPokadice::slotTestGame(void){
    int i, j;
  
    for(i = 0; i < this->prefs->numOfPlayers; i++){
        for(j = 0; j < NUMOFSCORES; j++){
            if ((!this->scorecard[i]->scoreDone[j]) && (!(((j > 5) && (j < 9)) || (j > 15)))) {
                this->diceControl->rollDice();
                this->scorecard[i]->scoreButtons[j]->click();
            }
        }
    }
}