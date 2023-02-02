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
        if (!(i == 7 || i == 8 || i == 9 || i == 19 || i == 20 || i == 21 || i == 22)) {
            this->scoreButtons[j] = new QPushButton();
            this->scoreButtons[j]->setEnabled(false);
            this->scoreButtons[j]->setFixedSize(20, 20);
            this->scoreButtons[j]->setCheckable(true);
            this->gBox->addWidget(this->scoreButtons[j], i, 4);
        }
        j++;
    }
    this->scorecardReset();
    connect(this->scoreButtons[ACE], SIGNAL(clicked()), SLOT(slotAce()));
    connect(this->scoreButtons[TWO], SIGNAL(clicked()), SLOT(slotTwo()));
    connect(this->scoreButtons[THREE], SIGNAL(clicked()), SLOT(slotThree()));
    connect(this->scoreButtons[FOUR], SIGNAL(clicked()), SLOT(slotFour()));
    connect(this->scoreButtons[FIVE], SIGNAL(clicked()), SLOT(slotFive()));
    connect(this->scoreButtons[SIX], SIGNAL(clicked()), SLOT(slotSix()));
    connect(this->scoreButtons[THREEOFAKIND], SIGNAL(clicked()), SLOT(slotThreeOfaKind()));
    connect(this->scoreButtons[FOUROFAKIND], SIGNAL(clicked()), SLOT(slotFourOfaKind()));
    connect(this->scoreButtons[FULLHOUSE], SIGNAL(clicked()), SLOT(slotFullHouse()));
    connect(this->scoreButtons[LOWSTRAIGHT], SIGNAL(clicked()), SLOT(slotLowStrght()));
    connect(this->scoreButtons[HIGHSTRAIGHT], SIGNAL(clicked()), SLOT(slotHighStrght()));
    connect(this->scoreButtons[POKA], SIGNAL(clicked()), SLOT(slotPoka()));
    connect(this->scoreButtons[CHANCE], SIGNAL(clicked()), SLOT(slotChance()));
}

//rkScorecard::rkScorecard(const rkScorecard& orig) {
//}

rkScorecard::~rkScorecard() {
}

int rkScorecard::getScore(void)
{
    return (this->score[GRANDTOTAL]);
}

bool rkScorecard::isScorecardFull(void)
{
    if(this->cardFull == TOTALSCORES) return (true);
    else return (false);
}

void rkScorecard::scorecardReset(void) {
    int i;
    QString string;
    for (i = 0; i < NUMOFSCORES; i++) {
        this->scoreDone[i] = false;
        this->score[i] = 0;
        if ((!(((i > 5) && (i < 9)) || (i > 15)))) {
            string.setNum(score[i]);
            this->scoreValues[i]->setText(string);
            this->scoreButtons[i]->setEnabled(true);
            this->scoreButtons[i]->setChecked(false);
            this->scoreValues[i]->setStyleSheet("QLabel {color: black}");
        }
    }
    setTotal();
    toggleScoreButtons(false); /* Disable the score buttons. */
}

void rkScorecard::toggleScoreButtons(bool state) {
    int i;
    for (i = 0; i < NUMOFSCORES; i++) {
        if (this->scoreButtons[i] != NULL && (this->scoreDone[i] == false)) {
            this->scoreButtons[i]->setEnabled(state);
        }
    }
}

void rkScorecard::fixScore(int but) {
    if (this->scoreDone[but] == false) {
        this->scoreDone[but] = true;
        this->scoreButtons[but]->setEnabled(false);
        this->scoreValues[but]->setStyleSheet("QLabel {color: blue}");
    }
    setTotal();
    toggleScoreButtons(false); /* Disable the score buttons. */
    // End turn
    emit this->sigTurnDone();
}

