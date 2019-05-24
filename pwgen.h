#ifndef PWGEN_H
#define PWGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "names.h"
#include "words.h"

#define BRUTEFORCE_MAX4 78074896


// My smart password guessing algorithm
// take a 4 letter word and add [0-99]
// take a 4 name and add [50-99]
// take a 6 letter word and leetify
// revert to complete bruteforce if nothing was found

#define ASCII_START 32
#define ASCII_END 126


int PW_GenCrackNumbers(int stop);

int PW_NameCrack(int stop);

int PW_WordCrack(int stop);

int PW_Transform(char *buffer, int stop);

int PW_Leetify(char *buffer, int stop);

int PW_AddChar(char *buffer, int stop);


void PW_BruteForce(int num, long long stop);


void PW_GenLen4(char *buffer, int stop);

void PW_GenLen6(char *buffer, long long stop);

void PW_GenCrack(int stop);

#endif // PWGEN_H