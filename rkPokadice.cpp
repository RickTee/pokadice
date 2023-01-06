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
    this->setWindowTitle("Pokadiceintonville");
    buildMenu();
    this->prefs = new rkPrefs();
    
    this->vBox = new QVBoxLayout(this);
    this->vBox->setMargin(0);
    this->diceControl = new rkDiceControl(5);
    this->scoreTabs = new QTabWidget();
    this->vBox->addWidget(this->menuBar);
    this->vBox->addWidget(this->diceControl);
    this->vBox->addWidget(this->scoreTabs);

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
    this->newGame = new QAction(QIcon("icons/new-game.png"),"&New Game");
    this->fileMenu->addAction(this->newGame);
    this->fileMenu->addSeparator();
    this->quitGame = new QAction(QIcon("icons/exit.png"),"&Quit");
    this->fileMenu->addAction(this->quitGame);
    this->menuBar->addMenu(this->fileMenu);
    // Settings menu
    this->settingsMenu = new QMenu("Settings");
    this->preferences = new QAction(QIcon("icons/prefs.png"),"&Preferences");
    this->settingsMenu->addAction(this->preferences);
    this->menuBar->addMenu(this->settingsMenu);
    //Help menu
    this->helpMenu = new QMenu("Help");
    this->about = new QAction(QIcon("icons/help-about.png"),"About");
    this->helpMenu->addAction(this->about);
    this->menuBar->addMenu(this->helpMenu);
    
    connect(this->newGame, SIGNAL(triggered()), this, SLOT(slotNewGame()));
    connect(this->quitGame, SIGNAL(triggered()), this, SLOT(slotQuitGame()));
    connect(this->preferences, SIGNAL(triggered()), this, SLOT(slotPrefs()));
    connect(this->about, SIGNAL(triggered()), this, SLOT(slotAbout()));
}

void rkPokadice::addScorecards() {
    this->scorecard = new rkScorecard();
    connect(this->scorecard, SIGNAL(sigTurnDone()), this, SLOT(slotEndTurn()));
    this->scoreTabs->addTab(this->scorecard, this->prefs->playerNames[0]);
}

void rkPokadice::slotNewGame() {
    printf("slotNewGame\n");
    if(this->gameOverDialog) this->gameOverDialog->close();
    this->diceControl->diceReset();
    this->scorecard->scorecardReset();
}

void rkPokadice::slotQuitGame() {
    // Clean up and exit
    if(this->gameOverDialog) this->gameOverDialog->close();
    close();
}

void rkPokadice::slotPrefs() {
    
}

void rkPokadice::slotAbout() {
    
}

void rkPokadice::slotSetScore() {
    // Set possible scores and activate score buttons
    this->scorecard->setScore(this->diceControl->diceValues);
}

void rkPokadice::slotEndTurn(void) {
    int i, flag = 0;
    QString *winner;
    //Msg msg;

    this->diceControl->diceReset();
    /* Next player */
    //    this->priv->current_player++;
    //    config_get_num(CONFIG(this->priv->prefs), &msg);
    //    /* If this is the last player then the first player is up */
    //    if(this->priv->current_player >= msg.num_of_players) this->priv->current_player = 0;
    //    /* Check if game is over */
    //    for(i=0;i<msg.num_of_players;i++)
    //    {
    if (this->scorecard->isScorecardFull()) {
        flag++;
    }
    if (flag) {
        
        this->gameOverDialog = new rkDialog();
        this->gameOverDialog->setWindowTitle("Game Over");
        //this->gameOverDialog->setModal(true);
        winner = new QString("The winner is: ");
        winner->append(this->prefs->playerNames[0]);
        
        connect(this->gameOverDialog, SIGNAL(sigQuitGame()), this, SLOT(slotQuitGame()));
        connect(this->gameOverDialog, SIGNAL(sigNewGame()), this, SLOT(slotNewGame()));
        this->gameOverDialog->show();
    }
    //    }
    //    /* If all score cards are full then end the game */
    //    if(flag == msg.num_of_players) rgt_yarzee_end_game(this);
    //    return TRUE;
}

//bool rkPokadice::newGame(int action, GtkWidget *menu_item)
//{
//    gint i;
//    Msg msg;
//    
//    config_get_num(CONFIG(this->priv->prefs), &msg);
//
//    for(i=0;i<msg.num_of_players;i++)
//    {
//        rgt_scorecard_reset(RGT_SCORECARD(this->priv->scorecard[i]));
//    }
//    this->priv->current_player = 0;
//    rgt_dice_reset(RGT_DICE(this->priv->dice));
//    return TRUE;
//}

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