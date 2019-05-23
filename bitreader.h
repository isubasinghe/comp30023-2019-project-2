#ifndef BITREADER_H
#define BITREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"bitreader.h"
#include "dt_hashtable.h"



DT_HashTable *ReadBinaryFile(char *fname);

char *BytesToHexStr(unsigned char *bytes, int num);

#endif //BITREADER_H