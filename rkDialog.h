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

class rkDialog : public QDialog{
    Q_OBJECT
public:
    rkDialog(QDialog * parent = 0);
    //rkDialog(const rkDialog& orig);
    virtual ~rkDialog();
    QVBoxLayout *vBox;
    QHBoxLayout *hBox;
    QLabel      *title;
    QLabel      *message;
    QPushButton *okButton;
    QPushButton *quitButton;
    QPushButton *resetScoreButton;
    
    public slots:
        void slotQuitGame(void);
        void slotNewGame(void);
        
    signals:
	void sigNewGame(void);
	void sigQuitGame(void);
};

#endif /* RKDIALOG_H */
