/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkDiceControl.cpp
 * Author: rick
 * 
 * Created on 18 December 2022, 09:20
 */
#include <iostream>
#include <time.h>
#include <qt5/QtWidgets/qlayout.h>
#include "rkDiceControl.h"

rkDiceControl::rkDiceControl(int numOfDice, QWidget * parent) : QWidget (parent){
    
    int i;
    this->dicePixmaps[0] = new QPixmap("gfx/d1.png");
    this->dicePixmaps[1] = new QPixmap("gfx/d2.png");
    this->dicePixmaps[2] = new QPixmap("gfx/d3.png");
    this->dicePixmaps[3] = new QPixmap("gfx/d4.png");
    this->dicePixmaps[4] = new QPixmap("gfx/d5.png");
    this->dicePixmaps[5] = new QPixmap("gfx/d6.png");
    this->numOfDice = numOfDice;
    this->rollCount = 3;
    this->hBox = new QHBoxLayout(this);
    
    for(i = 0; i < this->numOfDice; i ++)
    {
        this->diceValues[i] = randNum(6);
        this->diceArray[i]  = new rkDice(this->diceValues[i], this->dicePixmaps[this->diceValues[i]]);
        this->hBox->addWidget(this->diceArray[i]);
    }
    this->vBox              = new QVBoxLayout();
    this->toggleButton      = new QPushButton("Tog");
    this->toggleButton->setToolTip("Toggle all holds");
    this->toggleButton->setMinimumWidth(40);
    this->toggleButton->setMaximumWidth(40);
    this->rollCountLabel    = new QLabel();
    this->rollCountLabel->setNum(this->rollCount);
    this->rollCountLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    this->rollCountLabel->setMargin(-4);
    this->rollDiceButton    = new QPushButton("Roll");
    this->rollDiceButton->setToolTip("Roll the dice");
    this->rollDiceButton->setMinimumWidth(40);
    this->rollDiceButton->setMaximumWidth(40);
    this->vBox->addWidget(this->toggleButton);
    this->vBox->addWidget(this->rollCountLabel);
    this->vBox->addWidget(this->rollDiceButton);
    this->hBox->addLayout(this->vBox);
    
    for(i = 0; i < this->numOfDice; i ++)
    {
        this->diceArray[i]->disableHold();
    }
    
    connect(this->toggleButton, SIGNAL(clicked()), SLOT(toggleHolds()));
    connect(this->rollDiceButton, SIGNAL(clicked()), SLOT(rollDice()));
}

//rkDiceControl::rkDiceControl(const rkDiceControl& orig) {
//}

rkDiceControl::~rkDiceControl() {
    int i;
    for(i = 0; i < 6; i++) {
        delete this->dicePixmaps[i];
    }
    
}

void rkDiceControl::disableHolds(void)
{
    int i;
    for(i=0; i < this->numOfDice; i++)
    {
        this->diceArray[i]->disableHold();
    }
}

void rkDiceControl::toggleHolds(void)
{
    int i;
    for(i=0; i < this->numOfDice; i++)
    {
        this->diceArray[i]->slotToggleHold();
    }
}

void rkDiceControl::diceReset(void)
{
    int i;
    for(i=0; i < this->numOfDice; i++)
    {
        /* Reset all the hold buttons and disable them */
        this->diceArray[i]->resetHold();
        //this->diceArray[i]->disableHold();
    }
    /* Reset the roll count */
    this->rollCount = 3;
    //this->rollCountLabel->setText(QString::number(this->rollCount));
    this->rollCountLabel->setNum(this->rollCount);
}

void rkDiceControl::rollDice()
{
    int i;
    
    if(this->rollCount > 0)
    {
        for(i=0; i < this->numOfDice; i++)
        {
            if(this->diceArray[i]->getHold() == false)
            {
                this->diceValues[i] = randNum(6);
                this->diceArray[i]->setNum(this->diceValues[i], this->dicePixmaps[this->diceValues[i]]);
            }
            this->diceArray[i]->enableHold();
        }
        --this->rollCount;
        //this->rollCountLabel->setText(QString::number(this->rollCount));
        this->rollCountLabel->setNum(this->rollCount);
        // Send signal dice_rolled
        emit diceRolled();
    }
}

// Return a random number between 0 and max.
int rkDiceControl::randNum(int max)
{
    int num;
    float val;

	val = (float)rand();
	num = (int)((val / RAND_MAX) * max);
	if(num == max) { num = randNum(max); }
        // rand() % 6
	return(num);
}
