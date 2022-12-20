/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkPokadice.h
 * Author: rick
 *
 * Created on 17 December 2022, 14:20
 */

#ifndef RKPOKADICE_H
#define RKPOKADICE_H

#include <QWidget>
#include <QBoxLayout>
#include "rkDiceControl.h"
#include "rkScorecard.h"

class rkPokadice : public QWidget{
    Q_OBJECT
public:
    rkPokadice(QWidget * parent = 0);
    //rkDice(const rkPokadice& orig);
    virtual ~rkPokadice();
    QVBoxLayout     *vBox;
    rkDiceControl   *diceControl;
    rkScorecard     *scorecard;
    
    //void setHold(int state){ clicked(state); }
    public slots:
        //void setHold();
    signals:
	//void sig_clicked();
};

#endif /* RKPOKADICE_H */
