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

class rkScorecard : public QWidget{
    Q_OBJECT
public:
    rkScorecard(QWidget * parent = 0);
    //rkScorecard(const rkScorecard& orig);
    virtual ~rkScorecard();
    QVBoxLayout *vBox;
    QHBoxLayout *hBox;
    QGridLayout *gBox;
    QLabel      *scoreTitles[19];
    QLabel      *scores[19];
    QPushButton *scoreButtons[19];
    
    //void setHold(int state){ clicked(state); }
    public slots:
        //void setHold();
    signals:
	//void sig_clicked();
};

#endif /* RKSCORECARD_H */
