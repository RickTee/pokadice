/*
 * File: version.h
 * Program: Pokadice
 * Author: Richard G Townsend
 * Email: ricktee@virginmedia.com
 * Created on: Dec 17, 2022, 14:16
 * Copyright (C) 2022 - 2026  Richard G Townsend
 * Standard major, minor, micro version number.
 */

#ifndef __VERSION_H__
#define __VERSION_H__

#define SPC         " "
#define RELEASE     "1.0"
#define REVISION    ".1"
#define DATE        "( Dec 2022)"
#define YEAR        "2022 - 2026"
#define VERSION     RELEASE REVISION SPC DATE

#define AUTHOR      "Richard G Townsend"
#define TITLE       "Pokadice "
#define GAME        "P O K A D I C E"
#define DESCRIPTION "Yahtzee clone using Qt 5"
#define VERSTAG     "$VER: " TITLE VERSION SPC DESCRIPTION
#define APPLICATION TITLE VERSION
#define COPYRIGHT   "(C) " YEAR SPC AUTHOR
#define EMAIL       "ricktee@virginmedia.com"

#endif
