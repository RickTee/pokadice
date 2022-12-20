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
#include <stdio.h>
#include <time.h>
#include <qt5/QtWidgets/qlayout.h>
#include "rkDiceControl.h"

rkDiceControl::rkDiceControl(int numOfDice, QWidget * parent) : QWidget (parent){
    
    int i;
    this->numOfDice = numOfDice;
    this->rollCount = 3;
    this->hBox = new QHBoxLayout(this);
    
    for(i = 0; i < 6; i ++)
    {
        QString tmp = QString::number(i+1);
        this->dicePixmaps[i] = new QPixmap("gfx/d" + tmp + ".gif");
    }
    for(i = 0; i < this->numOfDice; i ++)
    {
        this->diceArray[i]  = new rkDice(6, this->dicePixmaps[5]);
        this->hBox->addWidget(this->diceArray[i]);
    }
    this->vBox              = new QVBoxLayout();
    this->toggleButton      = new QPushButton("Tog");
    this->toggleButton->setToolTip("Toggle all holds");
    this->toggleButton->setMinimumWidth(40);
    this->toggleButton->setMaximumWidth(40);
    this->rollCountLabel    = new QLabel(QString::number(this->rollCount)); //str.toInt();
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
    
    connect(this->toggleButton, SIGNAL(clicked()), SLOT(toggleHolds()));
    connect(this->rollDiceButton, SIGNAL(clicked()), SLOT(rollDice()));
}

//rkDiceControl::rkDiceControl(const rkDiceControl& orig) {
//}

rkDiceControl::~rkDiceControl() {
}

void rkDiceControl::toggleHolds()
{
    int i;
    for(i=0; i<this->numOfDice; i++)
    {
        this->diceArray[i]->setHold();
    }
}

void rkDiceControl::rollDice()
{
    int i, j;
    
    if(this->rollCount > 0)
    {
        for(i=0; i < this->numOfDice; i++)
        {
            j = randNum(6);
            this->diceArray[i]->setNum(j, this->dicePixmaps[j]);
        }
        --this->rollCount;
        this->rollCountLabel->setText(QString::number(this->rollCount));
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
	return(num);
}


// Seed random number.
void rkDiceControl::randomize(void)
{
    unsigned int stime;
    time_t ltime;

	ltime = time(NULL);
	// Make small time difference of greater significance
	// to prevent repeating random sequences.
	ltime = ltime << 21;
	stime = (unsigned) ltime / 2;
	srand(stime);
	}