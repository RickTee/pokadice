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
#include "rkPokadice.h"

rkPokadice::rkPokadice(QWidget * parent) : QWidget(parent) {
    
    randomize();

    this->vBox = new QVBoxLayout(this);
    this->vBox->setMargin(0);
    this->diceControl = new rkDiceControl(5);
    this->scorecard = new rkScorecard();
    this->vBox->addWidget(this->diceControl);
    this->vBox->addWidget(this->scorecard);

    connect(this->diceControl, SIGNAL(diceRolled()), this, SLOT(rolledDice()));
}

//rkPokadice::rkPokadice(const rkPokadice& orig) {
//}

rkPokadice::~rkPokadice() {
}

void rkPokadice::rolledDice() {

    this->scorecard->setScore(this->diceControl->diceValues);
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