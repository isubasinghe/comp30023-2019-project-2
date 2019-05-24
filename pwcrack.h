#ifndef PWCRACK_H
#define PWCRACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD_LEN 12000

#include "bitreader.h"
#include "dt_hashtable.h"
#include "sha256.h"


void ReadLineCrack(char *passwords, char *hashfile);




#endif // PWCRACK_H