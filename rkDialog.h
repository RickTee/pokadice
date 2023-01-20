/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkDialog.h
 * Author: rick
 *
 * Created on 05 January 2023, 11:50
 */

#ifndef RKDIALOG_H
#define RKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include "rkPrefs.h"

class rkDialog : public QDialog{
    Q_OBJECT
public:
    rkDialog(QDialog * parent = 0);
    rkDialog(QString *name, int score, QDialog * parent = 0);
    rkDialog(QString **names, int *scores, QDialog * parent = 0);
    rkDialog(rkPrefs *prefs, QDialog * parent = 0);
    //rkDialog(const rkDialog& orig);
    virtual ~rkDialog();
    QVBoxLayout *vBox;
    QHBoxLayout *hBox;
    QHBoxLayout *hBox1;
    QLabel      *title;
    QLabel      *message;
    QLabel      *winnerScore;
    QPushButton *addPlayerButton;
    QPushButton *deletePlayerButton;
    QPushButton *okButton;
    QPushButton *newGameButton;
    QPushButton *quitButton;
    QPushButton *resetScoreButton;
    void setMessage(QString);
    
    public slots:
        void slotExitDialog(void);
        void slotAddPlayer(void);
        void slotDeletePlayer(void);
        
    signals:
	void sigNewGame(void);
	void sigQuitGame(void);
};

#endif /* RKDIALOG_H */
