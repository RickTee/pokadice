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
#include <stdio.h>
#include "rkScorecard.h"

rkScorecard::rkScorecard(QWidget * parent) : QWidget(parent) {
    QFrame * hLines[5], *vLines[2];
    QString scoreTitles[] = {"Aces", "Twos", "Threes", "Fours", "Fives", "Sixes", "Total", "Bonus (25)", "Upper Total",
        "Three of a kind", "Four of a kind", "Full house", "Low Straight", "High straight", "Poka!", "Chance", "Upper total",
        "Lower total", "Grand total"};
    int i, j;
    
    this->gBox = new QGridLayout(this);
    this->gBox->setVerticalSpacing(3);
   
    vLines[0] = new QFrame();
    
    vLines[0]->setFrameStyle(QFrame::VLine | QFrame::Sunken);
    this->gBox->addWidget(vLines[0], 0, 1, 23, 1);
    vLines[1] = new QFrame();
    vLines[1]->setFrameStyle(QFrame::VLine | QFrame::Sunken);
    this->gBox->addWidget(vLines[1], 0, 3, 23, 1);
    // Horizontal lines
    hLines[0] = new QFrame();
    hLines[0]->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    this->gBox->addWidget(hLines[0], 6, 0, 1, 5);
    hLines[1] = new QFrame();
    hLines[1]->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    this->gBox->addWidget(hLines[1], 10, 0, 1, 5);
    hLines[2] = new QFrame();
    hLines[2]->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    this->gBox->addWidget(hLines[2], 18, 0, 1, 5);
    hLines[3] = new QFrame();
    hLines[3]->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    this->gBox->addWidget(hLines[3], 21, 0, 1, 5);
    hLines[4] = new QFrame();
    hLines[4]->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    this->gBox->addWidget(hLines[4], 24, 0, 1, 5);

    j = 0;
    for (i = 0; i < 23; i++) {
        // Skip horizontal lines
        if (i == 6 || i == 10 || i == 18 || i == 21) continue;

        this->scoreTitles[j] = new QLabel(scoreTitles[j]);
        this->scoreValues[j] = new QLabel("0");
        this->gBox->addWidget(this->scoreTitles[j], i, 0);
        this->gBox->addWidget(this->scoreValues[j], i, 2, Qt::AlignHCenter | Qt::AlignVCenter);
        // Build a sparse array for the buttons so they align with the score labels
        // set all to NULL so we can test later
        this->scoreButtons[j] = NULL;
        // Skip total, bonus, uppertotal, uppertotal2, lowertotal and grandtotal
        if (!(i == 7 || i == 8 || i == 9 || i == 19 || i == 20 || i==21 || i == 22)) {
            this->scoreButtons[j] = new QPushButton();
            this->scoreButtons[j]->setDisabled(true);
            this->scoreButtons[j]->setFixedSize(20,20);
            this->scoreButtons[j]->setCheckable(true);
            this->gBox->addWidget(this->scoreButtons[j], i, 4);
        }
        j++;
    }
    this->scorecardReset();
    connect(this->scoreButtons[ACE],            SIGNAL(clicked()), SLOT(slot_ace()));
    connect(this->scoreButtons[TWO],            SIGNAL(clicked()), SLOT(slot_two()));
    connect(this->scoreButtons[THREE],          SIGNAL(clicked()), SLOT(slot_three()));
    connect(this->scoreButtons[FOUR],           SIGNAL(clicked()), SLOT(slot_four()));
    connect(this->scoreButtons[FIVE],           SIGNAL(clicked()), SLOT(slot_five()));
    connect(this->scoreButtons[SIX],            SIGNAL(clicked()), SLOT(slot_six()));
    connect(this->scoreButtons[THREEOFAKIND],   SIGNAL(clicked()), SLOT(slot_threeof()));
    connect(this->scoreButtons[FOUROFAKIND],    SIGNAL(clicked()), SLOT(slot_fourof()));
    connect(this->scoreButtons[FULLHOUSE],      SIGNAL(clicked()), SLOT(slot_fhouse()));
    connect(this->scoreButtons[LOWSTRAIGHT],    SIGNAL(clicked()), SLOT(slot_lstrght()));
    connect(this->scoreButtons[HIGHSTRAIGHT],   SIGNAL(clicked()), SLOT(slot_hstrght()));
    connect(this->scoreButtons[POKA],           SIGNAL(clicked()), SLOT(slot_poka()));
    connect(this->scoreButtons[CHANCE],         SIGNAL(clicked()), SLOT(slot_chance()));
}

