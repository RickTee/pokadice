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

#ifndef RKDICE_H
#define RKDICE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QBoxLayout>
#include <QPushButton>

class rkDice : public QWidget{
    Q_OBJECT
public:
    rkDice(int num, QPixmap *diceImage, QWidget * parent = 0);
    //rkDice(const rkDice& orig);
    virtual ~rkDice();
    QVBoxLayout *vBox;
    QHBoxLayout *hBoxDice;
    QHBoxLayout *hBoxHoldButton;
    QLabel      *diceFace;
    QPushButton *holdButton;
    QPixmap     *pixMap;
    bool        onOff;
    bool getHold();
    void setNum(int, QPixmap *);
    int getNum(void);
    int number;
    //void setHold(int state){ clicked(state); }
    public slots:
        void setHold();
    signals:
	//void sig_clicked();
};

#endif /* RKDICE_H */
