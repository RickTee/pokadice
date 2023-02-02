/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkDiceControl.h
 * Author: rick
 *
 * Created on 18 December 2022, 09:20
 */

#ifndef RKDICECONTROL_H
#define RKDICECONTROL_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QBoxLayout>
#include <QPushButton>
#include "rkDice.h"
#include "rkPrefs.h"

class rkDiceControl : public QWidget{
    Q_OBJECT
public:
    rkDiceControl(int numOfDice, QWidget * parent = 0);
    //rkDiceControl(const rkDiceControl& orig);
    virtual ~rkDiceControl();
    QHBoxLayout *hBox;
    QVBoxLayout *vBox;
    QPushButton *toggleButton;
    QPushButton *rollDiceButton;
    QLabel      *rollCountLabel;
    QPixmap     *dicePixmaps[6];
    rkDice      *diceArray[NUMOFDICE];
    int         numOfDice;
    int         rollCount;
    int         diceValues[NUMOFDICE];

    int randNum(int);
    void diceReset(void);
    void disableHolds(void);
    
public slots:
	//void slot_clicked (int state){ clicked(state); }
    void toggleHolds();
    void rollDice();
    
signals:
    void diceRolled();

};

#endif /* RKDICECONTROL_H */

