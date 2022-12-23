/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkDice.cpp
 * Author: rick
 * 
 * Created on 17 December 2022, 14:20
 */

#include "rkDice.h"

rkDice::rkDice(int num, QPixmap *diceImage, QWidget * parent) : QWidget (parent){
    
    this->vBox              = new QVBoxLayout(this);
    this->hBoxDice          = new QHBoxLayout();
    this->hBoxHoldButton    = new QHBoxLayout();
    this->holdButton        = new QPushButton("Hold");
    this->diceFace          = new QLabel("0");
    
    this->holdButton->setFixedWidth(40);
    this->holdButton->setCheckable(true);
    this->diceFace->setLineWidth(2);
    this->diceFace->setFrameStyle(QFrame::Panel | QFrame::Raised);

    this->vBox->addLayout(this->hBoxDice);
    this->vBox->addLayout(this->hBoxHoldButton);
    this->hBoxDice->insertStretch(0);
    this->hBoxDice->addWidget(this->diceFace);
    this->hBoxDice->insertStretch(-1);
    this->hBoxHoldButton->insertStretch(0); 
    this->hBoxHoldButton->addWidget(this->holdButton);
    this->hBoxHoldButton->insertStretch(-1);
    
    this->vBox->setContentsMargins(0,0,0,0);
    this->onOff = false;
    connect(this->holdButton, SIGNAL(clicked()), SLOT(setHold()));
    // Set the dice image to num
    this->setNum(num, diceImage);
}

//rkDice::rkDice(const rkDice& orig) {
//}

rkDice::~rkDice() {
}

void rkDice::setNum(int num, QPixmap *diceImage)
{
    // If this dice is held then return
    if(this->onOff) return;
    this->number = num;
    // Set the pixmap
    this->diceFace->setPixmap(*diceImage);
    }

int rkDice::getNum()
{
    return this->number;
    }

void rkDice::setHold(void)
{
    // Hold off
    if(this->onOff)
    {
        this->onOff = false;
        this->setStyleSheet("QPushButton {color: black}");
        this->holdButton->setText("Hold");
        this->holdButton->setChecked(false);
    }
    // Hold on
    else 
    {
        this->onOff = true;
        this->setStyleSheet("QPushButton {background-color: red; color: white}");
        this->holdButton->setText("Held");
        this->holdButton->setChecked(true);
    }
}
    
bool rkDice::getHold(void)
{
    return this->onOff;
}