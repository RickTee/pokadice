/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkDialog.cpp
 * Author: rick
 * 
 * Created on 03 February 2023, 10:06
 */

#include <qt5/QtWidgets/qwidget.h>

#include "rkDialog.h"

// About constructor
rkDialog::rkDialog(QWidget * parent) : QDialog(parent) {
    //QString *aboutString = new QString(APPLICATION"\n" DESCRIPTION"\n\n" "Author: " AUTHOR"\n" EMAIL"\n");
    
    this->setModal(true);
    this->setWindowTitle("About");
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->title = new QLabel("About");
    this->title->setAlignment(Qt::AlignCenter);
    this->message = new QLabel(APPLICATION"\n" DESCRIPTION"\n\n" "Author: " AUTHOR"\n" EMAIL"\n");
    this->message->setAlignment(Qt::AlignCenter);
    this->okButton = new QPushButton("Ok");
    this->newGameButton = new QPushButton("New Game");
    this->quitButton = new QPushButton("Quit Game");

    this->vBox->addWidget(this->title);
    this->vBox->addWidget(this->message);
    this->setLayout(this->vBox);
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->okButton);
    this->hBox->addWidget(this->newGameButton);
    this->hBox->addWidget(this->quitButton);

    connect(this->okButton, SIGNAL(clicked()), SIGNAL(sigDialogDone()));
    connect(this->newGameButton, SIGNAL(clicked()), SLOT(slotPrefsNewGame()));
    connect(this->quitButton, SIGNAL(clicked()), SLOT(slotPrefsQuitGame()));
}

// Winner constructor
rkDialog::rkDialog(QString *name, int score, QWidget * parent) : QDialog(parent) {
    this->setModal(true);
    this->setWindowTitle("Game Over");
    
    this->wScore = new QString("ka-ching");
    this->wScore->setNum(score);
    this->winner = new QString("With a score of : ");
    this->winner->append(this->wScore);
    this->message = new QLabel(*this->winner);
    this->message->setAlignment(Qt::AlignCenter);
    this->winnerName = new QLabel(*name);
    this->winnerName->setAlignment(Qt::AlignCenter);
    this->winnerName->setStyleSheet("QLabel {color: red; font: 16px}");
        
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->hBox1 = new QHBoxLayout();
    this->title = new QLabel("Winner");
    this->title->setAlignment(Qt::AlignCenter);

    this->okButton = new QPushButton("Ok");
    this->newGameButton = new QPushButton("New Game");
    this->quitButton = new QPushButton("Quit Game");

    this->vBox->addWidget(this->title);
    this->vBox->addWidget(this->winnerName);
    this->vBox->addWidget(this->message);
    this->vBox->addLayout(this->hBox1);
    this->setLayout(this->vBox);
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->okButton);
    this->hBox->addWidget(this->newGameButton);
    this->hBox->addWidget(this->quitButton);

    connect(this->okButton, SIGNAL(clicked()), SLOT(slotExitDialog()));
    connect(this->newGameButton, SIGNAL(clicked()), SLOT(slotPrefsNewGame()));
    connect(this->quitButton, SIGNAL(clicked()), SLOT(slotPrefsQuitGame()));
}

// Settings constructor
rkDialog::rkDialog(rkPrefs *prfs, QWidget * parent) : QDialog(parent){
    int i;
    this->setModal(true);
    this->setWindowTitle("Settings");
    this->prefs = prfs;
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->hBox1 = new QHBoxLayout();
    this->title = new QLabel("Settings");
    this->addPlayerButton = new QPushButton("Add Player");
    this->deletePlayerButton = new QPushButton("Delete Player");
    this->okButton = new QPushButton("Ok");
    this->cancelButton = new QPushButton("Cancel");
    
    this->vBox->addWidget(this->title);
    this->setLayout(this->vBox);
    
    for(i = 0; i < this->prefs->numOfPlayers; i++){
        this->playerEdit[i] = new QLineEdit(*this->prefs->playerNames[i]);
        this->vBox->addWidget(this->playerEdit[i]);
    }
    
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->addPlayerButton);
    this->hBox->addWidget(this->deletePlayerButton);
    this->vBox->addLayout(this->hBox1);
    this->hBox1->addWidget(this->okButton);
    this->hBox1->addWidget(this->cancelButton);
    
    connect(this->cancelButton, SIGNAL(clicked()), SLOT(slotSettingsCancelled()));
    connect(this->okButton, SIGNAL(clicked()), SLOT(slotSettingsDone()));
    connect(this->addPlayerButton, SIGNAL(clicked()), SLOT(slotAddPlayer()));
    connect(this->deletePlayerButton, SIGNAL(clicked()), SLOT(slotDeletePlayer()));
}

rkDialog::~rkDialog() {
}

void rkDialog::slotAddPlayer(void){
    QString num(QString::number(this->prefs->numOfPlayers + 1));
    //if(this->playerNames[this->numOfPlayers] == NULL) {
        this->prefs->playerNames[this->prefs->numOfPlayers] = new QString("Player");
        this->prefs->playerNames[this->prefs->numOfPlayers]->append(num);
        this->playerEdit[this->prefs->numOfPlayers] = new QLineEdit(*this->prefs->playerNames[this->prefs->numOfPlayers]);
        this->vBox->insertWidget(this->prefs->numOfPlayers + 1, this->playerEdit[this->prefs->numOfPlayers]);
    //}
    
    // Problem: if user hits cancel after pressing add player numOfPlayers is still incremented
    this->prefs->numOfPlayers++;
    if(this->prefs->numOfPlayers > MAXPLAYERS) this->prefs->numOfPlayers = MAXPLAYERS;
}

void rkDialog::slotDeletePlayer(void){
    if(this->prefs->numOfPlayers > 1) {
        //Remove the Edit box and decrement player count
        this->prefs->numOfPlayers--;
        this->vBox->removeWidget(this->playerEdit[this->prefs->numOfPlayers]);
        
        delete this->playerEdit[this->prefs->numOfPlayers];
        this->adjustSize();
    }
}

void rkDialog::slotSettingsDone(void){
    int i;
    for(i = 0; i < this->prefs->numOfPlayers; i++){
        // Delete the QStrings containing player names and recreate them
        delete this->prefs->playerNames[i];
        this->prefs->playerNames[i] = new QString(this->playerEdit[i]->text());
    }
    this->prefs->savePrefs();
    emit sigNewGame();
    emit sigDialogDone();
}

void rkDialog::slotPrefsNewGame(void){
    emit sigNewGame();
    emit sigDialogDone();
}

void rkDialog::slotPrefsQuitGame(void){
    //emit sigDialogDone();
    emit sigQuitGame();
}
// User pressed cancel
void rkDialog::slotSettingsCancelled(void){
    this->prefs->numOfPlayers = this->prefs->numOfPlayersCpy;
    emit sigDialogDone();
    //slotExitDialog();
}

void rkDialog::slotExitDialog(void){
    emit sigDialogDone();
}

