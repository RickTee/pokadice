/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   prefs.cpp
 * Author: rick
 * 
 * Created on 02 January 2023, 10:06
 */

#include "rkPrefs.h"

rkPrefs::rkPrefs() {
    sprintf(this->fileName, "%s%s%s", HOME_PATH, FILE_PATH, FILE_NAME);
    this->loadPrefs();
    this->savePrefs();
}

//rkPrefs::rkPrefs(const rkPrefs& orig) {
//}

rkPrefs::~rkPrefs() {
}

void rkPrefs::savePrefs(){
    std::ofstream file_Handle;

    // File Open
    file_Handle.open(this->fileName);

    //std::cout << "this->fileName " << this->fileName;
    
    file_Handle << this->playerNames[0] << ";";
    file_Handle << this->playerNames[1];

    // File Close
    file_Handle.close();
    //return 0;
}

void rkPrefs::loadPrefs()
{
    std::ofstream file_Handle;
    std::ifstream MyReadFile(this->fileName);
    
    std::string input;
    //file_Handle.open(this->fileName);
    
    getline (MyReadFile, input);
    std::cout << "Input = " << input;
    
    strncpy(this->playerNames[0], "Rick", MAXLEN);
    strncpy(this->playerNames[1], "Richard", MAXLEN);
}