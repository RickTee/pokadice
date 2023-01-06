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

rkDialog::rkDialog(QDialog * parent) : QDialog(parent) {
    this->setWindowModality(Qt::ApplicationModal);
    this->vBox = new QVBoxLayout();
    this->hBox	= new QHBoxLayout();
    this->okButton = new QPushButton("New Game");
    this->quitButton = new QPushButton("Quit Game");
    
    this->setLayout(this->hBox);
    this->hBox->addWidget(this->okButton);
    this->hBox->addWidget(this->quitButton);
    
    connect(this->okButton, SIGNAL(clicked()), SLOT(slotNewGame()));
    connect(this->quitButton, SIGNAL(clicked()), SLOT(slotQuitGame()));
}

//rkDialog::rkDialog(const rkDice& orig) {
//}

rkDialog::~rkDialog() {
}

void rkDialog::slotQuitGame()
{
    emit sigQuitGame();
}

void rkDialog::slotNewGame(void) {
    emit sigNewGame();
}