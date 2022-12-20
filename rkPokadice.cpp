/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkPokadice.cpp
 * Author: rick
 * 
 * Created on 17 December 2022, 14:20
 */

#include <qt5/QtWidgets/qlayout.h>
#include "rkPokadice.h"

rkPokadice::rkPokadice(QWidget * parent) : QWidget (parent){
    
    this->vBox          = new QVBoxLayout(this);
    this->diceControl   = new rkDiceControl(5);
    this->scorecard     = new rkScorecard();
    this->vBox->addWidget(this->diceControl);
    this->vBox->addWidget(this->scorecard);
}

//rkDice::rkDice(const rkDice& orig) {
//}

rkPokadice::~rkPokadice() {
}

