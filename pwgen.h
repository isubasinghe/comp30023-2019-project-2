#ifndef PWGEN_H
#define PWGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "names.h"

// take a 4 letter word and add [0-99]
// take a 4 name and add [50-99]
// take a 6 letter word and leetify



#define ASCII_START 32
#define ASCII_END 126


int PW_GenCrackNumbers(int stop);

int PW_NameCrack(int stop);

int PW_Transform(char *buffer, int stop);

int PW_Leetify(char *buffer, int stop);

int PW_AddChar(char *buffer, int stop);

int PW_AddNum(char *buffer, int stop);


void PW_BruteForce(int num, unsigned long long stop);


void PW_GenLen4(char *buffer, int stop);

void PW_GenLen6(char *buffer, unsigned long long stop);

void PW_GenCrack(int stop);

#endif // PWGEN_H