//rkScorecard::rkScorecard(const rkScorecard& orig) {
//}

rkScorecard::~rkScorecard() {
}

void rkScorecard::toggleScoreButtons(bool state)
{
    int i;
    for(i = 0; i < NUMOFSCORES; i++)
    {
        if(this->scoreButtons[i])
        {
            this->scoreButtons[i]->setDisabled(false);
        }
    }
}

void rkScorecard::fixScore(int but)
{
    //printf("button %d\n", but);
    this->scoreDone[but] = 1;
    this->scoreButtons[but]->setDisabled(true);
}

/* Calculate the possible scores and display them. */
void rkScorecard::setScore(int *dice_values)
{
    int i, result[NUMOFSCORES], score[NUMOFSCORES];
    QString string;
    int fh1 = 0, fh2 = 0;

    /* Set the local score array to 0. */
    for (i = 0; i < NUMOFSCORES; i++)
    {
        score[i] = 0;
        result[i] = 0;
    }
//    for (i = 0; i < 6; i++)
//    {
//        result[i] = 0;
//    }
    
    for (i = 0; i < 5; i++)
    {
        /* Check for number of Ace's Two's Three's etc */
        switch (dice_values[i])
        {
        case ACE:
            result[ACE]++;
            break;
        case TWO:
            result[TWO]++;
            break;
        case THREE:
            result[THREE]++;
            break;
        case FOUR:
            result[FOUR]++;
            break;
        case FIVE:
            result[FIVE]++;
            break;
        case SIX:
            result[SIX]++;
            break;
        }
    }
//    for (i = 0; i < 5; i++)
//    {
//        printf("dice_values[%d] = %d", i,dice_values[i]);
//        printf(" result[%d] = %d \n", i, result[i]);
//     }
//    printf("\n");
    score[CHANCE] = 0;
    for (i = 0; i < UPPERSCORES; i++)
    {
        score[i] = result[i] * (i + 1); /* Calculate upper scores. */
        score[CHANCE] += score[i];      /* Add up dice for CHANCE. */
        if (result[i] == 2) fh1 = 1;    /* Set flag 1 for FULL_HOUSE. */
        if (result[i] == 5)             /* Check for POKA. */
        {
            score[POKA] = 50;
        }
    }
    
    for (i = 0; i < UPPERSCORES; i++)
    {
        if (result[i] >= 3) {score[THREEOFAKIND] = score[CHANCE]; fh2 = 1;}
        if (result[i] >= 4) score[FOUROFAKIND] = score[CHANCE];
    }
    if ((fh1 + fh2) == 2) score[FULLHOUSE] = 25;
    if (result[0] && result[1] && result[2] && result[3]) score[LOWSTRAIGHT] = 30;
    if (result[1] && result[2] && result[3] && result[4]) score[LOWSTRAIGHT] = 30;
    if (result[2] && result[3] && result[4] && result[5]) score[LOWSTRAIGHT] = 30;
    if (result[0] && result[1] && result[2] && result[3] && result[4]) score[HIGHSTRAIGHT] = 40;
    if (result[1] && result[2] && result[3] && result[4] && result[5]) score[HIGHSTRAIGHT] = 40;
    
    for (i = 0; i < NUMOFSCORES; i++)
    {
        /* Don't change the scores if they are set or if its the totals */
        if ((!this->scoreDone[i]) && (!(((i > 5) && (i < 9)) || (i > 15))))
        {
            string.setNum(score[i]);
            this->score[i] = score[i];
            this->scoreValues[i]->setText(string);
        }
    }
    toggleScoreButtons(true); /* Enable the score buttons. */
}

void rkScorecard::scorecardReset(void)
{
    int i;
    for(i = 0; i < NUMOFSCORES; i++)
    {
        this->scoreDone[i] = false;
    }
}