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

#include <QWidget>
#include <QBoxLayout>
#include <QTabWidget>
#include <QMenuBar>
#include "rkDialog.h"
#include "rkDiceControl.h"
#include "rkScorecard.h"
#include "rkPrefs.h"

class rkPokadice : public QWidget{
    Q_OBJECT
public:
    rkPokadice(QWidget * parent = 0);
    //rkDice(const rkPokadice& orig);
    virtual ~rkPokadice();
    QVBoxLayout     *vBox;
    rkDiceControl   *diceControl;
    rkScorecard     *scorecard[MAXPLAYERS];
    QTabWidget      *scoreTabs;
    QMenuBar        *menuBar;
    QMenu           *fileMenu;
    QMenu           *settingsMenu;
    QMenu           *helpMenu;
    QAction         *newGame;
    QAction         *quitGame;
    QAction         *preferences;
    QAction         *about;
    rkPrefs         *prefs;
    rkDialog        *dialog;
    int             currentPlayer;
    void            addScorecards(void);
    void            endGame(void);
    private:
        void buildMenu(void);
        void randomize(void);
    public slots:
        void slotSetScore(void);  // Tell the current players scorecard
                                    // to display possible scores.
	//void slotIsGameOver(void);  // Check for end game.
	//void slotAddPlayer(void);   // Add a scorecard.
	//void slotChangeName(void);  // Change the tab name.
	//void slotDeletePlayer(void);// Remove a scorecard.
	//void slotNewGame(void);     // Reset scorecards and dice.
	//void slotAbout(void);       // About dialog.
        void slotEndTurn(void);
    private slots:
        void slotNewGame(void);
        void slotQuitGame(void);
        void slotPrefs(void);
        void slotAbout(void);
    signals:
	void sigGameOver(void);
        void sigExit(void);         // User wants to quit.
};

#endif /* RKPOKADICE_H */
