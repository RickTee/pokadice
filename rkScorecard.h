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
//#define UPPERTOTALS	3
//#define	LOWERSCORES	UPPERSCORES + UPPERTOTALS + 7	
//#define LOWERTOTALS	3
#define NUMOFDICE       5

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
    QVBoxLayout *vBox;
    QHBoxLayout *hBox;
    QGridLayout *gBox;
    QLabel      *scoreTitles[NUMOFSCORES];
    QLabel      *scoreValues[NUMOFSCORES];
    QPushButton *scoreButtons[NUMOFSCORES];
    bool        scoreDone[NUMOFSCORES];
    int         score[NUMOFSCORES];
    void        toggleScoreButtons(bool);
    void        scorecardReset(void);
    //void        fixScore(int);
    public slots:
        void setScore(int *);
        void fixScore(int);
    signals:
	void sig_clicked(int );
    private slots:
        // These just map the button released signals of the scores
        // to the fix_score() method so it knows which button was
        // pressed.
        void slot_ace       (){ fixScore(ACE);          }
        void slot_two       (){ fixScore(TWO);          }
        void slot_three     (){ fixScore(THREE);        }
        void slot_four      (){ fixScore(FOUR);         }
        void slot_five      (){ fixScore(FIVE);         }
        void slot_six       (){ fixScore(SIX);          }
        void slot_threeof   (){ fixScore(THREEOFAKIND); }
        void slot_fourof    (){ fixScore(FOUROFAKIND);  }
        void slot_fhouse    (){ fixScore(FULLHOUSE);    }
        void slot_lstrght   (){ fixScore(LOWSTRAIGHT);  }
        void slot_hstrght   (){ fixScore(HIGHSTRAIGHT); }
        void slot_poka      (){ fixScore(POKA);         }
        void slot_chance    (){ fixScore(CHANCE);       }
    
};

#endif /* RKSCORECARD_H */
