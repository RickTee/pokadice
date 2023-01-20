/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rkDialog.cpp
 * Author: rick
 * 
 * Created on 05 January 2023, 11:50
 */

#include "rkDialog.h"
#include "version.h"

// About
rkDialog::rkDialog(QDialog * parent) : QDialog(parent) {
    this->setModal(true);
    QString *aboutString = new QString(APPLICATION"\n" DESCRIPTION"\n\n" "Author: " AUTHOR"\n" EMAIL"\n");
    
    this->setWindowTitle("About");
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->title = new QLabel("About");
    this->title->setAlignment(Qt::AlignCenter);
    this->message = new QLabel(*aboutString);
    this->message->setAlignment(Qt::AlignCenter);
    //this->winnerScore = new QLabel("Pokadice");
    //this->winnerScore->setAlignment(Qt::AlignCenter);
    this->okButton = new QPushButton("Ok");
    this->newGameButton = new QPushButton("New Game");
    this->quitButton = new QPushButton("Quit Game");

    this->vBox->addWidget(this->title);
    this->vBox->addWidget(this->message);
    //this->vBox->addWidget(this->winnerScore);
    this->setLayout(this->vBox);
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->okButton);
    this->hBox->addWidget(this->newGameButton);
    this->hBox->addWidget(this->quitButton);

    connect(this->okButton, SIGNAL(clicked()), SLOT(slotExitDialog()));
    connect(this->newGameButton, SIGNAL(clicked()), SIGNAL(sigNewGame()));
    connect(this->quitButton, SIGNAL(clicked()), SIGNAL(sigQuitGame()));
}

//rkDialog::rkDialog(const rkDice& orig) {
//}

rkDialog::~rkDialog() {
}

// Settings
rkDialog::rkDialog(rkPrefs *prefs, QDialog * parent) : QDialog(parent){
    this->setWindowTitle("Settings");
        
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->hBox1 = new QHBoxLayout();
    this->title = new QLabel("Settings");
    this->addPlayerButton = new QPushButton("Add Player");
    this->deletePlayerButton = new QPushButton("Delete Player");
    this->okButton = new QPushButton("Ok");
    this->newGameButton = new QPushButton("New Game");
    this->quitButton = new QPushButton("Quit Game");

    this->vBox->addWidget(this->title);
    this->setLayout(this->vBox);
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->addPlayerButton);
    this->hBox->addWidget(this->deletePlayerButton);
    this->vBox->addLayout(this->hBox1);
    this->hBox1->addWidget(this->okButton);
    this->hBox1->addWidget(this->newGameButton);
    this->hBox1->addWidget(this->quitButton);
    
    connect(this->okButton, SIGNAL(clicked()), SLOT(slotExitDialog()));
    connect(this->addPlayerButton, SIGNAL(clicked()), SLOT(slotAddPlayer()));
    connect(this->deletePlayerButton, SIGNAL(clicked()), SLOT(slotDeletePlayer()));
    connect(this->newGameButton, SIGNAL(clicked()), SIGNAL(sigNewGame()));
    connect(this->quitButton, SIGNAL(clicked()), SIGNAL(sigQuitGame()));
}

//Game over
rkDialog::rkDialog(QString *name, int score, QDialog * parent) : QDialog(parent) {
    QString *winner = new QString(" with a score of: ");
    QString *wScore = new QString("");
    wScore->setNum(score);
    winner->append(wScore);
    this->setWindowTitle("Game Over");
        
    this->vBox = new QVBoxLayout();
    this->hBox = new QHBoxLayout();
    this->hBox1 = new QHBoxLayout();
    this->title = new QLabel("Game over");
    this->title->setAlignment(Qt::AlignCenter);
    this->message = new QLabel(*name);
    this->message->setAlignment(Qt::AlignCenter);
    this->winnerScore = new QLabel(*winner);
    //this->winnerScore->setNum(score);
    this->okButton = new QPushButton("Ok");
    this->newGameButton = new QPushButton("New Game");
    this->quitButton = new QPushButton("Quit Game");

    this->vBox->addWidget(this->title);
    this->hBox1->addWidget(this->message);
    this->hBox1->addWidget(this->winnerScore);
    this->vBox->addLayout(this->hBox1);
    this->setLayout(this->vBox);
    this->vBox->addLayout(this->hBox);
    this->hBox->addWidget(this->okButton);
    this->hBox->addWidget(this->newGameButton);
    this->hBox->addWidget(this->quitButton);

    connect(this->okButton, SIGNAL(clicked()), SLOT(slotExitDialog()));
    connect(this->newGameButton, SIGNAL(clicked()), SIGNAL(sigNewGame()));
    connect(this->quitButton, SIGNAL(clicked()), SIGNAL(sigQuitGame()));
}

void rkDialog::setMessage(QString msg){
    this->message->setText(msg);
}

void rkDialog::slotExitDialog(void){
    this->close();
}

void rkDialog::slotAddPlayer(void){
    
}

void rkDialog::slotDeletePlayer(void){
    
}