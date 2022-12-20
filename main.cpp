/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: rick
 *
 * Created on 17 December 2022, 14:16
 */

#include <QApplication>
#include <QWidget>
#include <qt5/QtWidgets/qlayout.h>
#include "rkDiceControl.h"
//#include "rkScorecard.h"
//#include "rkPokadice.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    // create and show your widgets here
    rkDiceControl dice_1(5);
    
    dice_1.show();
    return app.exec();
}
