/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkScorecard.cpp
 * Author: rick
 * 
 * Created on 17 December 2022, 14:20
 */

#include "rkScorecard.h"

rkScorecard::rkScorecard(QWidget * parent) : QWidget (parent){
    
    this->gBox              = new QGridLayout(this);
    this->scoreTitles[0]    = new QLabel("Aces");
    this->scores[0]         = new QLabel("0");
    this->scoreButtons[0]   = new QPushButton();
    this->scoreButtons[0]->setMinimumWidth(40);
    this->scoreButtons[0]->setMaximumWidth(40);
    this->scoreButtons[0]->setCheckable(true);
    
    this->gBox->addWidget(this->scoreTitles[0], 0, 0);
    this->gBox->addWidget(this->scores[0], 0, 1);
    this->gBox->addWidget(this->scoreButtons[0], 0, 2);
    //this->hBoxHoldButton->insertStretch(0); 
    //this->hBoxHoldButton->addWidget(this->holdButton);
    //this->hBoxHoldButton->insertStretch(-1);
    
    //this->vBox->setContentsMargins(0,0,0,0);
    //connect(this->holdButton, SIGNAL(clicked()), SLOT(setHold()));
    // Set the dice image to num
}

//rkScorecard::rkScorecard(const rkScorecard& orig) {
//}

rkScorecard::~rkScorecard() {
}