// Add up the scores and display the totals.
void rkScorecard::setTotal(void) {
    int i, temp;
    int utotal, ltotal, gtotal;
    QString string;

    utotal = 0;
    ltotal = 0;
    this->cardFull = 0;
    // Add upper scores
    for (i = 0; i < UPPERSCORES; i++) {
        if (this->scoreDone[i] == true) {
            utotal += this->score[i];
            // Keep count of the num of scores that are set.
            this->cardFull++;
        }
    }
    this->score[TOTAL] = utotal;
    string.setNum(utotal);
    this->scoreValues[TOTAL]->setText(string);
    // Add in the bonus.
    if (utotal >= 50) {
        this->score[BONUS] = 25;
        utotal += 25;
    }        // Zero the bonus for a new game.
    else {
        this->score[BONUS] = 0;
    }
    string.setNum(this->score[BONUS]);
    this->scoreValues[BONUS]->setText(string);
    this->score[UPPERTOTAL] = utotal;
    string.setNum(utotal);
    this->scoreValues[UPPERTOTAL]->setText(string);
    this->score[UPPERTOTAL2] = utotal;
    this->scoreValues[UPPERTOTAL2]->setText(string);
    // Add lower scores
    for (i = UPPERSCORES; i < NUMOFSCORES; i++) {
        if (this->scoreDone[i] == true) {
            //string = this->score[i]->text();
            temp = this->score[i];
            ltotal += temp;
            // Keep count of the num of scores that are set.
            this->cardFull++;
        }
    }
    this->score[LOWERTOTAL] = ltotal;
    string.setNum(ltotal);
    this->scoreValues[LOWERTOTAL]->setText(string);
    gtotal = utotal + ltotal;
    string.setNum(gtotal);
    this->score[GRANDTOTAL] = gtotal;
    this->scoreValues[GRANDTOTAL]->setText(string);
}

/* Calculate the possible scores and display them. */
void rkScorecard::setScore(int *dice_values) {
    int i, result[NUMOFSCORES], score[NUMOFSCORES];
    QString string;
    int fh1 = 0, fh2 = 0;

    /* Set the local score array to 0. */
    for (i = 0; i < NUMOFSCORES; i++) {
        score[i] = 0;
        result[i] = 0;
    }

    for (i = 0; i < 5; i++) {
        /* Check for number of Ace's Two's Three's etc */
        switch (dice_values[i]) {
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

    score[CHANCE] = 0;
    for (i = 0; i < UPPERSCORES; i++) {
        score[i] = result[i] * (i + 1);         /* Calculate upper scores. */
        score[CHANCE] += score[i];              /* Add up dice for CHANCE. */
        if (result[i] == 2) fh1 = 1;            /* Set flag 1 for FULLHOUSE. */
        if (result[i] == 5) score[POKA] = 50;   /* Check for POKA. */ 
    }

    for (i = 0; i < UPPERSCORES; i++) {
        if (result[i] >= 3) {
            score[THREEOFAKIND] = 15;
            fh2 = 1;                            /* Set flag 2 for FULLHOUSE. */
        }
        if (result[i] >= 4) score[FOUROFAKIND] = 20;
    }
    if ((fh1 + fh2) == 2) score[FULLHOUSE] = 25;
    if (result[0] && result[1] && result[2] && result[3]) score[LOWSTRAIGHT] = 30;
    if (result[1] && result[2] && result[3] && result[4]) score[LOWSTRAIGHT] = 30;
    if (result[2] && result[3] && result[4] && result[5]) score[LOWSTRAIGHT] = 30;
    if (result[0] && result[1] && result[2] && result[3] && result[4]) score[HIGHSTRAIGHT] = 40;
    if (result[1] && result[2] && result[3] && result[4] && result[5]) score[HIGHSTRAIGHT] = 40;

    for (i = 0; i < NUMOFSCORES; i++) {
        /* Don't change the scores if they are set or if its the totals */
        if ((this->scoreDone[i] == false) && (!(((i > 5) && (i < 9)) || (i > 15)))) {
            string.setNum(score[i]);
            this->score[i] = score[i];
            this->scoreValues[i]->setText(string);
        }
    }
    toggleScoreButtons(true); /* Enable the score buttons. */
}
