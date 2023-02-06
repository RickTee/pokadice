/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkDice.h
 * Author: rick
 *
 * Created on 17 December 2022, 14:20
 */

#ifndef RKSCORECARD_H
#define RKSCORECARD_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

#define NUMOFSCORES     19
#define UPPERSCORES	6
#define TOTALSCORES     13

/* enums: For clarity when indexing arrays. */
enum scores
{
    ACE, TWO, THREE, FOUR, FIVE, SIX, TOTAL, BONUS, UPPERTOTAL,
    THREEOFAKIND, FOUROFAKIND, FULLHOUSE, LOWSTRAIGHT, HIGHSTRAIGHT,
    POKA, CHANCE, UPPERTOTAL2, LOWERTOTAL, GRANDTOTAL
};

class rkScorecard : public QWidget{
    Q_OBJECT
public:
    rkScorecard(QWidget * parent = 0);
    //rkScorecard(const rkScorecard& orig);
    virtual ~rkScorecard();
private:
    QVBoxLayout *vBox;
    QHBoxLayout *hBox;
    QGridLayout *gBox;
    QLabel      *scoreTitles[NUMOFSCORES];
    QLabel      *scoreValues[NUMOFSCORES];
    QPushButton *scoreButtons[NUMOFSCORES];
    bool        scoreDone[NUMOFSCORES];
    int         score[NUMOFSCORES];
    int         cardFull;
    void        toggleScoreButtons(bool);
    void        scorecardReset(void);
    void        setTotal(void);
    void        fixScore(int);
public:
    bool        getScoreDone(int indx);
    void        pressScoreButton(int indx);
    void        setScore(int *);
    // Check if this score card is full
    bool        isScorecardFull(void);
    int         getScore(void);

    private slots:
        // These just map the button released signals of the scores
        // to the fix_score() method so it knows which button was
        // pressed.
        void slotAce(void)          { fixScore(ACE);          }
        void slotTwo(void)          { fixScore(TWO);          }
        void slotThree(void)        { fixScore(THREE);        }
        void slotFour(void)         { fixScore(FOUR);         }
        void slotFive(void)         { fixScore(FIVE);         }
        void slotSix(void)          { fixScore(SIX);          }
        void slotThreeOfaKind(void) { fixScore(THREEOFAKIND); }
        void slotFourOfaKind(void)  { fixScore(FOUROFAKIND);  }
        void slotFullHouse(void)    { fixScore(FULLHOUSE);    }
        void slotLowStrght(void)    { fixScore(LOWSTRAIGHT);  }
        void slotHighStrght(void)   { fixScore(HIGHSTRAIGHT); }
        void slotPoka(void)         { fixScore(POKA);         }
        void slotChance(void)       { fixScore(CHANCE);       }
        
    signals:
	void sigTurnDone(void);
};

#endif /* RKSCORECARD_H */
